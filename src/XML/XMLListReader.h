#ifndef __XMLLISTTREADER_H__
#define __XMLLISTTREADER_H__

#ifndef DOXYGEN_IGNORE_TAG
/**
OpenAWars is an open turn by turn strategic game similar to Advance Wars (c)
Copyright (C) 2010-2015  Alexandre LAURENT

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

website: https://github.com/LittleWhite-tb/OpenWars
e-mail: lw.demoscene@gmail.com
**/
#endif

#include "XMLReader.h"

#include <string>
#include <list>

class XMLListReader : public XMLReader
{
private:

	bool parseNodes(xmlNodePtr xmlNode, std::list<std::string>* pNodeValueList, const std::string& searchedNode);

public:
	XMLListReader(const std::string& fileName):XMLReader(fileName) {}

	bool parse(const std::string& nodeName, std::list<std::string>* pNodeValueList);
};

/*! \class XMLListReader XMLListReader.h "XML/XMLListReader.h"
 *  \brief Parse list of information from XML file
 */

/*! \fn XMLListReader :: XMLListReader(const std::string& fileName)
 *	\param fileName file to open and read
 */

/*! \fn bool XMLListReader :: parseNodes(xmlNodePtr xmlNode, std::list<std::string>* pNodeValueList, const std::string& searchedNode);
 *	\brief parse a sub-node (recursive function)
 *	\param xmlNode the sub node to parse
 *	\param pNodeValueList the information storage to fill
 *	\param searchedNode the node to search
 *	\return true if all goes right
 *  This function is recursive and will call itself if a sub node exist. Only node called ''searchedNode'' will be read
 */

/*! \fn bool XMLListReader :: parse(const std::string& nodeName, std::list<std::string>* pNodeValueList);
 *	\brief parse the file for ''nodeName'' information / Other nodes are ignored.
 *	\param nodeName the name of the nodes to worry about
 *	\param pNodeValueList a pointer to the storage to fill
 *	\return true if all goes right ; false if the XML file does not have root node
 */

#endif
