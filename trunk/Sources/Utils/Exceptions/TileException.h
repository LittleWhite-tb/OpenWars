#ifndef __TILEEXCEPTION_H__
#define __TILEEXCEPTION_H__

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

class MissingParameterTileException : public std::exception
{
private:
	std::string message;	/*!< error message to display */

public:
	MissingParameterTileException(const std::string& parameterName):message(std::string("Missing parameter '") + parameterName + std::string("' to construct the Tile")) {}
    virtual ~MissingParameterTileException (void)throw() {}

	virtual const char* what() const throw()
	{
		return message.c_str();
	}
};

/*! \class MissingParameterTileException MissingParameterTileException.h "Utils/Exceptions/MissingParameterTileException.h"
 *  \brief Exception for missing requested parameters
 */

/*! \fn MissingParameterTileException::MissingParameterTileException(const std::string& parameterName)
 * Create a message of the format: "Missing parameter 'PARAMETER_NAME' to construct the Tile"
 * \param parameterName the parameter name missing
 */

/*! \fn virtual const char* MissingParameterTileException::what()const throw()
 * \return the error message
 */

#endif