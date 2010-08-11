#ifndef __LOGGER_H__
#define __LOGGER_H__

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

	static Logger* getLogger(const LMessageType messageType);
	static void deleteLogger(void);

	template <class T>
	Logger& operator<< (const T& message);
};

#include "Logger_template.hpp"

#define LDebug (*Logger::getLogger(LMT_Debug))
#define LWarning (*Logger::getLogger(LMT_Warning))
#define LError (*Logger::getLogger(LMT_Error))

#endif