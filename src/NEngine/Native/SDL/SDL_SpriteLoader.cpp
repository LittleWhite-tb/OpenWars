#ifndef DOXYGEN_IGNORE_TAG
/**
NEngine: Native Engine abstracts multimedia libraries such as SDL, SFML, Allegro
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

website: https://github.com/LittleWhite-tb/NEngine
e-mail: lw.demoscene@gmail.com
**/
#endif

#include "SDL_SpriteLoader.h"

#include <SDL/SDL.h>

#include <string>

#include "NEngine/NEngine.h"
#include "SDL_Sprite.h"

NE::Sprite* NE::SDL_SpriteLoader :: loadSpriteFromFile(const std::string& fileName, const Colour& transparencyColour)
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
            Uint32 colorkey = SDL_MapRGB(pOptimisedSurface->format, transparencyColour.r, transparencyColour.g, transparencyColour.b);
            if ( SDL_SetColorKey(pOptimisedSurface, SDL_RLEACCEL | SDL_SRCCOLORKEY, colorkey ) == -1 )
            {
                NEWarning << "Fail to set transparency to '" << fileName << "'\n";
            }

            // We replace the pointer to the new optimised surface
            pSurface = pOptimisedSurface;
        }
        else
        {
            NEError << "Fail to optimise sprite '" << fileName << "'\n";
        }

        NE::SDL_Sprite* pSprite = new NE::SDL_Sprite(pSurface);
        if ( pSprite == NULL )
        {
            NEError << "Fail to allocate memory for a SDL_Sprite\n";
        }

        return pSprite;
    }

    // NEError << "Fail to load a sprite from file: " << SDL_GetError() << "\n";
    return NULL;
}
