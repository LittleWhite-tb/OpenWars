#ifndef __XMLREADER_H__
#define __XMLREADER_H__

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

#include <libxml/parser.h>

#include <string>

#include <NEngine/Exception.h>

class XMLReader
{
protected:

	xmlDocPtr xmlFile;	/*!< */

public:

	XMLReader(const std::string& fileName);
	virtual ~XMLReader();
};

class XMLParsingFailedException : public Exception
{
public:
	XMLParsingFailedException(const std::string& fileName):Exception(std::string("Failed to parse '") + fileName + std::string("' XML file (not existing or mal-formatted)")) {}
};

/*! \class XMLReader XMLReader.h "XML/XMLReader.h"
 *  \brief base class for XML file handling
 */

/*! \fn XMLReader :: XMLReader(const std::string& fileName)
 *	\brief Open a XML file
 *	\param fileName the file of the name to open
 *  Throw an XMLParsingFailedException if the file is not a valid XML or is not openable
 */

/*! \fn virtual XMLReader :: ~XMLReader()
 *	Free the ressource allocated when opening the XML file
 */


/*! \class XMLParsingFailedException XMLReader.h "XML/XMLReader.h"
 *  \brief Exception for XML parsers
 */

/*! \fn XMLParsingFailedException::XMLParsingFailedException(const std::string& fileName)
 * \param fileName the name of the file from where the problem is
 */

#endif
