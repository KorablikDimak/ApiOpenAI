#include <OpenAI/OpenAI.h>
#include <OpenAI/GptTurbo.h>
#include <OpenAI/Whisper.h>
#include <OpenAI/Dalle.h>
#include <OpenAI/Speaker.h>

OpenAI::OpenAI::OpenAI(const std::string &token)
{
    _api = std::make_shared<OpenAIApi>(token);
}

OpenAI::OpenAIModel::Ptr OpenAI::OpenAI::GptTurboSession(const std::string& user, const std::string& name) const
{
    return std::make_shared<GptTurbo>(_api, user, name);
}

OpenAI::OpenAIModel::Ptr OpenAI::OpenAI::WhisperSession() const
{
    return std::make_shared<Whisper>(_api);
}

OpenAI::OpenAIModel::Ptr OpenAI::OpenAI::DalleSession(const std::string& user) const
{
    return std::make_shared<Dalle>(_api, user);
}

OpenAI::OpenAIModel::Ptr  OpenAI::OpenAI::SpeakerSession() const
{
    return std::make_shared<Speaker>(_api);
}
