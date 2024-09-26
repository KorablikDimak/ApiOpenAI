#ifndef OpenAI_CreateImageResponse_H
#define OpenAI_CreateImageResponse_H

#include <ExtendedCpp/Json.h>

namespace OpenAI
{
    class CreateImageResponse
    {
    public:
        typedef std::shared_ptr<CreateImageResponse> Ptr;

        std::int64_t created;
        std::vector<std::string> data;
    };

    inline void from_json(const ExtendedCpp::Json& json, CreateImageResponse& object) noexcept
    {
        VALUE_FROM_JSON(created)

        if (json.contains("data"))
            for (const ExtendedCpp::Json& url : json.at("data"))
                if (url.contains("url"))
                    object.data.push_back(url.at("url").get<std::string>());
    }
}

#endif