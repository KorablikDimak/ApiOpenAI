#ifndef OpenAI_OpenAIModel_H
#define OpenAI_OpenAIModel_H

#include <OpenAI/OpenAIApi.h>

namespace OpenAI
{
    class OpenAIModel
    {
    protected:
        OpenAIApi::Ptr _api;
        std::string _modelName;

    public:
        typedef std::shared_ptr<OpenAIModel> Ptr;

        OpenAIModel() noexcept = default;
        virtual ~OpenAIModel() = default;
        std::string GetModelName() noexcept;
    };
}

#endif