#ifndef OpenAI_HttpContext_H
#define OpenAI_HttpContext_H

#include <boost/beast/http.hpp>

namespace OpenAI
{
    typedef boost::beast::http::empty_body EmptyBody;
    typedef boost::beast::http::string_body StringBody;
    typedef boost::beast::http::file_body FileBody;
    typedef boost::beast::http::buffer_body BufferBody;
    typedef boost::beast::http::dynamic_body DynamicBody;

    template<typename RequestBody, typename ResponseBody>
    class HttpContext
    {
    public:
        typedef boost::beast::http::request<RequestBody> HttpRequest;
        typedef boost::beast::http::response_parser<ResponseBody> HttpResponse;

        std::unique_ptr<HttpRequest> Request;
        std::unique_ptr<HttpResponse> Response;

        HttpContext()
        {
            Request = std::make_unique<HttpRequest>();
            Response = std::make_unique<HttpResponse>();
        }
        ~HttpContext() = default;
    };
}

#endif