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

#include "SDL_SpriteLoaderSDLI.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include "SDL_Sprite.h"
#include <NEngine/Exceptions/ConstructionFailedException.h>
#include <NEngine/Utils/Logger.h>

NE :: SDL_SpriteLoaderSDLI :: SDL_SpriteLoaderSDLI(const int flags)
{
    int initIMG = IMG_Init(flags);

    // Starting SDL_image
    if ( (initIMG & flags) != flags )
    {
        LError << "Fail to init the SDL_image with PNG support (" << IMG_GetError() << ")";
        throw ConstructionFailedException("SDL_SpriteLoaderSDLI");
    }
}

NE :: SDL_SpriteLoaderSDLI :: ~SDL_SpriteLoaderSDLI(void)
{
    IMG_Quit();
}

NE :: Sprite* NE :: SDL_SpriteLoaderSDLI :: loadSprite(const std::string& fileName)
{
    SDL_Surface* pSurface = IMG_Load(fileName.c_str());

    // No optimisation is possible for these kind of surface

    if ( pSurface != NULL )
    {
        NE::SDL_Sprite* pSprite = new NE::SDL_Sprite(pSurface);
        if ( pSprite == NULL )
        {
            LError << "Fail to allocate memory for a SDL_Sprite";
        }

        return pSprite;
    }

    LError << "Fail to load a sprite from file: " << IMG_GetError();
    return NULL;
}
