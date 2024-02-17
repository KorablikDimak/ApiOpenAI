#ifndef OpenAI_SpeakerH
#define OpenAI_SpeakerH

#include <OpenAI/OpenAIModel.h>
#include <OpenAI/Types/Voice.h>
#include <OpenAI/Types/ResponseFormat.h>

namespace OpenAI
{
    class Speaker final : public OpenAIModel
    {
    private:
        static const std::string MODEL_NAME;

        Voice _voice;
        ResponseFormat _responseFormat;
        float _speed;

    public:
        typedef std::shared_ptr<Speaker> Ptr;

        explicit Speaker(const OpenAIApi::Ptr& api);
        ~Speaker() override = default;

        std::string Speech(const std::string& text) const;

        void ChangeVoice(Voice voice);
        void ChangeResponseFormat(ResponseFormat format);
        void SetSpeed(float speed);
    };
}

#endif