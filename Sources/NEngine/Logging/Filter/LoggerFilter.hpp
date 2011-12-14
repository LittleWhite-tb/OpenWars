#ifndef LOGGERFILTER_HPP
#define LOGGERFILTER_HPP

#include "../LoggerMessage.hpp"

namespace NE
{
    class LoggerFilter
    {
        protected:
            virtual bool accept(const NE::LoggerMessage& message)=0;
    };
}

#endif
