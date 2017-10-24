#ifndef HOME_VIEW_H
#define HOME_VIEW_H

#include "web_view.h"

namespace web_gui
{
    class HomeView : public WebView
    {
    public:
        HomeView();
        ~HomeView();

        std::string handle_request(WebRequest & request);
        std::string to_string();

    private:
        std::string show_test_page(WebRequest & request);
        std::string show_home_page(WebRequest & request);
    };
}

#endif // HOME_VIEW_H