#ifndef SPRITEBANK_HPP
#define SPRITEBANK_HPP

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

#include <map>
#include <string>

#include <cassert>

#include "Utils/Logger.h"

namespace NE
{
    
    template <typename T>
    class Bank
    {
    private:

        std::map<std::string, const T*> m_bank;  /*!< Bank saving the Sprite loaded */

    public:

        ~Bank()
        {
            for( std::map<std::string, const T*>::const_iterator itSprite = m_bank.begin() ; itSprite != m_bank.end() ; ++itSprite )
            {
                delete (itSprite->second);
            }
            m_bank.clear();
        }

        void add(const std::string& name, const T* pResource)
        {
            assert(pResource);

            // Problem detection
            if ( exist(name) )
            {
                LWarning << "NE::Bank : '" << name << " is already in the Bank (not overwrittin)";
                return;
            }

            // Adding the entry
            m_bank[name] = pResource;
        }

        bool exist(const std::string& name)const
        {
            if ( m_bank.find(name) != m_bank.end() )
            {
                return true;
            }

            return false;
        }

        const T* get(const std::string& name)const
        {
            std::map<std::string, const T*>::const_iterator itT = m_bank.find(name);

            if (itT == m_bank.end())
            {
                return NULL;
            }// ToDO throw exception ?

            return itT->second;
        }
    };
}

#endif