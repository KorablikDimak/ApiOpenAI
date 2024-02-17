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
        static const std::string HOST;
        static const unsigned int HTTP_VERSION;

        std::string _token;

        [[nodiscard]]
        Json::Json Get(const std::string& methodName) const;
        [[nodiscard]]
        Json::Json Post(const std::string& methodName, const Json::Json& params) const;

    public:
        typedef std::shared_ptr<OpenAIApi> Ptr;

        explicit OpenAIApi(const std::string& token) noexcept;
        ~OpenAIApi() noexcept = default;

        [[nodiscard]]
        ChatCompletionsResponse::Ptr ChatCompletions(const ChatCompletionsRequest::Ptr& completionsRequest) const;
        [[nodiscard]]
        FileInfo::Ptr UploadFile(const std::string& filePath) const = delete;
        [[nodiscard]]
        FileInfo::Ptr DeleteFile(const std::string& fileId) const;
        [[nodiscard]]
        std::string CreateTranscription(const TranscriptionsRequest::Ptr& transcriptionsRequest) const;
        [[nodiscard]]
        CreateImageResponse::Ptr CreateImage(const CreateImageRequest::Ptr& createImageRequest) const;
        [[nodiscard]]
        std::string Speech(const SpeechRequest::Ptr& speechRequest) const;
    };
}

#endif