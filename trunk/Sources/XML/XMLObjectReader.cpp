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

#include "XMLObjectReader.h"

#include <iostream>
#include <string>
#include <cassert>

#include "Game/Params.h"

#include "Utils/Logger.h"
#include "Utils/Exceptions/XMLException.h"

XMLObjectReader :: XMLObjectReader(const std::string& fileName)
	:XMLReader(fileName)
{
}

bool XMLObjectReader :: parseAttributes(xmlNodePtr xmlNode, Params* const pParams)
{
	assert(pParams);
	if ( !xmlNode->properties )
	{
		// Silent fail condition
		return true;
	}

	bool bResult = true;

	xmlAttrPtr node;
	for ( node = xmlNode->properties ; node ; node = node->next )
	{
		if ( node->type == XML_ATTRIBUTE_NODE )
		{
			std::string attrName = std::string((const char*)xmlNode->name) + std::string("-") + std::string((const char*)node->name);
			LDebug << "Attribute detected '" << attrName << "'";

			if ( node->children && node->children->type == XML_TEXT_NODE && node->children->content && !node->children->next )
			{
				LDebug << "Captured: " << std::string((char*)node->children->content) << " for '" << attrName << "'";
				pParams->add(attrName,std::string((char*)node->children->content));
			}
		}
	}

	return bResult;
}

bool XMLObjectReader :: parseNodes(xmlNodePtr xmlNode, Params* const pParams, const std::string& previousNodes)
{
	assert(pParams);

	xmlNodePtr node;
	for ( node = xmlNode ; node ; node = node->next )
	{
		if (node->type == XML_ELEMENT_NODE)
		{
			std::string nodeName = std::string((const char*)node->name);
			if ( !previousNodes.empty() )
			{
				nodeName = previousNodes + std::string("_") + nodeName;
			}
			LDebug << "Detected '" << nodeName << "'";

			// Attribute
			if ( node->properties )
			{
				this->parseAttributes(node,pParams);
			}

			if ( node->children && node->children->type == XML_TEXT_NODE && node->children->content && !node->children->next )
			{
				LDebug << "Captured: " << std::string((char*)node->children->content) << " for '" << nodeName << "'";
				pParams->add(nodeName,std::string((char*)node->children->content));
			}

			if ( node->children )
			{
				parseNodes(node->children,pParams,std::string((const char*)node->name));
			}
			
		}
	}

	return true;
}
