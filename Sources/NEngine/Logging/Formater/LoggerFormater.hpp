#ifndef LOGGERFORMATER_HPP
#define LOGGERFORMATER_HPP

#include <string>

#include <cstdarg>

#include "../LoggerMessage.hpp"

namespace NE
{
    class LoggerFormater
    {
        protected:
            virtual void format(LoggerMessage& message)=0;
    };
}

#endif
