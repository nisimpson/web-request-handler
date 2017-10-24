#include "api_view.h"
#include "http_response.h"
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
    HttpResponse response = HttpResponse::httpOK();
    std::stringstream stream;
    stream << "<html>"
        << "<h1>Hello, Api!</h1>"
        << "</html>";

    response.set_body(stream.str());    
    return response.data();
}

std::string
ApiView::to_string()
{
    return "ApiView";
}