#ifndef LOGGERWRITER_HPP
#define LOGGERWRITER_HPP

#include <string>

namespace NE
{
    class LoggerWriter
    {
        protected:

            virtual ~LoggerWriter() {};
            virtual void write(int level, const std::string& message)=0;
    };
}

/*! \class NE::LoggerWriter LoggerWriter.hpp Logging/Writer/LoggerWriter.hpp
 *  \brief Base class for output information in a log media
 *  \sa Logger
 */

#endif
