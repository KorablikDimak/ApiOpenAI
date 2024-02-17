#include <OpenAI/Speaker.h>

const std::string OpenAI::Speaker::MODEL_NAME = "tts-1";

OpenAI::Speaker::Speaker(const OpenAIApi::Ptr &api)
{
    _api = api;
    _modelName = MODEL_NAME;
    _voice = Voice::alloy;
    _responseFormat = ResponseFormat::mp3;
    _speed = 1;
}

std::string OpenAI::Speaker::Speech(const std::string &text) const
{
    const auto speechRequest = std::make_shared<SpeechRequest>();
    speechRequest->model = _modelName;
    speechRequest->input = text;
    speechRequest->voice = ToString(_voice);
    speechRequest->response_format = ToString(_responseFormat);
    speechRequest->speed = _speed;
    return _api->Speech(speechRequest);
}

void OpenAI::Speaker::ChangeVoice(const Voice voice)
{
    _voice = voice;
}

void OpenAI::Speaker::ChangeResponseFormat(const ResponseFormat format)
{
    _responseFormat = format;
}

void OpenAI::Speaker::SetSpeed(const float speed)
{
    if (speed >= 0.25 && speed <= 4)
        _speed = speed;
}
