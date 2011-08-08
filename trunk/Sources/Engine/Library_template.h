#ifndef __LIBRARY_TEMPLATE_H__
#define __LIBRARY_TEMPLATE_H__

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

#include "Library.h"

#include <map>
#include <string>

#include "Utils/Logger.h"

template <typename T>
Library<T> :: ~Library()
{
    for ( LibraryIterator itPair = entries.begin() ; itPair != entries.end() ; ++itPair )
    {
        delete (itPair->second);
    }

    LDebug << "Library of " << typeid(T).name() << " free";
}

template <typename T>
void Library<T> :: add(const std::string& name, T* const value)
{
    if ( this->exists(name) )
    {
        LWarning << "Library will overwrite the key '" << name << "'";
    }
    entries[name] = value;
}

template <typename T>
const T* Library<T> :: get(const std::string& name)const
{
    LibraryConstIterator itT = entries.find(name);

    if (itT == entries.end())
    {
        throw LibraryException("Element '" + name + "' not found");
    }

    return itT->second;
}

template <typename T>
bool Library<T> :: exists(const std::string& name)const
{
    if ( entries.find(name) != entries.end() )
    {
        return true;
    }

    return false;
}

template <typename T>
void Library<T> :: getValues(std::list< const T* >* pListItems)const
{
    for (LibraryConstIterator itItem = entries.begin() ;
         itItem != entries.end() ; ++itItem )
    {
        pListItems->push_back(itItem->second);
    }
}

#endif
