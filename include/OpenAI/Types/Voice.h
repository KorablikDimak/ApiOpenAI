#ifndef OpenAI_Voice_H
#define OpenAI_Voice_H

#include <string>

namespace OpenAI
{
    enum class Voice
    {
        alloy = 0,
        echo = 1,
        fable = 2,
        onyx = 3,
        nova = 4,
        shimmer = 5
    };

    inline void FromString(Voice& voice, const std::string& voiceString)
    {
        if (voiceString == "alloy")
            voice = Voice::alloy;
        else if (voiceString == "echo")
            voice = Voice::echo;
        else if (voiceString == "fable")
            voice = Voice::fable;
        else if (voiceString == "onyx")
            voice = Voice::onyx;
        else if (voiceString == "nova")
            voice = Voice::nova;
        else if (voiceString == "shimmer")
            voice = Voice::shimmer;
    }

    inline std::string ToString(const Voice voice)
    {
        switch (voice)
        {
            case Voice::alloy:
                return "alloy";
            case Voice::echo:
                return "echo";
            case Voice::fable:
                return "fable";
            case Voice::onyx:
                return "onyx";
            case Voice::nova:
                return "nova";
            case Voice::shimmer:
                return "shimmer";
        }
        return "";
    }
}

#endif