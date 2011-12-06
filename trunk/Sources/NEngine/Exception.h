#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

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

class Exception : public std::exception
{
private:
	std::string message;

public:
	Exception(const std::string& userMessage):message(std::string("Exception received (") + userMessage + std::string(")")) {}
    virtual ~Exception(void)throw() {}

	virtual const char* what() const throw()
	{
		return message.c_str();
	}
};

/*! \class Exception Exception.h "NEngine/Exception.h"
 *  \brief Exception base class
 */

/*! \fn Exception::Exception(const std::string& userMessage)
 * Create a message of the format: "Exception received (USER_MESSAGE)"
 * \param userMessage message from the user to display
 */

/*! \fn virtual const char* Exception::what()const throw()
 * \return the error message
 */

#endif