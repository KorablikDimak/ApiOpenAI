#ifndef OpenAI_Message_H
#define OpenAI_Message_H

#include <ExtendedCpp/Json.h>

namespace OpenAI
{
    class Message
    {
    public:
        typedef std::shared_ptr<Message> Ptr;

        std::string role;
        std::string content;
        std::string name;
    };

    inline void to_json(ExtendedCpp::Json& json, const Message::Ptr& object) noexcept
    {
        VALUE_TO_JSON(role)
        VALUE_TO_JSON(content)
        if (!object->name.empty()) VALUE_TO_JSON(name)
    }
}

#endif