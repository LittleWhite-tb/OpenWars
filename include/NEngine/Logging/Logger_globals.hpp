#ifndef LOGGER_GLOBALS_HPP
#define LOGGER_GLOBALS_HPP

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

/** \file Logger_globals.hpp
 * Brings some help to use the Logger<br>
 * Four message priority are defined to be passed to the <a>Logger::setLevel()</a> function<br>
 * Four macros are defined to log easily the messages, without worrying about the level priority<br>
 * \sa Logger
 */

const int LL_Info = 0;          /*!< Lower message priority (i.e. "Logger Init")*/
const int LL_Debug = 1;         /*!< Debug message priority (i.e. "TODO: Fix the bug") */
const int LL_Warning = 2;       /*!< Warning message priority (i.e. "You are badly using this") */
const int LL_Error = 3;         /*!< Error message priority (i.e. "Fatal error occured") */

#define LDebug(logger) logger.setLevel(LL_Debug);logger          /*!< shortcut to send debug messages */
#define LWarning(logger) logger.setLevel(LL_Warning);logger      /*!< shortcut to send warning messages */
#define LError(logger) logger.setLevel(LL_Error);logger          /*!< shortcut to send error messages */
#define Log(logger,level) logger.setLevel(level);logger          /*!< shortcut to send log message with specified importancy level */

#endif
