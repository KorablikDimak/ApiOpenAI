#include <OpenAI/GptTurbo.h>

const std::string OpenAI::GptTurbo::MODEL_NAME = "gpt-3.5-turbo";
const float OpenAI::GptTurbo::TOP_P = 1;
const unsigned char OpenAI::GptTurbo::N = 1;
const std::int16_t OpenAI::GptTurbo::MAX_TOKENS = 0;
const float OpenAI::GptTurbo::PRESENCE_PENALTY = 0;
const float OpenAI::GptTurbo::FREQUENCY_PENALTY = 0;

OpenAI::GptTurbo::GptTurbo(const OpenAIApi::Ptr& api, const std::string& user, const std::string& name)
{
    _api = api;
    _modelName = MODEL_NAME;

    _user = user;
    if (name.size() > 64) throw std::invalid_argument("name is too long");
    _name = name;

    _contextSize = 2;
    _temperature = 1;
    _allowModelMessagesInContext = false;
}

std::pair<std::string, int> OpenAI::GptTurbo::Chat(const std::string& content)
{
    const auto chatRequestBody = std::make_shared<ChatCompletionsRequest>();
    chatRequestBody->model = _modelName;
    chatRequestBody->temperature = _temperature;
    chatRequestBody->top_p = TOP_P;
    chatRequestBody->n = N;
    chatRequestBody->stream = false;
    chatRequestBody->max_tokens = MAX_TOKENS;
    chatRequestBody->presence_penalty = PRESENCE_PENALTY;
    chatRequestBody->frequency_penalty = FREQUENCY_PENALTY;
    chatRequestBody->user = _user;

    auto iterator = _context.begin();
    for (unsigned char i = 0, count = 0; i < _context.size() && count < _contextSize; ++i)
    {
        auto message = std::make_shared<Message>();
        std::pair<Role, std::string> pair = *iterator;

        switch (pair.first)
        {
            case Role::System:
                message->role = "system";
                message->content = pair.second;
                chatRequestBody->messages.push_back(message);
                ++count;
                break;
            case Role::User:
                message->role = "user";
                message->content = pair.second;
                message->name = _name;
                chatRequestBody->messages.push_back(message);
                ++count;
                break;
            case Role::Assistant:
                if (!_allowModelMessagesInContext) break;
                message->role = "assistant";
                message->content = pair.second;
                chatRequestBody->messages.push_back(message);
                ++count;
                break;
        }

        std::advance(iterator, 1);
    }

    const auto message = std::make_shared<Message>();
    message->role = "user";
    message->content = content;
    message->name = _name;
    chatRequestBody->messages.push_back(message);

    const ChatCompletionsResponse::Ptr chatResponseBody = _api->ChatCompletions(chatRequestBody);
    std::pair<std::string, int> result = std::make_pair(chatResponseBody->content, chatResponseBody->usage->total_tokens);

    _context.emplace_back(Role::User, content);
    _context.emplace_back(Role::Assistant, result.first);
    while (_context.size() > _contextSize * 2)
        _context.pop_front();

    return result;
}

void OpenAI::GptTurbo::AddSystemMessage(const std::string& content)
{
    // TODO AddSystemMessage
}

void OpenAI::GptTurbo::SetContextSize(const unsigned char contextSize)
{
    if (contextSize > 7) return;
    _contextSize = contextSize;
}

void OpenAI::GptTurbo::SetTemperature(const float temperature)
{
    if (temperature < 0 || temperature > 2) return;
    _temperature = temperature;
}

void OpenAI::GptTurbo::AllowModelMessagesInContext(const bool allow)
{
    _allowModelMessagesInContext = allow;
}