#include <iostream>
#include <sstream>
#include <regex>
#include <fcgio.h>
#include "web_request_handler.h"
#include "web_view.h"

using namespace std;
using namespace web_gui;

const unsigned long STDIN_MAX = 1000000;

class FcgiWebRequest : public WebRequest
{
    public:
        FcgiWebRequest(const FCGX_Request & request)
            : WebRequest()
            , m_request(request)
            , m_content_extracted(false) { }

        ~FcgiWebRequest() { }

        std::string content() 
        {
           if (!m_content_extracted)
           {
                char * content_length_str = FCGX_GetParam("CONTENT_LENGTH", m_request.envp);
                unsigned long content_length = STDIN_MAX;

                if (content_length_str) {
                    content_length = strtol(content_length_str, &content_length_str, 10);
                    if (*content_length_str) {
                        cerr << "Can't Parse 'CONTENT_LENGTH='"
                             << FCGX_GetParam("CONTENT_LENGTH", m_request.envp)
                             << "'. Consuming stdin up to " << STDIN_MAX << endl;
                    }

                    if (content_length > STDIN_MAX) {
                        content_length = STDIN_MAX;
                    }
                } else {
                    // Do not read from stdin if CONTENT_LENGTH is missing
                    content_length = 0;
                }

                char * content_buffer = new char[content_length];
                cin.read(content_buffer, content_length);
                content_length = cin.gcount();

                // Chew up any remaining stdin - this shouldn't be necessary
                // but is because mod_Fcgi doesn't handle it correctly.

                // ignore() doesn't set the eof bit in some versions of glibc++
                // so use gcount() instead of eof()...
                do cin.ignore(1024); while (cin.gcount() == 1024);

                m_content.assign(content_buffer, content_length);
                delete [] content_buffer;
                m_content_extracted = true;
           }

           return m_content;
        }

        string uri() const
        {
            const char * uri = FCGX_GetParam("REQUEST_URI", m_request.envp);
            return string(uri);
        }

        string query_string() const
        {
            const char * qs = FCGX_GetParam("QUERY_STRING", m_request.envp);
            return string(qs);
        }

        string method() const
        {
            const char * method = FCGX_GetParam("REQUEST_METHOD", m_request.envp);
            return string(method);
        }

        string user_agent() const
        {
            const char * user_agent = FCGX_GetParam("HTTP_USER_AGENT", m_request.envp);
            return string(user_agent);
        }

    private:
        FCGX_Request m_request;
        bool m_content_extracted;
        string m_content;
};

class TestWebView : public WebView
{
    public:
        TestWebView() : WebView() { }
        ~TestWebView() { }

        string handle_request(WebRequest & request)
        {
           
            stringstream response;
            string content(request.content());

            if (content.length() == 0)
            {
                content = ", World!";
            }

            response << "Content-type: text/html\r\n"
                << "\r\n"
                << "<html>\n"
                << "  <head>\n"
                << "    <title>Hello, World!</title>\n"
                << "  </head>\n"
                << "  <body>\n"
                << "    <h1>Hello" << content << " from " << request.uri() << "!</h1>\n"
                << "  </body>\n"
                << "</html>\n";

            return response.str();
        }
};

TestWebView test_web_view;

WebRequestHandler::WebRequestHandler()
{
    // empty
}

WebRequestHandler::~WebRequestHandler()
{
    cleanup();
}

void
WebRequestHandler::init()
{

}

void
WebRequestHandler::add_route(const string & pattern, WebView & view)
{
    WebRequestRoute route;
    route.pattern.assign(pattern);
    route.view = &view;
    m_router.push_back(route);
}

WebView * 
WebRequestHandler::route(const string & uri) const
{
    return &test_web_view;
    WebView * result = nullptr;

    vector<WebRequestRoute>::const_iterator it = m_router.begin();
    for(; it != m_router.end(); it++)
    {
        regex pattern(it->pattern);
        if (regex_match(uri, pattern))
        {
            result = it->view;
            break;
        }
    }

    return result;
}

int
WebRequestHandler::run()
{
    // Backup the stdio streambufs
    streambuf * cin_streambuf  = cin.rdbuf();
    streambuf * cout_streambuf = cout.rdbuf();
    streambuf * cerr_streambuf = cerr.rdbuf();

    FCGX_Request request;

    FCGX_Init();
    FCGX_InitRequest(&request, 0, 0);

    while (FCGX_Accept_r(&request) == 0) {
        fcgi_streambuf cin_fcgi_streambuf(request.in);
        fcgi_streambuf cout_fcgi_streambuf(request.out);
        fcgi_streambuf cerr_fcgi_streambuf(request.err);

        cin.rdbuf(&cin_fcgi_streambuf);
        cout.rdbuf(&cout_fcgi_streambuf);
        cerr.rdbuf(&cerr_fcgi_streambuf);

        FcgiWebRequest wrapper(request);
        WebView * view = route(wrapper.uri());
        if (view)
        {
            cout << view->handle_request(wrapper);
        }

        // Note: the fcgi_streambuf destructor will auto flush
    }

    // restore stdio streambufs
    cin.rdbuf(cin_streambuf);
    cout.rdbuf(cout_streambuf);
    cerr.rdbuf(cerr_streambuf);

    return 0;
}

void
WebRequestHandler::cleanup()
{

}
