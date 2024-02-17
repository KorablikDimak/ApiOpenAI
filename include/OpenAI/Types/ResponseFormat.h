#ifndef OpenAI_ResponseFormat_H
#define OpenAI_ResponseFormat_H

#include <string>

namespace OpenAI
{
    enum class ResponseFormat
    {
        mp3 = 0,
        opus = 1,
        aac = 2,
        flac = 3
    };

    inline void FromString(ResponseFormat& format, const std::string& formatString)
    {
        if (formatString == "mp3")
            format = ResponseFormat::mp3;
        else if (formatString == "opus")
            format = ResponseFormat::opus;
        else if (formatString == "aac")
            format = ResponseFormat::aac;
        else if (formatString == "flac")
            format = ResponseFormat::flac;
    }

    inline std::string ToString(const ResponseFormat voice)
    {
        switch (voice)
        {
            case ResponseFormat::mp3:
                return "mp3";
            case ResponseFormat::opus:
                return "opus";
            case ResponseFormat::aac:
                return "aac";
            case ResponseFormat::flac:
                return "flac";
        }
        return "";
    }
}

#endif