#include <OpenAI/Speaker.h>

const std::string OpenAI::Speaker::MODEL_NAME = "tts-1";

OpenAI::Speaker::Speaker(const OpenAIApi::Ptr &api, const std::string& directory) noexcept
{
    _api = api;
    _modelName = MODEL_NAME;
    _voice = Voice::alloy;
    _responseFormat = ResponseFormat::mp3;
    _speed = 1;
    _directory = directory;
}

std::string OpenAI::Speaker::Speech(const std::string &text) const noexcept
{
    const auto speechRequest = std::make_shared<SpeechRequest>();
    speechRequest->model = _modelName;
    speechRequest->input = text;
    speechRequest->voice = ToString(_voice);
    speechRequest->response_format = ToString(_responseFormat);
    speechRequest->speed = _speed;
    return _api->Speech(speechRequest);
}

void OpenAI::Speaker::ChangeVoice(const Voice voice) noexcept
{
    _voice = voice;
}

void OpenAI::Speaker::ChangeResponseFormat(const ResponseFormat format) noexcept
{
    _responseFormat = format;
}

void OpenAI::Speaker::SetSpeed(const float speed) noexcept
{
    if (speed >= 0.25 && speed <= 4)
        _speed = speed;
}

void OpenAI::Speaker::SetDirectory(const std::string& directory) noexcept
{
    _directory = directory;
}