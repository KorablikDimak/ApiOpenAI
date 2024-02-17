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
        explicit OpenAI(const std::string& token);
        ~OpenAI() = default;

        [[nodiscard]]
        OpenAIModel::Ptr GptTurboSession(const std::string& user = "", const std::string& name = "") const;
        [[nodiscard]]
        OpenAIModel::Ptr WhisperSession() const;
        [[nodiscard]]
        OpenAIModel::Ptr DalleSession(const std::string& user = "") const;
        [[nodiscard]]
        OpenAIModel::Ptr SpeakerSession() const;
    };
}

#endif