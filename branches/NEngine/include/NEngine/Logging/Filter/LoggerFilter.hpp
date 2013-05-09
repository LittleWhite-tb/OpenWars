#ifndef LOGGERFILTER_HPP
#define LOGGERFILTER_HPP

namespace NE
{
    class LoggerFilter
    {
        protected:
            /*! \brief Determines if the priority level passed as argument is enough to be written in the log
             *  \param level
             *  \return true if the information should be written
             */
            virtual bool accept(int level)=0;
    };
}

/*! \class LoggerFilter LoggerFilter.hpp Logging/Filter/LoggerFilter.hpp
 *  \brief Base class for filtering information based on priority level
 */

#endif
