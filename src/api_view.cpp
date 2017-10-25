#include "api_view.h"
#include "error_view.h"
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
    ErrorView error;
    return error.handle_request(request);
}

std::string
ApiView::to_string() const
{
    return "ApiView";
}