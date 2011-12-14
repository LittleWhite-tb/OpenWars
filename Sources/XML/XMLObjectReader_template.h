#ifndef __XMLOBJECTREADER_TEMPLATE_H__
#define __XMLOBJECTREADER_TEMPLATE_H__

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

#include <libxml/parser.h>

#include "NEngine/NEngine.h"
#include "NEngine/SpriteLoader.h"

#include "Engine/Library.h"
#include "Engine/Params.h"

template <typename T>
bool XMLObjectReader :: parse(const std::string& nodeName, Library<T>* pLibrary, NE::SpriteLoader* pSL, const std::string& folderPath)
{
    // LDebug << "Started XMLReader parsing";

    xmlNodePtr xmlRoot = xmlDocGetRootElement(xmlFile);
    if ( xmlRoot == NULL )
    {
        NE::NEngine::logger().log(NE::LL_Error,"XML file does not have a root node");
        return false;
    }

    // LDebug << "Root is: " << xmlRoot->name;

    bool bResult = true;
    xmlNodePtr node;
    for ( node = xmlRoot->children ; node ; node = node->next )
    {
        if (node->type == XML_ELEMENT_NODE)
        {
            if ( xmlStrcmp((const xmlChar *)nodeName.c_str(),node->name) == 0 )
            {
                if ( node->children )
                {
                    Params* pParams = new Params();
                    if ( pParams == NULL )
                    {
                        NE::NEngine::logger().log(NE::LL_Error,"Fail to allocate memory for Params");
                        throw std::bad_alloc();
                    }

                    if ( node->properties )
                    {
                        bResult &= parseAttributes(node,pParams);
                    }

                    bResult &= parseNodes(node->children,pParams,"");
                    if ( bResult == true )
                    {
                        T* pInstance = new T(pParams,pSL,folderPath);
                        if ( pInstance == NULL )
                        {
                            NE::NEngine::logger().log(NE::LL_Error,"Fail to allocate memory for %s",typeid(T).name());
                            throw std::bad_alloc();
                        }

                        pLibrary->add(pInstance->getInternalName(),pInstance);
                    }
                    // LDebug << "Finished '" << typeid(T).name() << "' parsing";
                }
                else
                {
                    NE::NEngine::logger().log(NE::LL_Error,"%s node is empty -> ignored",typeid(T).name());
                }
            }
            else
            {
                NE::NEngine::logger().log(NE::LL_Error,"File contain an invalid node '%s' -> Ignored",node->name);
            }
        }
    }

    // LDebug << "Finished XMLReader parsing";

    return bResult;
}

#endif
