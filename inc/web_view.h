#ifndef WEB_VIEW_H
#define WEB_VIEW_H

#include <string>
#include "web_request.h"

namespace web_gui
{
    class WebView
    {
    public:
        virtual ~WebView() { /* empty */ }
        virtual std::string handle_request(WebRequest & request) = 0;
    };
}

#endif // WEB_VIEW_H