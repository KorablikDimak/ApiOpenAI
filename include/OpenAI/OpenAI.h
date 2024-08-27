#ifndef OpenAI_OpenAI_H
#define OpenAI_OpenAI_H

#include <OpenAI/OpenAIApi.h>
#include <OpenAI/OpenAIModel.h>

namespace OpenAI
{
    class OpenAI
    {
    private:
        OpenAIApi::Ptr _api;

    public:
        explicit OpenAI(const std::string& token) noexcept;
        ~OpenAI() = default;

        [[nodiscard]]
        OpenAIModel::Ptr GptTurboSession(const std::string& user = "", const std::string& name = "") const noexcept;
        [[nodiscard]]
        OpenAIModel::Ptr WhisperSession() const noexcept;
        [[nodiscard]]
        OpenAIModel::Ptr DalleSession(const std::string& user = "") const noexcept;
        [[nodiscard]]
        OpenAIModel::Ptr SpeakerSession() const noexcept;
    };
}

#endif