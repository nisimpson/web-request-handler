#include "api_view.h"
#include "error_view.h"
#include "common/http_response.h"
#include "common/json.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>

using namespace web_gui;

typedef struct _MockCvtItem {
    std::string key;
    std::string value;
} MockCvtItem;

ApiView::ApiView()
{

}

ApiView::~ApiView()
{

}

std::string
ApiView::handle_request(WebRequest & request)
{
    // only handle GET requests
    if (request.method() == "GET")
    {
        // TODO: This is insufficient to check for a valid CVT endpoint
        // but will suffice for the prototype.
        if (request.uri().find("/cvt") != std::string::npos)
        {
            return handle_cvt_request(request);
        }
    }

    return show_error_page(request);
}

std::string
ApiView::show_error_page(WebRequest & request)
{
    ErrorView error;
    return error.handle_request(request);
}

std::string
ApiView::handle_cvt_request(WebRequest & request)
{
    // we're going to pretend that we've made a request
    // to the CVT server and got a list of current values.
    std::vector<MockCvtItem> items;
    for (int i = 0; i < 10; i++)
    {
        MockCvtItem item;
        item.key = "Some CVT Key #" + std::to_string(i + 1);
        item.value = "Some Value";
        items.push_back(item);
    }

    // now create some JSON...
    JsonNode * root = json_mkobject();
    JsonNode * arr = json_mkarray();
    json_append_member(root, "items", arr);

    std::vector<MockCvtItem>::iterator it;
    for (it = items.begin(); it != items.end(); it++)
    {
        JsonNode * item = json_mkobject();
        json_append_member(item, "key", json_mkstring(it->key.c_str()));;
        json_append_member(item, "value", json_mkstring(it->value.c_str()));;
        json_append_element(arr, item);
    }

    HttpResponse response = HttpResponse::OK();
    response.set_header("Content-Type", "text/json");
    response.set_html(json_encode(root));
    
    // clean up and return response
    json_delete(root);
    return response.data();
}

std::string
ApiView::to_string() const
{
    return "ApiView";
}