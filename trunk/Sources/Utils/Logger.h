#ifndef __LOGGER_H__
#define __LOGGER_H__

#ifndef DOXYGEN_IGNORE_TAG
/**
OpenAWars is an open turn by turn strategic game aiming to recreate the feeling of advance (famicon) wars (c)
Copyright (C) 2010  Alexandre LAURENT

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

website: http://code.google.com/p/openawars/
e-mail: lw.demoscene@gmail.com
**/
#endif

#include <iostream>

typedef enum LMessageType
{
	LMT_Debug,
	LMT_Warning,
	LMT_Error
}LMessageType;

// This class is a Singleton
class Logger
{
private:
	static Logger* pInstance;
	// Keep the type of the message when the user wants to log something
	static LMessageType m_messageType;

	// The developper can't create the class himself
	Logger(void) {};
	~Logger(void) {};

	// Avoid the copy
	Logger(const Logger&);
	void operator= (const Logger&);

public:

	//! Get an instance of the logger
	/*!
		As all Singleton, if an instance of the logger already exists, this one is returned, otherwise we are creating a new one
		\param messageType the type of the message to send to the instance
		\return an instance of the Logger
	*/
	static Logger* getLogger(const LMessageType messageType);

	//! Basic destructor
	/*!
		Free memory
	*/
	static void deleteLogger(void);

	//! << overloading
	/*!
		\param message the message to send to the logger
		\return an instance of the logger to loop the << usage
	*/
	template <class T>
	Logger& operator<< (const T& message);
};

#include "Logger_template.hpp"

#define LDebug (*Logger::getLogger(LMT_Debug))			/*!< shortcut to send debug messages */
#define LWarning (*Logger::getLogger(LMT_Warning))		/*!< shortcut to send warning messages */
#define LError (*Logger::getLogger(LMT_Error))			/*!< shortcut to send error messages */

/*! \class Logger Logger.h "Utils/Logger.h"
 *  \brief Logging class
 *
 * This class is a singleton
 * The following should be the way to use it:
 *		- Use at anytime LDebug / LWarning / LError shortcuts to send messages
 *		- Free memory by calling deleteLogger() (if you reuse the shortcuts or getLogger(), you need to call again deleteLogger())
 */

/*! \enum LMessageType
 * Identifiers to know which message type is send to the Logger
 */

#endif