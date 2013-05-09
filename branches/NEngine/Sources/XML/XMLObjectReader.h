#ifndef __XMLOBJECTREADER_H__
#define __XMLOBJECTREADER_H__

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

#include "XMLReader.h"

#include <libxml/parser.h>

#include <string>

#include "Engine/Library.h"

namespace NE { class SpriteLoader; }

class Params;

class XMLObjectReader : public XMLReader
{
private:

	bool parseAttributes(xmlNodePtr xmlNode, Params* const pParams);
	bool parseNodes(xmlNodePtr xmlNode, Params* const pParams, const std::string& previousNodes);

public:
	XMLObjectReader(const std::string& fileName);

	template <typename T>
	bool parse(const std::string& nodeName, Library<T>* pLibrary, NE::SpriteLoader* pSL, const std::string& folderPath);
};

#include "XMLObjectReader_template.h"

/*! \class XMLObjectReader XMLObjectReader.h "XML/XMLObjectReader.h"
 *  \brief Parse objects information from XML file
 *	As temporary storage, a Params instance is used to keep the data read from the file. This Params is given to the constructor of the object that should use the information
 *	The parameters name are the following:
 *
 *	- For attributes, an '-' is added to the name
 *	- For sub-nodes, an '_' is added
 */

/*! \fn XMLObjectReader :: XMLObjectReader(const std::string& fileName)
 *	\param fileName file to open and read
 */

/*! \fn XMLObjectReader :: parseAttributes(xmlNodePtr xmlNode, Params* const pParams);
 *	\brief parse attributes for the current node
 *	\param xmlNode the node to parse attributes
 *	\param pParams the information storage to fill
 *	\return true if all goes right
 *  This function adds an '-' between the name of the node contening the attributes and the name of the attribute
 */

/*! \fn bool XMLObjectReader :: parseNodes(xmlNodePtr xmlNode, Params* const pParams, const std::string& previousNodes);
 *	\brief parse a sub-node (recursive function)
 *	\param xmlNode the sub node to parse
 *	\param pParams the information storage to fill
 *	\param previousNodes the name of the previous nodes
 *	\return true if all goes right
 *  This function is recursive and will call itself if a sub node exist. For each sub node, an '_' is added between the name of the previous node and the name of the parameter
 */

/*! \fn bool XMLObjectReader :: XMLObjectReader(const std::string& fileName)
 *	\brief Open a XML file for parsing
 *	\param fileName the file of the name to open
 *  Throw an XMLParsingFailedException if the file is not a valid XML or is not openable
 */

/*! \fn bool XMLObjectReader :: parse(const std::string& nodeName, Library<T>* pLibrary, NE::SpriteLoader* pSL, const std::string& folderPath);
 *	\brief parse the file for ''nodeName'' information/ Other nodes are ignored.
 *	\param nodeName the name of the nodes to worry about
 *	\param pLibrary a pointer to the library to fill
 *	\param pSL a pointer to a SpriteLoader to use to construct objects
 *	\param folderPath the path to the folder that the object should use to load data
 *	\return true if all goes right ; false if the XML file does not have root node
 *	The parser will fill the library with the objects information parsed. Technically, the object type must have a constructor accepting Params.
 *	The information parsed from the XML file are put in Params instance and then used to create the object.
 */

#endif
