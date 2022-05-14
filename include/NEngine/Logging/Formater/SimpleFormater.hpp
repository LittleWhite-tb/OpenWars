#ifndef SIMPLEFORMATER_HPP
#define SIMPLEFORMATER_HPP

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

namespace NE
{
    class SimpleFormater : public NE::LoggerFormater
    {
        protected:
            /*! \brief Format the input <i>message</i> to be outputted exactly the same
             *  \param level the priority level (unused here)
             *  \param message
             *  \return the new formed message (just a copy of message as a std::string)
             */
            std::string format(int level, const std::string& message)
            {
                return message;
            }
    };
}

/*! \class NE::SimpleFormater SimpleFormater.hpp Logging/Formater/SimpleFormater.hpp
 *  \brief Formater letting the information passing through without any changes
 *  \sa Logger
 */

#endif
