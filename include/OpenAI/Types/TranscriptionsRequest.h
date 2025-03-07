#ifndef OpenAI_TranscriptionsRequest_H
#define OpenAI_TranscriptionsRequest_H

#include <ExtendedCpp/Json.h>

namespace OpenAI
{
    class TranscriptionsRequest
    {
    public:
        typedef std::shared_ptr<TranscriptionsRequest> Ptr;

        std::string file;
        std::string model;
        std::string prompt;
        std::string response_format;
        float temperature;
        std::string language;
    };

    inline void to_json(ExtendedCpp::Json& json, const TranscriptionsRequest::Ptr& object) noexcept
    {
        VALUE_TO_JSON(file)
        VALUE_TO_JSON(model)
        if (!object->prompt.empty()) VALUE_TO_JSON(prompt)
        if (!object->response_format.empty()) VALUE_TO_JSON(response_format)
        VALUE_TO_JSON(temperature)
        if (!object->language.empty()) VALUE_TO_JSON(temperature)
    }
}

#endif