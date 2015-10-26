#ifndef __LIBRARY_H__
#define __LIBRARY_H__

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

#include <list>
#include <map>
#include <string>
#include <cassert>

#include <typeinfo>

#include "NEngine/NEngine.h"
#include "NEngine/Exception.h"

#include "Game/GameState/GameObjects/UnitTemplate.h"
#include "Game/GameState/GameObjects/UnitTemplateFactionList.h"

class LibraryException : public Exception
{
public:
    LibraryException(const std::string& userMessage):Exception(userMessage) {}
};

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

        NEDebug << "Library of '" << typeid(UnitTemplateFactionList).name() << "' free\n";
    }

    void add(const std::string& name, UnitTemplate* const value)
    {
        if ( !this->exists(name) )
        {
            entries[name] = new UnitTemplateFactionList();
            if ( entries[name] == NULL )
            {
                NEError << "Fail to allocate memory for UnitTemplateFactionList\n";
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

/*! \fn Library :: ~Library()
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

/*! \class Library<UnitTemplate> Library.h "Game/Library.h"
 *  \brief Contains UnitTemplateFactionList indexed using a name.
 *  Each unit can be inserted multiple times making new faction
 */

/*! \fn Library<UnitTemplate> :: ~Library()
 */

/*! \fn void Library<UnitTemplate> :: add(const std::string& name, UnitTemplate* const value)
 *  \brief Adds a new value corresponding to name
 *  \param name
 *  \param value
 */

/*! \fn const T* Library<UnitTemplate> :: get(const std::string& name)const()
 *  \brief Gets the value corresponding to name
 *  \param name
 *  \return the value or NULL if name does not exist
 */

/*! \fn bool Library<UnitTemplate> :: exists(const std::string& name)const
 *  \brief Checks if a value called name exists
 *  \param name
 *  \return true if the name is present
 */

/*! \fn void Library<UnitTemplate> :: getValues(std::list< const UnitTemplateFactionList* >* pListItems)const()
 *  \brief Gets all the values contained in the library
 *  \param pListItems the list to fill with
 */

/*! \class LibraryException Library.h "Engine/Library.h"
 *  \brief Exception when library class failed
 */

/*! \fn LibraryException::LibraryException(const std::string& userMessage)
 * \param userMessage message to display
 */

#endif
