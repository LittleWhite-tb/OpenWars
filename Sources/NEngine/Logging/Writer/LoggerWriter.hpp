#ifndef LOGGERWRITER_HPP
#define LOGGERWRITER_HPP

#include <string>

#include "../LoggerMessage.hpp"

namespace NE
{
    class LoggerWriter
    {
        protected:

            virtual void write(const NE::LoggerMessage& message)=0;
    };
}

#endif
