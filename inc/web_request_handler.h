#ifndef WEB_REQUEST_HANDLER_H
#define WEB_REQUEST_HANDLER_H

#include <string>
#include <vector>
#include "web_view.h"

namespace web_gui
{
    typedef struct {
        std::string pattern;
        WebView * view;
    } WebRequestRoute;

    class WebRequestHandler
    {
    public:
        WebRequestHandler();
        ~WebRequestHandler();
        void init();
        int run();
        void cleanup();
        void add_route(const std::string & pattern, WebView & view);
        WebView * route(const std::string & uri) const;
    private:
        std::vector<WebRequestRoute> m_router;
    };
}

#endif // WEB_REQUEST_HANDLER_H
