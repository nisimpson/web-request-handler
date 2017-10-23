#ifndef WEB_REQUEST_HANDLER_H
#define WEB_REQUEST_HANDLER_H

#include <string>
#include <map>

namespace web_gui
{
    class WebRequest
    {
    public:
        virtual ~WebRequest() { /* empty */ }
        virtual std::string content() = 0;
        virtual std::string uri() const = 0;
        virtual std::string query_string() const = 0;
        virtual std::string method() const = 0;
        virtual std::string user_agent() const = 0;
        static std::map<std::string, std::string> parse_query_string(const std::string & query);
    };

    class WebView
    {
    public:
        virtual ~WebView() { /* empty */ }
        virtual std::string handle_request(WebRequest & request) = 0;
    };

    class WebRequestHandler
    {
    public:
        WebRequestHandler();
        ~WebRequestHandler();
        void init();
        int run();
        void cleanup();
        void add_route(std::string pattern, WebView & view);
        WebView * route(std::string uri) const;
    private:
        std::map<std::string, WebView *> m_router;
    };
}

#endif // WEB_REQUEST_HANDLER_H
