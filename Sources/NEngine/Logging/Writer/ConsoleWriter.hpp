#ifndef CONSOLEWRITER_HPP
#define CONSOLEWRITER_HPP

#include "LoggerWriter.hpp"
#include "../Logger_globals.hpp"

#include <iostream>

#if defined(__WIN32__) || defined(WIN) || defined(WIN32)
    #include <windows.h>
#endif

namespace NE
{
    class ConsoleWriter : public NE::LoggerWriter
    {
        protected:

            /*! \brief Output the <i>message</i> to the console
             *  On Windows, the message will be colourised by this LoggerWriter depending on the priority of the message.
             *  The warnings are made yellow and errors red.
             *  Errors are outputted on std::cerr, all others are outputted on std::cout
             *  \param level priority level (unused here)
             *  \param message
             */
            void write(int level, const std::string& message)
            {
                switch (level)
                {
                    case LL_Warning:
            #if defined(__WIN32__) || defined(WIN) || defined(WIN32)
                        SetConsoleTextAttribute(GetStdHandle(STD_ERROR_HANDLE),14);
                        std::cout << message;
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
            #else
                        std::cout << message;
            #endif
                        break;
                    case LL_Error:
            #if defined(__WIN32__) || defined(WIN) || defined(WIN32)
                        SetConsoleTextAttribute(GetStdHandle(STD_ERROR_HANDLE),12);
                        std::cerr << message << std::endl;
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
            #else
                        std::cerr << message;
            #endif
                        break;
                    default:
                        std::cout << message;
                        break;
                }
            }
    };
}

/*! \class NE::ConsoleWriter ConsoleWriter.hpp Logging/Writer/ConsoleWriter.hpp
 *  \brief Writer implementation outputting information on the console (std::cout / std::cerr)
 *
 *  The errors are outputted on std::cerr, others on std::cout.
 *  \warning On Windows, the messages are colourised using SetConsoleTextAttribute.
 *  \sa Logger
 */

#endif
