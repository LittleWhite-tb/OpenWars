#include "ColourFormater.hpp"

#include <cstdio>

#if defined(__WIN32__) || defined(WIN) || defined(WIN32)
    #include <windows.h>
#endif

void NE::ColourFormater::format(NE::LoggerMessage& message)
{
    char buffer[1000] = {0};

    vsnprintf(buffer,999,message.format.c_str(),*message.messages);

    switch(message.level)
    {
        case NE::LL_Warning:
#if defined(linux) || defined(__linux) || defined(__linux__)
            message.formatedMessage = "\033[33m" + std::string(buffer) + "\033[0m";
#else
            message.formatedMessage = std::string(buffer);
#endif

            break;
        case NE::LL_Error:
#if defined(linux) || defined(__linux) || defined(__linux__)
            message.formatedMessage = "\033[31m" + std::string(buffer) + "\033[0m";
#else
            message.formatedMessage = std::string(buffer);
#endif
            break;
		default:
            message.formatedMessage = buffer;
            break;
    }
}
