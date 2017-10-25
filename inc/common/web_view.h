#ifndef WEB_VIEW_H
#define WEB_VIEW_H

#include <string>
#include "common/web_request.h"

namespace web_gui
{
    class WebView
    {
    public:
        virtual ~WebView() { /* empty */ }
        virtual std::string handle_request(WebRequest & request) = 0;
        virtual std::string to_string() { return ""; }
    };
}

#endif // WEB_VIEW_H