#ifndef __XMLEXCEPTION_H__
#define __XMLEXCEPTION_H__

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

class XMLParsingFailedException : public std::exception
{
private:
	std::string message;	/*!< error message to display */

public:
	XMLParsingFailedException(const std::string& fileName):message(std::string("Failed to parse '") + fileName + std::string("' XML file (not existing or mal-formatted)")) {}
    virtual ~XMLParsingFailedException(void)throw() {}

	virtual const char* what() const throw()
	{
		return message.c_str();
	}
};

/*! \class XMLParsingFailedException XMLParsingFailedException.h "Utils/Exceptions/XMLParsingFailedException.h"
 *  \brief Exception for XML parsers
 */

/*! \fn XMLParsingFailedException::XMLParsingFailedException(const std::string& fileName)
 * Create a message of the format: "Failed to parse 'FILENAME' XML file (not existing or mal-formatted)"
 * \param fileName the name of the file from where the problem is
 */

/*! \fn virtual const char* XMLParsingFailedException::what()const throw()
 * \return the error message
 */

#endif