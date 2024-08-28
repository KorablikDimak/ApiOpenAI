#ifndef OpenAI_SpeechRequest_H
#define OpenAI_SpeechRequest_H

#include <Json/Json.h>

namespace OpenAI
{
    class SpeechRequest
    {
    public:
        typedef std::shared_ptr<SpeechRequest> Ptr;

        std::string model;
        std::string input;
        std::string voice;
        std::string response_format;
        float speed;
        std::string directory;
    };

    inline void to_json(Json::Json& json, const SpeechRequest::Ptr& object) noexcept
    {
        VALUE_TO_JSON(model)
        VALUE_TO_JSON(input)
        VALUE_TO_JSON(voice)
        VALUE_TO_JSON(response_format)
        VALUE_TO_JSON(speed)
    }
}

#endif