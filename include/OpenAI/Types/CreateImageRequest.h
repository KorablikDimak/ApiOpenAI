#ifndef OpenAI_CreateImageRequest_H
#define OpenAI_CreateImageRequest_H

#include <Json/Json.h>

namespace OpenAI
{
    class CreateImageRequest
    {
    public:
        typedef std::shared_ptr<CreateImageRequest> Ptr;

        std::string prompt;
        int n;
        std::string size;
        std::string response_format;
        std::string user;
    };

    inline void to_json(Json::Json& json, const CreateImageRequest::Ptr& object) noexcept
    {
        VALUE_TO_JSON(prompt)
        VALUE_TO_JSON(n)
        if (!object->size.empty()) VALUE_TO_JSON(size)
        if (!object->response_format.empty()) VALUE_TO_JSON(response_format)
        if (!object->user.empty()) VALUE_TO_JSON(user)
    }
}

#endif