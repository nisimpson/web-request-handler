#ifndef ERROR_VIEW_H
#define ERROR_VIEW_H

#include "common/web_view.h"
#include "common/web_request.h"
#include <string>

namespace web_gui
{
    class ErrorView : public WebView
    {
    public:
        ErrorView();
        ~ErrorView();

        std::string handle_request(WebRequest & request);
        std::string to_string() const;
    };
}

#endif // ERROR_VIEW_H