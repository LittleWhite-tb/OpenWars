#ifndef COLOURFORMATER_HPP
#define COLOURFORMATER_HPP

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

#include "LoggerFormater.hpp"
#include "../Logger_globals.hpp"

namespace NE
{
    class ColourFormater : public NE::LoggerFormater
    {
        protected:

            /*! \brief Format the input <i>message</i> to be outputted with some colours
             *  The warning are made yellow and the errors red. Others are unchanged
             *  \warning the colouration works only on Unix system
             *  \param level the priority level (unused here)
             *  \param message
             *  \return the new formed message (just a copy of message as a std::string)
             */
            std::string format(int level, const std::string& message)
            {
                std::string formatedMessage;

                switch(level)
                {
                    case LL_Warning:
            #if defined(linux) || defined(__linux) || defined(__linux__)
                        formatedMessage = "\033[33m" + message + "\033[0m";
            #else
                        formatedMessage = message;
            #endif

                        break;
                    case LL_Error:
            #if defined(linux) || defined(__linux) || defined(__linux__)
                        formatedMessage = "\033[31m" + message + "\033[0m";
            #else
                        formatedMessage = message;
            #endif
                        break;
                    default:
                        formatedMessage = message;
                        break;
                }

                return formatedMessage;
            }
    };
}

/*! \class NE::ColourFormater ColourFormater.hpp Logging/Formater/ColourFormater.hpp
 *  \brief Formater colouring the input message depending on the priority level
 *  \warning This formater colourize the message only on Unix systems since it is using the escapement characters
 *  \sa Logger
 */

#endif
