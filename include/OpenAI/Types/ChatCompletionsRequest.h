#ifndef OpenAI_ChatRequestBody_H
#define OpenAI_ChatRequestBody_H

#include <map>
#include <vector>
#include <cstdint>

#include <OpenAI/Types/Message.h>

namespace OpenAI
{
    class ChatCompletionsRequest
    {
    public:
        typedef std::shared_ptr<ChatCompletionsRequest> Ptr;

        std::string model;
        std::vector<Message::Ptr> messages;
        float temperature;
        float top_p;
        unsigned char n;
        bool stream;
        std::string stop;
        std::int16_t max_tokens;
        float presence_penalty;
        float frequency_penalty;
        std::map<std::string, signed char> logit_bias; // do not use!
        std::string user;
    };

    inline void to_json(ExtendedCpp::Json& json, const ChatCompletionsRequest::Ptr& object) noexcept
    {
        VALUE_TO_JSON(model)
        OBJECTS_TO_JSON(messages)
        VALUE_TO_JSON(temperature)
        VALUE_TO_JSON(top_p)
        VALUE_TO_JSON(n)
        VALUE_TO_JSON(stream)
        if (!object->stop.empty()) VALUE_TO_JSON(stop)
        if (object->max_tokens != 0) VALUE_TO_JSON(max_tokens)
        VALUE_TO_JSON(presence_penalty)
        VALUE_TO_JSON(frequency_penalty)
        // TODO logit_bias
        if (!object->user.empty()) VALUE_TO_JSON(user)
    }
}

#endif