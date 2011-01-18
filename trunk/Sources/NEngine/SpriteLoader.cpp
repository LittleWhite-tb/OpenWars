#ifndef DOXYGEN_IGNORE_TAG
/**
OpenAWars is an open turn by turn strategic game aiming to recreate the feeling of advance (famicon) wars (c)
Copyright (C) 2010  Alexandre LAURENT

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

#include "Sprite.h"
#include "Scaler.h"

#include "../Utils/Logger.h"

NE::SpriteLoader :: ~SpriteLoader(void)
{
    for( std::map<std::string, NE::Sprite*>::const_iterator itSprite = spritesBank.begin() ; itSprite != spritesBank.end() ; ++itSprite )
	{
		delete (itSprite->second);
	}
	spritesBank.clear();
}

NE::Sprite* NE::SpriteLoader :: loadSpriteFromFile(const std::string& fileName)
{
    if ( spritesBank.find(fileName) == spritesBank.end() ) // Not found
    {
    
        Sprite* pSprite = loadSprite(fileName);
        if ( pSprite == NULL )
        {
            LError << "NE::SpriteLoader (Fail to load the Sprite ('" << fileName << "')";
            return NULL;
        }
        
        // Now scaling
        Sprite* pScaledSprite = pScaler->scale(pSprite);
        if ( pScaledSprite == NULL )
        {
            // We keep unscale one
            spritesBank[fileName] = pSprite;
        }
        else if ( pScaledSprite == pSprite )
        {
            spritesBank[fileName] = pSprite;
        }
        else
        {
            spritesBank[fileName] = pScaledSprite;
            delete pSprite;
        }
        
        return spritesBank[fileName];
    }
    else
    {
        return spritesBank[fileName];
    }
}
