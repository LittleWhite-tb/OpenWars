#ifndef NOFILTER_HPP
#define NOFILTER_HPP

#include "LoggerFilter.hpp"

namespace NE
{
    class NoFilter : public LoggerFilter
    {
        protected:
            bool accept(const NE::LoggerMessage& message)
            {
                (void)message;
                // Default is to return all the levels are valid
                return true;
            }
    };
}

#endif
