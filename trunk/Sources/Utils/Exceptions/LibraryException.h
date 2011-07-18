#ifndef __LIBRARYEXCEPTION_H__
#define __LIBRARYEXCEPTION_H__

#ifndef DOXYGEN_IGNORE_TAG
/**
OpenAWars is an open turn by turn strategic game aiming to recreate the feeling of advance (famicon) wars (c)
Copyright (C) 2010-2011  Alexandre LAURENT

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

#include <string>

class LibraryException : public std::exception
{
private:
	std::string message;	/*!< Message to display */

public:
	LibraryException(const std::string& userMessage):message(userMessage) {}
    virtual ~LibraryException(void)throw() {}

	virtual const char* what() const throw()
	{
		return message.c_str();
	}
};

/*! \class LibraryException LibraryException.h "Utils/Exceptions/LibraryException.h"
 *  \brief Exception when library class failed
 */

/*! \fn LibraryException::LibraryException(const std::string& userMessage)
 * \param userMessage message to display
 */

/*! \fn virtual const char* LibraryException::what()const throw()
 * \return the error message
 */

#endif
