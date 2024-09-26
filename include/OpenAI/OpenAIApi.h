#ifndef OpenAI_OpenAIApi_H
#define OpenAI_OpenAIApi_H

#include <OpenAI/Types/ChatCompletionsRequest.h>
#include <OpenAI/Types/ChatCompletionsResponse.h>
#include <OpenAI/Types/TranscriptionsRequest.h>
#include <OpenAI/Types/FileInfo.h>
#include <OpenAI/Types/CreateImageRequest.h>
#include <OpenAI/Types/CreateImageResponse.h>
#include <OpenAI/Types/SpeechRequest.h>

namespace OpenAI
{
    class OpenAIApi
    {
    private:
        static const std::string_view HOST;
        static const unsigned int HTTP_VERSION;

        std::string _token;

        [[nodiscard]]
        std::optional<ExtendedCpp::Json> Get(const std::string& methodName) const noexcept;
        [[nodiscard]]
        std::optional<ExtendedCpp::Json> Post(const std::string& methodName, const ExtendedCpp::Json& params) const noexcept;

    public:
        typedef std::shared_ptr<OpenAIApi> Ptr;

        explicit OpenAIApi(const std::string& token) noexcept;
        ~OpenAIApi() = default;

        [[nodiscard]]
        ChatCompletionsResponse::Ptr ChatCompletions(const ChatCompletionsRequest::Ptr& completionsRequest) const noexcept;
        [[nodiscard]]
        FileInfo::Ptr UploadFile(const std::string& filePath) const noexcept = delete;
        [[nodiscard]]
        FileInfo::Ptr DeleteFile(const std::string& fileId) const noexcept;
        [[nodiscard]]
        std::string CreateTranscription(const TranscriptionsRequest::Ptr& transcriptionsRequest) const noexcept;
        [[nodiscard]]
        CreateImageResponse::Ptr CreateImage(const CreateImageRequest::Ptr& createImageRequest) const noexcept;
        [[nodiscard]]
        std::string Speech(const SpeechRequest::Ptr& speechRequest) const noexcept;
    };
}

#endif