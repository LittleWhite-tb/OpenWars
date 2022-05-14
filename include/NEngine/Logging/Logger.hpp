#ifndef LOGGER_HPP
#define LOGGER_HPP

#ifndef DOXYGEN_IGNORE_TAG
/**
NEngine: Native Engine abstracts multimedia libraries such as SDL, SFML, Allegro
Copyright (C) 2010-2015  Alexandre LAURENT

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

website: https://github.com/LittleWhite-tb/NEngine
e-mail: lw.demoscene@gmail.com
**/
#endif

#include "Filter/LoggerFilter.hpp"
#include "Formater/LoggerFormater.hpp"
#include "Writer/LoggerWriter.hpp"
#include "Logger_globals.hpp"

#include <sstream>

namespace NE
{
    template <typename LoggerFilter, typename LoggerFormater, typename LoggerWriter>
    class Logger : public LoggerFilter, public LoggerFormater, public LoggerWriter
    {
        using LoggerFilter::accept;
        using LoggerFormater::format;
        using LoggerWriter::write;

        private:

            int m_level;

        public:
            /*!
             * Sets the default priority level of messages to <a>LL_Error</a>
             */
            Logger():m_level(LL_Error) {}

            /*! \brief Log a message
             *  For a message to be logged, the priority level should be accepted by the LoggerFilter, then it will be formatted by the LoggerFormater and written by the LoggerWriter
             *  \param message the information to log
             *  \sa setLevel
             */
            template <class T>
            Logger<NE::LoggerFilter, NE::LoggerFormater, NE::LoggerWriter>& operator<< (const T& message)
            {
                if ( this->accept(m_level) )
                {
                    // Convert the entry as a std::string
                    std::ostringstream oss;
                    oss << message;

                    this->write(m_level,this->format(m_level,oss.str()));
                }

                return *this;
            }

            /*! \brief Defines a new priority level for all following messages
             *  \param newLevel
             */
            void setLevel(int newLevel) { m_level = newLevel; }
    };
}

/*! \class Logger Logger.hpp Logging/Logger.hpp
 *  \brief Modulable logger based on templates
 *
 *  A logger consists in the composition of three classes:<br>
 *      LoggerFilter : allowing or restricting the message to be logged (e.g. only errors are outputted)<br>
 *      LoggerFormater : transforming the input message in a normalised way (e.g. prepend the message with the application time)<br>
 *      LoggerWriter : writting the formatted message on a specific media<br>
 *  This logger can be used as a normal stream (i.e. like std::cout), but, since it handles an priority for each message, the message's priority should be set with <a>setLevel</a><br>
 *  By default, all messages are <a>LL_Error</a><br>
 *  \sa LoggerFilter LoggerFormater LoggerWriter setLevel Logger_globals.hpp
 */

#endif
