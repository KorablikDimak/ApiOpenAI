#include <fstream>
#include <algorithm>

#include <OpenAI/OpenAIApi.h>
#include <OpenAI/HttpsClient.h>
#include <Common/Random.h>

constexpr std::string OpenAI::OpenAIApi::HOST = "api.openai.com";
constexpr unsigned int OpenAI::OpenAIApi::HTTP_VERSION = 11;

OpenAI::OpenAIApi::OpenAIApi(const std::string& token) noexcept
{
    _token = token;
}

std::optional<Json::Json> OpenAI::OpenAIApi::Get(const std::string& methodName) const noexcept
{
    const auto httpContext = std::make_shared<HttpContext<EmptyBody, StringBody>>();
    httpContext->Request->version(HTTP_VERSION);
    httpContext->Request->method_string("GET");
    httpContext->Request->set(boost::beast::http::field::host, HOST);
    httpContext->Request->target("/v1/" + methodName);
    httpContext->Request->set(boost::beast::http::field::authorization, "Bearer " + _token);

    try
    {
        HttpsClient::SendHttpsAsync(httpContext, UseSNI::ON);
        return Json::Json::parse(httpContext->Response->get().body());
    }
    catch (...)
    { return std::nullopt; }
}

std::optional<Json::Json> OpenAI::OpenAIApi::Post(const std::string& methodName, const Json::Json& params) const noexcept
{
    const auto httpContext = std::make_shared<HttpContext<StringBody, StringBody>>();
    httpContext->Request->version(HTTP_VERSION);
    httpContext->Request->method_string("POST");
    httpContext->Request->set(boost::beast::http::field::host, HOST);
    httpContext->Request->target("/v1/" + methodName);
    httpContext->Request->set(boost::beast::http::field::authorization, "Bearer " + _token);

    httpContext->Request->set(boost::beast::http::field::content_type, "application/json");
    httpContext->Request->body() = std::move(params.dump());
    httpContext->Request->prepare_payload();

    try
    {
        HttpsClient::SendHttpsAsync(httpContext, UseSNI::ON);
        return Json::Json::parse(httpContext->Response->get().body());
    }
    catch (...)
    { return std::nullopt; }
}

OpenAI::ChatCompletionsResponse::Ptr OpenAI::OpenAIApi::ChatCompletions(const ChatCompletionsRequest::Ptr& completionsRequest) const noexcept
{
    if (!completionsRequest) return { nullptr };
    const Json::Json requestBody = completionsRequest;

    const auto postResult = Post("chat/completions", requestBody);
    if (!postResult.has_value()) return { nullptr };
    const Json::Json& responseBody = postResult.value();

    auto completionsResponse = std::make_shared<ChatCompletionsResponse>();
    *completionsResponse = std::move(responseBody.get<ChatCompletionsResponse>());
    return completionsResponse;
}

#undef DeleteFile

OpenAI::FileInfo::Ptr OpenAI::OpenAIApi::DeleteFile(const std::string& fileId) const noexcept
{
    const auto httpContext = std::make_shared<HttpContext<EmptyBody, StringBody>>();
    httpContext->Request->version(HTTP_VERSION);
    httpContext->Request->method_string("DELETE");
    httpContext->Request->set(boost::beast::http::field::host, HOST);
    httpContext->Request->target("/v1/files/" + fileId);
    httpContext->Request->set(boost::beast::http::field::authorization, "Bearer " + _token);

    try
    { HttpsClient::SendHttpsAsync(httpContext, UseSNI::ON); }
    catch (...)
    { return { nullptr }; }

    const Json::Json responseBody = Json::Json::parse(httpContext->Response->get().body());

    auto fileInfo = std::make_shared<FileInfo>();
    *fileInfo = std::move(responseBody.get<FileInfo>());
    return fileInfo;
}

#define DeleteFile __MINGW_NAME_AW(DeleteFile)

