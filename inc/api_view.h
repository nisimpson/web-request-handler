#ifndef API_VIEW_H
#define API_VIEW_H

#include "web_view.h"
#include <string>

namespace web_gui
{
    class ApiView : public WebView
    {
    public:
        ApiView();
        ~ApiView();

        std::string handle_request(WebRequest & request);
        std::string to_string();
    };
}

#endif // API_VIEW_H