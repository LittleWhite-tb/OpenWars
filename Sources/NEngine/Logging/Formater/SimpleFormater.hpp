#ifndef SIMPLEFORMATER_HPP
#define SIMPLEFORMATER_HPP

#include "LoggerFormater.hpp"

namespace NE
{
    class SimpleFormater : public LoggerFormater
    {
        protected:
            void format(NE::LoggerMessage& message);
    };
}

#endif
