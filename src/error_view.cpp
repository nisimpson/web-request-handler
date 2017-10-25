#include "error_view.h"
#include "common/http_response.h"
#include <fstream>
#include <sstream>

using namespace web_gui;

ErrorView::ErrorView() : WebView() { }

ErrorView::~ErrorView() { }

std::string
ErrorView::handle_request(WebRequest & request)
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
ErrorView::to_string() const
{
    return "ErrorView";
}
