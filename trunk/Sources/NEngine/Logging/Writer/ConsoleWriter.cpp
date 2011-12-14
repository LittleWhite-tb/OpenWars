#include "ConsoleWriter.hpp"

#include <iostream>

void NE::ConsoleWriter::write(const NE::LoggerMessage& message)
{
    switch (message.level)
    {
        case NE::LL_Warning:
            std::cout << message.formatedMessage << std::endl;
            break;
        case NE::LL_Error:
            std::cerr << message.formatedMessage << std::endl;
            break;
        default:
            std::cout << message.formatedMessage << std::endl;
            break;
    }
}
