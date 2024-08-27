#ifndef OpenAI_FileInfo_H
#define OpenAI_FileInfo_H

#include <Json/Json.h>

namespace OpenAI
{
    class FileInfo
    {
    public:
        typedef std::shared_ptr<FileInfo> Ptr;

        std::string id;
        std::string object;
        std::int32_t bytes;
        std::int64_t created_at;
        std::string filename;
        std::string purpose;
        bool deleted;
    };

    inline void from_json(const Json::Json& json, FileInfo& object) noexcept
    {
        VALUE_FROM_JSON(id)
        VALUE_FROM_JSON(object)
        VALUE_FROM_JSON(bytes)
        VALUE_FROM_JSON(created_at)
        VALUE_FROM_JSON(filename)
        VALUE_FROM_JSON(purpose)
        VALUE_FROM_JSON(deleted)
    }
}

#endif