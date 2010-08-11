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

#include "Logger.h"

#if defined(__WIN32__) || defined(WIN) || defined(WIN32)
	#include <windows.h>
#endif

template <class T>
Logger& Logger :: operator<< (const T& message)
{
#if defined(_DEBUG)
	switch(this->m_messageType)
	{
		case LMT_Debug:
			std::cout  << message;
			break;
		case LMT_Warning:
#if defined(linux) || defined(__linux) || defined(__linux__)
				std::cout << "\033[33m" << message << "\033[0m";
#elif defined(__WIN32__) || defined(WIN) || defined(WIN32)
				SetConsoleTextAttribute(GetStdHandle(STD_ERROR_HANDLE),14);
				std::cout << message;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
#else
				std::cout << message;
#endif

			break;
		case LMT_Error:
#if defined(linux) || defined(__linux) || defined(__linux__)
				std::cerr << "\033[31m" << message << "\033[0m";
#elif defined(__WIN32__) || defined(WIN) || defined(WIN32)
				SetConsoleTextAttribute(GetStdHandle(STD_ERROR_HANDLE),4);
				std::cerr << message;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
#else
				std::cerr << message;
#endif
			break;
	}
#else
	// Remove some warnings for unused parameter
	(void)message;
#endif
	return *pInstance;

}