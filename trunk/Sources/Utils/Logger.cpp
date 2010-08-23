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

#include "Logger.h"

#define NULL	0

Logger* Logger::pInstance = NULL;
LMessageType Logger::m_messageType = LMT_Debug;

Logger* Logger :: getLogger(const LMessageType messageType)
{
	// Check if we exist
	if ( pInstance == NULL )
	{
		// Birthday!
		pInstance = new Logger();
	}

#if defined(_DEBUG)
	m_messageType = messageType;

	// To have some newline in the logs

	switch (messageType)
	{
		case LMT_Debug:
			std::cout << std::endl;
			break;
		case LMT_Warning:
			std::cout << std::endl;
			break;
		case LMT_Error:
			std::cerr << std::endl;
			break;
	}
#else
	// Remove some warnings for unused parameter
	(void)messageType;
#endif

	return pInstance;
}

void Logger :: deleteLogger(void)
{
	// Kill itself
	delete pInstance;
	// Very important, otherwise we will crash after reusing the class
	pInstance = NULL;
}