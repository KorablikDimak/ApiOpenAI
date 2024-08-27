#ifndef OpenAI_Whisper_H
#define OpenAI_Whisper_H

#include <OpenAI/OpenAIModel.h>

namespace OpenAI
{
    class Whisper final : public OpenAIModel
    {
    private:
        static const std::string MODEL_NAME;

        float _temperature;

    public:
        typedef std::shared_ptr<Whisper> Ptr;

        explicit Whisper(const OpenAIApi::Ptr& api) noexcept;
        ~Whisper() override = default;

        [[nodiscard]]
        std::string Transcript(const std::string& filePath) const noexcept;

        void SetTemperature(float temperature) noexcept;
    };
}

#endif