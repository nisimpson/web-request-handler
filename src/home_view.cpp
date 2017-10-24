#include "home_view.h"
#include "http_response.h"
#include <sstream>

using namespace web_gui;

HomeView::HomeView()
{

}

HomeView::~HomeView()
{

}

std::string
HomeView::handle_request(WebRequest & request)
{
    return show_test_page(request);
}

std::string
HomeView::show_test_page(WebRequest & request)
{
    std::stringstream body;
    std::string content(request.content());

    if (content.length() == 0)
    {
        content = ", World!";
    }

    body << "<html>\n"
        << "  <head>\n"
        << "    <title>Hello, Nathan!</title>\n"
        << "  </head>\n"
        << "  <body>\n"
        << "    <h1>Home View</h1>\n"
        << "    <h2>Hello" << content << " from " << request.uri() << "!</h2>\n"
        << "  </body>\n"
        << "</html>\n";

    HttpResponse response = HttpResponse::httpOK();
    response.set_body(body.str());
    return response.data();
}

std::string
HomeView::show_home_page(WebRequest & request)
{
    return "";
}

std::string
HomeView::to_string()
{
    return "HomeView";
}
