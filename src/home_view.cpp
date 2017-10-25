#include "home_view.h"
#include "common/http_response.h"
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
    std::stringstream html;
    std::string content(request.content());

    if (content.length() == 0)
    {
        content = ", World!";
    }

    html << "<html>\n"
        << "  <head>\n"
        << "    <title>Hello, Nathan!</title>\n"
        << "  </head>\n"
        << "  <html>\n"
        << "    <h1>Home View</h1>\n"
        << "    <h2>Hello" << content << " from " << request.uri() << "!</h2>\n"
        << "  </html>\n"
        << "</html>\n";

    HttpResponse response = HttpResponse::OK();
    response.set_html(html.str());
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
