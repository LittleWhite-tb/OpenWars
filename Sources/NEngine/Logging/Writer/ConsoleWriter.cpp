#include "ConsoleWriter.hpp"

#include <iostream>

#if defined(__WIN32__) || defined(WIN) || defined(WIN32)
    #include <windows.h>
#endif

void NE::ConsoleWriter::write(const NE::LoggerMessage& message)
{
    switch (message.level)
    {
        case NE::LL_Warning:
#if defined(__WIN32__) || defined(WIN) || defined(WIN32)
            SetConsoleTextAttribute(GetStdHandle(STD_ERROR_HANDLE),14);
            std::cout << message.formatedMessage << std::endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
#else
			std::cout << message.formatedMessage << std::endl;
#endif
            break;
        case NE::LL_Error:
#if defined(__WIN32__) || defined(WIN) || defined(WIN32)
            SetConsoleTextAttribute(GetStdHandle(STD_ERROR_HANDLE),12);
            std::cerr << message.formatedMessage << std::endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
#else
			std::cerr << message.formatedMessage << std::endl;
#endif
            break;
        default:
            std::cout << message.formatedMessage << std::endl;
            break;
    }
}
