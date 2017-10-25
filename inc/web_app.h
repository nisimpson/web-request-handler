#ifndef WEB_APP_H
#define WEB_APP_H

#include "common/web_request_handler.h"
#include "home_view.h"
#include "api_view.h"
#include "error_view.h"

namespace web_gui
{
    class WebApp
    {
    public:
        WebApp();
        ~WebApp();
        
        bool init();
        bool run();
        bool cleanup();

    private:
        WebRequestHandler m_handler;
        HomeView m_home_view;
        ApiView m_api_view;
        ErrorView m_error_view;
    };
}

#endif // WEB_APP_H