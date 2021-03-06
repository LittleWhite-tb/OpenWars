#ifndef __LIBRARYUNITEMPLATE_TEMPLATE_H__
#define __LIBRARYUNITEMPLATE_TEMPLATE_H__

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

#include "Library.h"

#include <map>
#include <string>

#include "Utils/Logger.h"
#include "Utils/Exceptions/LibraryException.h"

Library<UnitTemplate> :: ~Library()
{
    for ( std::map< std::string, UnitTemplateFactionList* >::iterator itPair = entries.begin() ; itPair != entries.end() ; ++itPair )
    {
        delete (itPair->second);
    }

    LDebug << "Library of " << typeid(UnitTemplateFactionList).name() << " free";
}

void Library<UnitTemplate> :: add(const std::string& name, UnitTemplate* const value)
{
    if ( !this->exists(name) )
    {
        entries[name] = new UnitTemplateFactionList();
        if ( entries[name] == NULL )
        {
            LError << "Fail to allocate memory for UnitTemplateFactionList";
            throw std::bad_alloc();
        }
    }

    entries[name]->add(value);
}

const UnitTemplateFactionList* Library<UnitTemplate> :: get(const std::string& name)const
{
    std::map<std::string, UnitTemplateFactionList*>::const_iterator itT = entries.find(name);

    if (itT == entries.end())
    {
        return NULL;
    }// ToDO throw exception ?

    return itT->second;
}

bool Library<UnitTemplate> :: exists(const std::string& name)const
{
    if ( entries.find(name) != entries.end() )
    {
        return true;
    }

    return false;
}

void Library<UnitTemplate> :: getValues(std::list< const UnitTemplateFactionList* >* pListItems)const
{
    for (std::map< std::string, UnitTemplateFactionList* >::const_iterator itItem = entries.begin() ;
         itItem != entries.end() ; ++itItem )
    {
        pListItems->push_back(itItem->second);
    }
}

#endif
