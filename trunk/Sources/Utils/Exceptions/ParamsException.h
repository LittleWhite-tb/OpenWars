#ifndef __PARAMSEXCEPTION_H__
#define __PARAMSEXCEPTION_H__

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

class ParameterNotFoundParamsException : public std::exception
{
private:
	std::string message;	/*!< error message to display */

public:
	ParameterNotFoundParamsException(const std::string& paramName):message(std::string("Parameter '") + paramName + std::string("' not found")) {}
    virtual ~ParameterNotFoundParamsException(void)throw() {}

	virtual const char* what() const throw()
	{
		return message.c_str();
	}
};

class InvalidConvertionParamsException : public std::exception
{
private:
	std::string message;	/*!< error message to display */

public:
	InvalidConvertionParamsException(const std::string& paramName):message(std::string("Invalid convertion for parameter '") + paramName + std::string("'")) {}
    virtual ~InvalidConvertionParamsException(void)throw() {}

	virtual const char* what() const throw()
	{
		return message.c_str();
	}
};

/*! \class ParameterNotFoundParamsException ParameterNotFoundParamsException.h "Utils/Exceptions/ParameterNotFoundParamsException.h"
 *  \brief Exception for parameters not found when requested
 */

/*! \fn ParameterNotFoundParamsException::ParameterNotFoundParamsException(const std::string& paramName)
 * Create a message of the format: "Parameter 'PARAMETER_NAME' not found"
 * \param paramName the parameter name missing
 */

/*! \fn virtual const char* ParameterNotFoundParamsException::what()const throw()
 * \return the error message
 */


/*! \class InvalidConvertionParamsException InvalidConvertionParamsException.h "Utils/Exceptions/InvalidConvertionParamsException.h"
 *  \brief Exception for invalid cast of parameters
 */

/*! \fn InvalidConvertionParamsException::InvalidConvertionParamsException(const std::string& paramName)
 * Create a message of the format: "Invalid convertion for parameter 'PARAMETER_NAME'"
 * \param paramName the parameter name
 */

/*! \fn virtual const char* InvalidConvertionParamsException::what()const throw()
 * \return the error message
 */

#endif