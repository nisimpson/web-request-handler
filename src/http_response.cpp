#include "http_response.h"
#include <sstream>

using namespace web_gui;

class StatusCodeReason
{
public:
    StatusCodeReason()
    {
        _storage[100] = "Continue";
        _storage[101] = "Switching Protocols";
        _storage[200] = "OK";
        _storage[201] = "Created";
        _storage[202] = "Accepted";
        _storage[203] = "Non-Authoritative Information";
        _storage[204] = "No Content";
        _storage[205] = "Reset Content";
        _storage[206] = "Partial Content";
        _storage[300] = "Multiple Choices";
        _storage[301] = "Moved Permanently";
        _storage[302] = "Found";
        _storage[400] = "Bad Request";
        _storage[401] = "Unauthorized";
        _storage[403] = "Forbidden";
        _storage[404] = "Not Found";
        _storage[405] = "Method Not Allowed";
        _storage[406] = "Not Acceptable";
        _storage[500] = "Internal Server Error";
        _storage[501] = "Not Implemented";
        _storage[502] = "Bad Gateway";
        _storage[503] = "Service Unavailable";
        _storage[504] = "Gateway Time-out";
        _storage[505] = "HTTP Version Not Supported";
    }

    char * reason(HttpStatusCode code) const
    {
        return _storage[code];
    }

private:
    char * _storage[600];
};

const StatusCodeReason status_code_reason;

HttpResponse::HttpResponse(HttpStatusCode code)
    : WebResponse()
    , m_status_code(code)
{

}

HttpResponse::HttpResponse() : HttpResponse(HTTP_OK) { }

std::string
HttpResponse::data() const
{

}

HttpStatusCode
HttpResponse::status_code() const
{
    return m_status_code;
}

std::string
HttpResponse::status_line() const
{

}

void
HttpResponse::set_header(const std::string & key, const std::string & value)
{

}

std::string
header(const std::string & key)
{

}

std::string body() const
{

}

void
set_body(const std::string & body)
{

}
