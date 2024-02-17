#ifndef OpenAI_Dalle_H
#define OpenAI_Dalle_H

#include <memory>

#include <OpenAI/OpenAIModel.h>
#include <OpenAI/Types/Size.h>

namespace OpenAI
{
    class Dalle final : public OpenAIModel
    {
    private:
        static const std::string MODEL_NAME;
        static const std::string RESPONSE_FORMAT;
        static const unsigned char N;

        std::string _user;
        Size _size;

    public:
        typedef std::shared_ptr<Dalle> Ptr;

        explicit Dalle(const OpenAIApi::Ptr& api, const std::string& user = "");
        ~Dalle() override = default;

        [[nodiscard]]
        std::string CreateImage(const std::string& prompt) const;

        void SetSize(Size size);
    };
}

#endif