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

#include "XMLListReader.h"

#include <libxml/parser.h>

#include <cassert>

#include "NEngine/NEngine.h"

bool XMLListReader :: parseNodes(xmlNodePtr xmlNode, std::list<std::string>* pNodeValueList, const std::string& searchedNode)
{
	assert(pNodeValueList);

	bool bResult = true;
	xmlNodePtr node;
	for ( node = xmlNode ; node ; node = node->next )
	{
		if (node->type == XML_ELEMENT_NODE)
		{
			if ( xmlStrcmp((const xmlChar *)searchedNode.c_str(),node->name) == 0 )
			{
				if ( node->children && node->children->type == XML_TEXT_NODE && node->children->content && !node->children->next )
				{
                    NE::NEngine::logger()->log(NE::LL_Debug,"Captured: '%s'",(char*)node->children->content);
					pNodeValueList->push_back(std::string((char*)node->children->content));
				}
			}

			// Recursive
			if ( node->children )
			{
				bResult &= parseNodes(node->children,pNodeValueList,searchedNode);
			}
		}
	}

	return bResult;
}

bool XMLListReader :: parse(const std::string& nodeName, std::list<std::string>* pNodeValueList)
{
	assert(pNodeValueList);

	xmlNodePtr xmlRoot = xmlDocGetRootElement(xmlFile);
	if ( xmlRoot == NULL )
	{
        NE::NEngine::logger()->log(NE::LL_Error,"XML file does not have a root node");
		return false;
	}

	return parseNodes(xmlRoot,pNodeValueList,nodeName);
}