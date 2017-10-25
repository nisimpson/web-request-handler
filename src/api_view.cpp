#include "api_view.h"
#include "common/http_response.h"
#include <sstream>
#include <iostream>
#include <fstream>

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
    return show_error_page(request);
}

std::string
ApiView::show_error_page(WebRequest & request)
{
    HttpResponse response = HttpResponse::Error404();
    std::ifstream errorPage;
    std::stringstream stream;
    std::string line;
    errorPage.open(request.document_root() + "/404.html");
    if(errorPage.is_open())
    {
        while(std::getline(errorPage, line))
        {
            stream << line << "\n";
        }
        response.set_html(stream.str());
        errorPage.close();
    }

    return response.data();
}

std::string
ApiView::to_string()
{
    return "ApiView";
}