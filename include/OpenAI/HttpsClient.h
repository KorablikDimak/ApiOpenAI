#ifndef OpenAI_HttpsClient_H
#define OpenAI_HttpsClient_H

#include <boost/asio/ssl/context.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <boost/asio/ssl/host_name_verification.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/co_spawn.hpp>
#include <boost/beast/core/flat_buffer.hpp>
#include <boost/asio/detached.hpp>

#include <OpenAI/HttpContext.h>

namespace OpenAI
{
    enum class UseSNI
    {
        OFF,
        ON
    };

    typedef boost::asio::io_service Service;
    typedef boost::asio::ssl::context SslContext;
    typedef boost::asio::ip::tcp::socket Socket;
    typedef boost::asio::ssl::stream<Socket> SslSocket;
    typedef boost::asio::ip::tcp::resolver Resolver;

    class HttpsClient
    {
    public:
        HttpsClient() = default;
        ~HttpsClient() = default;

        template<typename RequestBody, typename ResponseBody>
        static void SendHttpsAsync(const std::shared_ptr<HttpContext<RequestBody, ResponseBody>>& context, const UseSNI useSNI = UseSNI::OFF)
        {
            Service service;
            SslContext sslContext(SslContext::tlsv13_client);
            SslSocket sslSocket(service, sslContext);

            if (useSNI == UseSNI::ON)
            {
                SSL_set_tlsext_host_name(sslSocket.native_handle(), std::string((*context->Request)[boost::beast::http::field::host]).c_str());
                sslSocket.set_verify_callback(boost::asio::ssl::host_name_verification((*context->Request)[boost::beast::http::field::host]));
            }

            Resolver resolver(service);
            auto ip = resolver.resolve((*context->Request)[boost::beast::http::field::host], "443");

        #ifdef BOOST_ASIO_HAS_CO_AWAIT
            boost::asio::co_spawn(service, [&sslSocket, &ip, context]()->boost::asio::awaitable<void>
            {
                co_await boost::asio::async_connect(sslSocket.lowest_layer(), ip, boost::asio::use_awaitable);
                co_await sslSocket.async_handshake(boost::asio::ssl::stream_base::client, boost::asio::use_awaitable);
                co_await boost::beast::http::async_write(sslSocket, *context->Request, boost::asio::use_awaitable);

                boost::beast::flat_buffer buffer;
                while (!context->Response->is_done())
                    co_await boost::beast::http::async_read_some(sslSocket, buffer, *context->Response, boost::asio::use_awaitable);
            }, boost::asio::detached);
        #else
            boost::asio::connect(sslSocket.lowest_layer(), ip);
            sslSocket.handshake(boost::asio::ssl::stream_base::client);
            boost::beast::http::write(sslSocket, *context->Request);

            boost::beast::flat_buffer buffer;
            while (!context->Response->is_done())
                boost::beast::http::read_some(sslSocket, buffer, *context->Response);
        #endif

            service.run();
        }
    };
}

#endif