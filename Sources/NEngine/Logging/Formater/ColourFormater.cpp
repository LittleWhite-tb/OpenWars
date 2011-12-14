#include "ColourFormater.hpp"

#include <cstdio>

void NE::ColourFormater::format(NE::LoggerMessage& message)
{
    char buffer[1000] = {0};

    vsnprintf(buffer,999,message.format.c_str(),*message.messages);

    switch(message.level)
    {
        case 0:
            break;
        case NE::LL_Debug:
            message.formatedMessage = buffer;
            break;
        case NE::LL_Warning:
            message.formatedMessage = "\033[33m" + std::string(buffer) + "\033[0m";
            break;
        case NE::LL_Error:
            message.formatedMessage = "\033[31m" + std::string(buffer) + "\033[0m";
            break;
    }
}
