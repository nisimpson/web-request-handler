#ifndef WEB_REQUEST_H
#define WEB_REQUEST_H

#include <string>
#include <map>

namespace web_gui
{
    class WebRequest
    {
    public:
        virtual ~WebRequest() { /* empty */ }
        virtual std::string content() = 0;
        virtual std::string uri() const = 0;
        virtual std::string query_string() const = 0;
        virtual std::string method() const = 0;
        virtual std::string user_agent() const = 0;
        virtual std::string document_root() const = 0;
        static std::map<std::string, std::string> parse_query_string(const std::string & query);
    };

}

#endif // WEB_REQUEST_H