#include <OpenAI/OpenAIModel.h>

std::string OpenAI::OpenAIModel::GetModelName() noexcept
{
    return _modelName;
}