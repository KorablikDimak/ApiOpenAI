#include <OpenAI/Dalle.h>

const std::string OpenAI::Dalle::MODEL_NAME = "DALLE";
const std::string OpenAI::Dalle::RESPONSE_FORMAT = "url";
const unsigned char OpenAI::Dalle::N = 1;

OpenAI::Dalle::Dalle(const OpenAIApi::Ptr& api, const std::string& user)
{
    _api = api;
    _modelName = MODEL_NAME;

    _user = user;
    _size = Size::Large;
}

std::string OpenAI::Dalle::CreateImage(const std::string& prompt) const
{
    const auto createImageRequest = std::make_shared<CreateImageRequest>();
    createImageRequest->prompt = prompt;
    createImageRequest->n = N;
    switch (_size)
    {
        case Size::Mini:
            createImageRequest->size = "256x256";
            break;
        case Size::Medium:
            createImageRequest->size = "512x512";
            break;
        case Size::Large:
            createImageRequest->size = "1024x1024";
            break;
    }
    createImageRequest->response_format = RESPONSE_FORMAT;
    createImageRequest->user = _user;

    const CreateImageResponse::Ptr createImageResponse = _api->CreateImage(createImageRequest);
    return createImageResponse->data[0];
}

void OpenAI::Dalle::SetSize(const Size size)
{
    _size = size;
}