#ifndef WEB_RESPONSE_H
#define WEB_RESPONSE_H

#include <string>

namespace web_gui
{
    class WebResponse
    {
    public:
        virtual ~WebResponse() { /* empty */ }
        virtual std::string data() const = 0;
    };
}

#endif // WEB_RESPONSE