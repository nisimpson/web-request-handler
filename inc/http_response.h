#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H

#include "web_response.h"
#include <string>
#include <map>

namespace web_gui
{
    typedef enum _HttpStatusCode {
        
        HTTP_CONTINUE = 100,
        HTTP_SWITCH_PROTOCOL = 101,
        
        HTTP_OK = 200,
        HTTP_CREATED = 201,
        HTTP_ACCEPTED = 202,
        HTTP_INFO = 203,
        HTTP_NO_CONTENT = 204,
        HTTP_RESET = 205,
        HTTP_PARTIAL = 206,
        
        HTTP_MULTIPLE_CHOICE = 300,
        HTTP_MOVED = 301,
        HTTP_FOUND = 302,

        HTTP_BAD_REQUEST = 400,
        HTTP_UNAUTHORIZED = 401,
        HTTP_FORBIDDEN = 403,
        HTTP_NOT_FOUND = 404,
        HTTP_METHOD_NOT_ALLOWED = 405,
        HTTP_NOT_ACCEPTABLE = 406,

        HTTP_INTERNAL_ERROR = 500,
        HTTP_NOT_IMPLEMENTED = 501,
        HTTP_BAD_GATEWAY = 502,
        HTTP_SERVICE_UNAVAILABLE = 503,
        HTTP_GATEWAY_TIMEOUT = 504,
        HTTP_VERSION_NOT_SUPPORTED = 505

    } HttpStatusCode;
    
    class HttpResponse : public WebResponse
    {
    public:
        HttpResponse(HttpStatusCode code);
        ~HttpResponse();

        // WebResponse implementation
        virtual std::string data() const;
        
        virtual HttpStatusCode status_code() const;
        
        virtual std::string status_line() const;
        virtual void set_header(const std::string & key, const std::string & value);
        virtual std::string header(const std::string & key);
        
        virtual std::string body() const;
        virtual void set_body(const std::string & body);

        static HttpResponse httpOK();
        static HttpResponse http404();

    private:
        std::map<std::string, std::string> m_headers;
        std::string m_body;
        HttpStatusCode m_status_code;
    };
}

#endif  // HTTP_RESPONSE_H