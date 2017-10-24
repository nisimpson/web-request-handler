#ifndef WEB_REQUEST_HANDLER_H
#define WEB_REQUEST_HANDLER_H

#include <string>
#include <map>
#include "web_view.h"

namespace web_gui
{
    class WebRequestHandler
    {
    public:
        WebRequestHandler();
        ~WebRequestHandler();
        void init();
        int run();
        void cleanup();
        void add_route(std::string pattern, WebView & view);
        WebView * route(std::string uri) const;
    private:
        std::map<std::string, WebView *> m_router;
    };
}

#endif // WEB_REQUEST_HANDLER_H
