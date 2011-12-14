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

#include "SpriteLoader.h"

#include "NEngine/NEngine.h"
#include "NEngine/ISpriteLoader.h"
#include "NEngine/Exceptions/FileNotFoundException.h"

#include <cassert>

NE::SpriteLoader::~SpriteLoader()
{
    for ( std::list<NE::ISpriteLoader*>::const_iterator itLoader = m_loaders.begin() ; 
          itLoader != m_loaders.end() ;
          ++itLoader )
    {
        delete (*itLoader);
    }

    m_loaders.clear();
}

void NE::SpriteLoader::registerLoader(NE::ISpriteLoader* pLoader)
{
    assert(pLoader);

    m_loaders.push_back(pLoader);
}

const NE::Sprite* NE::SpriteLoader::loadSpriteFromFile(const std::string& fileName)
{
    const NE::Sprite* pSprite = m_bank.get(fileName);
    
    if ( pSprite == NULL ) // It was not in the bank
    {
        for ( std::list<NE::ISpriteLoader*>::const_iterator itLoader = m_loaders.begin() ; 
            itLoader != m_loaders.end() ;
            ++itLoader )
        {
            pSprite = (*itLoader)->loadSpriteFromFile(fileName,m_transparencyColour);
            if ( pSprite != NULL )  // It is loaded, we can stop
            {
                m_bank.add(fileName,pSprite);
                break;
            }
        }

        // We gone through all loaders, and the sprite is not loaded ... so, error
        if ( pSprite == NULL )
        {
            NE::NEngine::logger().log(NE::LL_Error,"Fail to load sprite '%s'",fileName);
            throw FileNotFoundException(fileName);
        }
    }
    
    return pSprite;
}