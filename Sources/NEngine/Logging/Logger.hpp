#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "LoggerMessage.hpp"
#include "Filter/LoggerFilter.hpp"
#include "Formater/LoggerFormater.hpp"
#include "Writer/LoggerWriter.hpp"

namespace NE
{
    template <typename LoggerFilter, typename LoggerFormater, typename LoggerWriter>
    class Logger : public LoggerFilter, public LoggerFormater, public LoggerWriter
    {
        using LoggerFilter::accept;
        using LoggerFormater::format;
        using LoggerWriter::write;

        private:

        public:

            void log(int level, const char* stringFormat, ...)
            {
                va_list ap;

                va_start(ap,stringFormat);
                LoggerMessage message(level,stringFormat,&ap);

                if ( this->accept(message) )
                {
                    this->format(message);
                    this->write(message);
                }

                va_end(ap);
            }
    };
}

#endif