std::string OpenAI::OpenAIApi::CreateTranscription(const TranscriptionsRequest::Ptr& transcriptionsRequest) const noexcept
{
    try
    {
        if (!transcriptionsRequest) return {};
        std::stringstream fileContent;
        std::ifstream file(transcriptionsRequest->file.c_str(), std::ios::binary);
        if (!file.is_open()) return {};
        fileContent << file.rdbuf();

        const std::string guid = Common::RandomString(12);
        std::string body = "--" + guid + "\r\n"
                           "Content-Disposition: form-data; name=\"file\"; filename=\""
                           + guid + ".mp3\"\r\n"
                           "Content-Type: application/octet-stream\r\n\r\n"
                           + fileContent.str() + "\r\n"
                           "--" + guid + "\r\n"
                           "Content-Disposition: form-data; name=\"model\"\r\n"
                           "Content-Type: text/plain\r\n\r\n"
                           + transcriptionsRequest->model + "\r\n"
                           "--" + guid + "\r\n"
                           "Content-Disposition: form-data; name=\"temperature\"\r\n"
                           "Content-Type: text/plain\r\n\r\n"
                           + std::to_string(transcriptionsRequest->temperature) + "\r\n"
                           "--" + guid + "--\r\n";

        auto httpContext = std::make_shared<HttpContext<StringBody, StringBody>>();
        httpContext->Request->version(HTTP_VERSION);
        httpContext->Request->method_string("POST");
        httpContext->Request->set(boost::beast::http::field::host, HOST);
        httpContext->Request->target("/v1/audio/transcriptions");
        httpContext->Request->set(boost::beast::http::field::authorization, "Bearer " + _token);

        httpContext->Request->set(boost::beast::http::field::content_type, "multipart/form-data; boundary=" + guid);
        httpContext->Request->body() = std::move(body);
        httpContext->Request->prepare_payload();

        HttpsClient::SendHttpsAsync(httpContext, UseSNI::ON);

        const Json::Json responseBody = Json::Json::parse(httpContext->Response->get().body());
        if (!responseBody.contains("text")) return {};
        return responseBody.at("text").get<std::string>();
    }
    catch (...)
    {
        return {};
    }
}

OpenAI::CreateImageResponse::Ptr OpenAI::OpenAIApi::CreateImage(const CreateImageRequest::Ptr& createImageRequest) const noexcept
{
    if (!createImageRequest) return { nullptr };
    const Json::Json requestBody = createImageRequest;

    const auto postResult = Post("images/generations", requestBody);
    if (!postResult.has_value()) return { nullptr };
    const Json::Json& responseBody = postResult.value();

    auto createImageResponse = std::make_shared<CreateImageResponse>();
    *createImageResponse = std::move(responseBody.get<CreateImageResponse>());
    return createImageResponse;
}

std::string OpenAI::OpenAIApi::Speech(const SpeechRequest::Ptr& speechRequest) const noexcept
{
    try
    {
        if (!speechRequest) return {};
        std::string filePath;

        if (speechRequest->directory.empty())
            filePath = Common::RandomString(16) + "." + speechRequest->response_format;
        else if (speechRequest->directory.ends_with("/"))
            filePath = speechRequest->directory + Common::RandomString(16) + "." + speechRequest->response_format;
        else
            filePath = speechRequest->directory + "/" + Common::RandomString(16) + "." + speechRequest->response_format;

        const auto httpContext = std::make_shared<HttpContext<StringBody, StringBody>>();

        httpContext->Request->version(HTTP_VERSION);
        httpContext->Request->method_string("POST");
        httpContext->Request->set(boost::beast::http::field::host, HOST);
        httpContext->Request->target("/v1/audio/speech");
        httpContext->Request->set(boost::beast::http::field::authorization, "Bearer " + _token);

        httpContext->Request->set(boost::beast::http::field::content_type, "application/json");
        const Json::Json json = speechRequest;
        httpContext->Request->body() = std::move(json.dump());
        httpContext->Request->prepare_payload();

        try
        { HttpsClient::SendHttpsAsync(httpContext, UseSNI::ON); }
        catch (...)
        { return {}; }

        const std::string responseResult = httpContext->Response->get().body();
        std::ofstream audiofile(filePath, std::ios::binary);
        audiofile.write(responseResult.data(), static_cast<long long>(responseResult.size()));

        return filePath;
    }
    catch (...)
    {
        return {};
    }
}