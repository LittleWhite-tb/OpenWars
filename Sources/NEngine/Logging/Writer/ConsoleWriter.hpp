#ifndef CONSOLEWRITER_HPP
#define CONSOLEWRITER_HPP

#include "LoggerWriter.hpp"

namespace NE
{
    class ConsoleWriter : public LoggerWriter
    {
        protected:

            void write(const NE::LoggerMessage& message);
    };
}

#endif
