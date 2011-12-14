#include "SimpleFormater.hpp"

#include <cstdio>

void NE::SimpleFormater::format(NE::LoggerMessage& message)
{
    char buffer[1000] = {0};

    vsnprintf(buffer,999,message.format.c_str(),*message.messages);
    message.formatedMessage = std::string(buffer);
}
