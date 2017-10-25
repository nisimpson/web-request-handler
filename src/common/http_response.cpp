#include "common/http_response.h"
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

    std::string text(HttpStatusCode code) const
    {
        return _storage[code];
    }

private:
    std::string _storage[600];
};

const StatusCodeReason status_code_reason;

HttpResponse::HttpResponse(HttpStatusCode code)
    : WebResponse()
    , m_status_code(code)
{
    set_header("Content-Type", "text/html");
}

HttpResponse::~HttpResponse() { }

std::string
HttpResponse::data() const
{
    std::stringstream stream;
    std::map<std::string, std::string>::const_iterator it;
    
    stream << status_line() << "\r\n";
    for(it = m_headers.begin(); it != m_headers.end(); it++)
    {
        // ex. Content-Type: text/html
        stream << it->first << ": " << it->second << "\r\n"; 
    }

    stream << "\r\n" << html();
    return stream.str();
}

HttpStatusCode
HttpResponse::status_code() const
{
    return m_status_code;
}

std::string
HttpResponse::status_line() const
{
    std::stringstream stream;

    // ex. HTTP/1.1 200 OK
    stream << "HTTP/1.1 " 
        << status_code() << " "
        << status_code_reason.text(status_code());
    return stream.str();
}

void
HttpResponse::set_header(const std::string & key, const std::string & value)
{
    m_headers[key] = value;
}

std::string
HttpResponse::header(const std::string & key)
{
    return m_headers[key];
}

std::string
HttpResponse::html() const
{
    return m_html;
}

void
HttpResponse::set_html(const std::string & html)
{
    m_html = html;
    set_header("Content-Length", std::to_string(m_html.size()));
}

HttpResponse
HttpResponse::Error404()
{
    HttpResponse response(HTTP_NOT_FOUND);
    return response;
}

HttpResponse
HttpResponse::OK()
{
    HttpResponse response(HTTP_OK);
    return response;
}
