#ifndef NOFILTER_HPP
#define NOFILTER_HPP

#include "LoggerFilter.hpp"

namespace NE
{
    class NoFilter : public NE::LoggerFilter
    {
        protected:

            bool accept(int level)
            {
                (void) level;

                // Default is to return all the levels are valid
                return true;
            }
    };
}

/*! \class NE::NoFilter NoFilter.hpp Logging/Filter/NoFilter.hpp
 *  \brief Filter accepting all input messages whatever what is the priority
 */

#endif
