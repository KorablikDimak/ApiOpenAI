#include <gtest/gtest.h>

#include <OpenAI/OpenAI.h>
#include <OpenAI/GptTurbo.h>
#include <OpenAI/Whisper.h>
#include <OpenAI/Speaker.h>

TEST(NoThrowTests, NoThrowTestGptTurbo)
{
    const OpenAI::OpenAIApi::Ptr api = std::make_shared<OpenAI::OpenAIApi>("test_token");
    OpenAI::GptTurbo gptTurbo(api);

    ASSERT_NO_THROW(auto result = gptTurbo.Chat("test_message"));
}

TEST(NoThrowTests, NoThrowTestWhisper)
{
    const OpenAI::OpenAIApi::Ptr api = std::make_shared<OpenAI::OpenAIApi>("test_token");
    OpenAI::Whisper whisper(api);

    ASSERT_NO_THROW(std::string result = whisper.Transcript("test_message"));
}

TEST(NoThrowTests, NoThrowTestSpeaker)
{
    const OpenAI::OpenAIApi::Ptr api = std::make_shared<OpenAI::OpenAIApi>("test_token");
    OpenAI::Speaker speaker(api);

    ASSERT_NO_THROW(std::string result = speaker.Speech("test_message"));
}