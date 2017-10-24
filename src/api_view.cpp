#include "api_view.h"
#include <sstream>

using namespace web_gui;

ApiView::ApiView()
{

}

ApiView::~ApiView()
{

}

std::string
ApiView::handle_request(WebRequest & request)
{
    std::stringstream stream;
    stream << "<html>"
        << "<h1>Hello, Api!</h1>"
        << "</html>";

    return stream.str();
}

std::string
ApiView::to_string()
{
    return "ApiView";
}