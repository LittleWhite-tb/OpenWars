#ifndef COLOURFORMATER_HPP
#define COLOURFORMATER_HPP

#include "LoggerFormater.hpp"

namespace NE
{
    class ColourFormater : public LoggerFormater
    {
        protected:
            void format(NE::LoggerMessage& message);
    };
}

#endif
