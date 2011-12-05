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

#include "SDL_SpriteLoader.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include "SDL_Sprite.h"
#include <NEngine/Utils/Logger.h>

NE::Sprite* NE::SDL_SpriteLoader :: loadSprite(const std::string& fileName)
{
    SDL_Surface* pSurface = SDL_LoadBMP(fileName.c_str());
    if ( pSurface != NULL )
    {
        // We optimise the texture to match the Screen surface
        SDL_Surface* pOptimisedSurface = SDL_DisplayFormat(pSurface);
        if ( pOptimisedSurface != NULL )
        {
            // We clean old surface
            SDL_FreeSurface(pSurface);

            // We set the color
            Uint32 colorkey = SDL_MapRGB(pOptimisedSurface->format, m_transparancyColour.r, m_transparancyColour.g, m_transparancyColour.b);
            if ( SDL_SetColorKey(pOptimisedSurface, SDL_RLEACCEL | SDL_SRCCOLORKEY, colorkey ) == -1 )
            {
                LWarning << "Fail to set transparancy to '" << fileName << "'";
            }

            // We replace the pointer to the new optimised surface
            pSurface = pOptimisedSurface;
        }
        else
        {
            LError << "Fail to optimise sprite '" << fileName << "'";
        }

        NE::SDL_Sprite* pSprite = new NE::SDL_Sprite(pSurface);
        if ( pSprite == NULL )
        {
            LError << "Fail to allocate memory for a SDL_Sprite";
        }

        return pSprite;
    }

    LError << "Fail to load a sprite from file: " << SDL_GetError();
    return NULL;
}
