#ifndef LOGGERFORMATER_HPP
#define LOGGERFORMATER_HPP

#include <string>

namespace NE
{
    class LoggerFormater
    {
        protected:
            virtual std::string format(int level, const std::string& message)=0;
    };
}

/*! \class LoggerFormater LoggerFormater.hpp Logging/Formater/LoggerFormater.hpp
 *  \brief Base class for formatting information
 *  \sa Logger
 */

#endif
