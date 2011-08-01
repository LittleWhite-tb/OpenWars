#ifndef __BOUH_LIBRARY_H__
#define __BOUH_LIBRARY_H__

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

#include <list>
#include <map>
#include <string>
#include <cassert>

#include <typeinfo>

#include "Game/UnitTemplate.h"
#include "Game/UnitTemplateFactionList.h"

#include "Utils/Logger.h"
#include "Utils/Exceptions/LibraryException.h"

template <typename T>
class Library
{
    typedef typename std::map < std::string, T* >::iterator LibraryIterator;
    typedef typename std::map < std::string, T* >::const_iterator LibraryConstIterator;

private:

    std::map < std::string, T* > entries;   /*!< */

public:

    ~Library();
    void add(const std::string& name, T* const value);
    const T* get(const std::string& name)const;
    bool exists(const std::string& name)const;
    void getValues(std::list< const T* >* pListItems)const;
};

#include "Library_template.h"

template <>
class Library<UnitTemplate>
{
private:

    std::map < std::string, UnitTemplateFactionList* > entries;     /*!< */

public:

    ~Library()
    {
        for ( std::map< std::string, UnitTemplateFactionList* >::iterator itPair = entries.begin() ; itPair != entries.end() ; ++itPair )
        {
            delete (itPair->second);
        }

        LDebug << "Library of " << typeid(UnitTemplateFactionList).name() << " free";
    }

    void add(const std::string& name, UnitTemplate* const value)
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

    const UnitTemplateFactionList* get(const std::string& name)const
    {
        std::map<std::string, UnitTemplateFactionList*>::const_iterator itT = entries.find(name);

        if (itT == entries.end())
        {
            return NULL;
        }// ToDO throw exception ?

        return itT->second;
    }

    bool exists(const std::string& name)const
    {
        if ( entries.find(name) != entries.end() )
        {
            return true;
        }

        return false;
    }

    void getValues(std::list< const UnitTemplateFactionList* >* pListItems)const
    {
        for (std::map< std::string, UnitTemplateFactionList* >::const_iterator itItem = entries.begin() ;
             itItem != entries.end() ; ++itItem )
        {
            pListItems->push_back(itItem->second);
        }
    }
};

/*! \class Library Library.h "Game/Library.h"
 *  \brief Contains elements indexed using a name
 */

/*! \fn void Library :: add(const std::string& name, T* const value)
 *  \brief Adds a new value corresponding to name
 *  \param name
 *  \param value
 */

/*! \fn const T* Library :: get(const std::string& name)const()
 *  \brief Gets the value corresponding to name
 *  \param name
 *  \return the value or NULL if name does not exist
 */

/*! \fn bool Library :: exists(const std::string& name)const
 *  \brief Checks if a value called name exists
 *  \param name
 *  \return true if the name is present
 */

/*! \fn void Library :: getValues(std::list< const T* >* pListItems)const()
 *  \brief Gets all the values contained in the library
 *  \param pListItems the list to fill with
 */

#endif
