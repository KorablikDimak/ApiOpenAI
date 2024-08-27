#ifndef OpenAI_ChatResponseBody_H
#define OpenAI_ChatResponseBody_H

#include <OpenAI/Types/Usage.h>

namespace OpenAI
{
    class ChatCompletionsResponse
    {
    public:
        typedef std::shared_ptr<ChatCompletionsResponse> Ptr;

        std::string id;
        std::string object;
        std::int64_t created;
        std::int16_t index;
        std::string role;
        std::string content;
        std::string name;
        std::string finish_reason;
        Usage::Ptr usage;
    };

    inline void from_json(const Json::Json& json, ChatCompletionsResponse& object) noexcept
    {
        VALUE_FROM_JSON(id)
        VALUE_FROM_JSON(object)
        VALUE_FROM_JSON(created)

        if (json.contains("choices"))
        {
            object.index = json.at("choices")[0].value<std::int16_t>("index", 0);
            if (json.at("choices")[0].contains("message"))
            {
                object.role = json.at("choices")[0].at("message").value<std::string>("role", "");
                object.content = json.at("choices")[0].at("message").value<std::string>("content", "");
                object.name = json.at("choices")[0].at("message").value<std::string>("name", "");
            }
            object.finish_reason = json.at("choices")[0].value<std::string>("finish_reason", "");
        }

        OBJECT_FROM_JSON(usage)
    }
}

#endif