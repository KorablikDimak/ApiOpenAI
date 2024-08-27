#ifndef OpenAI_Size_H
#define OpenAI_Size_H

#include <string>

namespace OpenAI
{
    enum class Size
    {
        Mini = 0,
        Medium = 1,
        Large = 2
    };

    inline void FromString(Size& size, const std::string& sizeString) noexcept
    {
        if (sizeString == "256x256")
            size = Size::Mini;
        else if (sizeString == "512x512")
            size = Size::Medium;
        else if (sizeString == "1024x1024")
            size = Size::Large;
    }

    inline std::string ToString(const Size size) noexcept
    {
        switch (size)
        {
            case Size::Mini:
                return "256x256";
            case Size::Medium:
                return "512x512";
            case Size::Large:
                return "1024x1024";
        }
        return "";
    }
}

#endif