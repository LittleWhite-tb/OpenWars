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

#include "SDL_Renderer.h"

#include <SDL/SDL.h>

#include <cassert>

#include "NEngine/Types/Vec2.h"
#include "NEngine/Types/Colour.h"
#include "NEngine/Types/Rect.h"

#include "NEngine/NEngine.h"
#include "NEngine/Window.h"
#include "NEngine/Sprite.h"

bool NE :: SDL_Renderer :: clearScreen(const Colour& colour)
{
    SDL_Surface* pSDLWindow = static_cast<SDL_Surface*>(this->getNativeWindow());

    if ( SDL_FillRect(pSDLWindow,NULL,SDL_MapRGB(pSDLWindow->format,colour.r,colour.g,colour.b)) != 0 )
    {
        NEWarning << "Fail to clear the screen\n";
        return false;
    }

    return true;
}

bool NE :: SDL_Renderer :: drawRect(const Rect& tile, const Colour& colour)const
{
    SDL_Surface* pSDLWindow = static_cast<SDL_Surface*>(this->getNativeWindow());
    SDL_Rect sdlTile = { static_cast<short int>(tile.position.x),
                        static_cast<short int>(tile.position.y),
                        static_cast<unsigned short int>(tile.size.width),
                        static_cast<unsigned short int>(tile.size.height) };

    if ( SDL_FillRect(pSDLWindow, &sdlTile, SDL_MapRGBA(pSDLWindow->format, colour.r, colour.g, colour.b, colour.a)) == -1 )
    {
        NEWarning << "Failed to draw\n";
        return false;
    }

    return true;
}

bool NE :: SDL_Renderer :: drawSurface(const IVec2& position,const Sprite* pSprite)const
{
    assert(pSprite);

    return this->drawSurface(position,pSprite,Rect(IVec2(),pSprite->getSize()));
}

bool NE :: SDL_Renderer :: drawSurface(const IVec2& position, const Sprite* pSprite, const Colour& mask)const
{
    assert(pSprite);

    return this->drawSurface(position,pSprite,Rect(IVec2(),pSprite->getSize()),mask);
}

bool NE :: SDL_Renderer :: drawSurface(const IVec2& position,const Sprite* pSprite, const Rect& srcRect)const
{
    assert(pSprite);

    SDL_Surface* pSDLWindow = static_cast<SDL_Surface*>(this->getNativeWindow());
    SDL_Surface* pSDLSurface = static_cast<SDL_Surface*>(this->getNativeSurface(pSprite));
    SDL_Rect sdlDestRect = { static_cast<short int>(position.x),
                        static_cast<short int>(position.y),
                        static_cast<unsigned short int>(srcRect.size.width),
                        static_cast<unsigned short int>(srcRect.size.height) };

    SDL_Rect sdlSrcRect = { static_cast<short int>(srcRect.position.x),
                        static_cast<short int>(srcRect.position.y),
                        static_cast<unsigned short int>(srcRect.size.width),
                        static_cast<unsigned short int>(srcRect.size.height) };

    if ( SDL_BlitSurface(pSDLSurface, &sdlSrcRect, pSDLWindow, &sdlDestRect) != 0 )
    {
        NEWarning << "Fail to blit the surface\n";
        return false;
    }

    return true;
}

bool NE :: SDL_Renderer :: drawSurface(const IVec2& position,const Sprite* pSprite, const Rect& srcRect, const Colour& mask)const
{
    assert(pSprite);

    SDL_Surface* pSDLWindow = static_cast<SDL_Surface*>(this->getNativeWindow());
    SDL_Surface* pSDLSurface = static_cast<SDL_Surface*>(this->getNativeSurface(pSprite));
    SDL_Rect sdlDestRect = { static_cast<short int>(position.x),
                        static_cast<short int>(position.y),
                        static_cast<unsigned short int>(srcRect.size.width),
                        static_cast<unsigned short int>(srcRect.size.height) };

    SDL_Rect sdlSrcRect = { static_cast<short int>(srcRect.position.x),
                        static_cast<short int>(srcRect.position.y),
                        static_cast<unsigned short int>(srcRect.size.width),
                        static_cast<unsigned short int>(srcRect.size.height) };

    SDL_Surface* pSrc = SDL_CreateRGBSurface(SDL_SWSURFACE | SDL_SRCALPHA, srcRect.size.width, srcRect.size.height, pSDLSurface->format->BitsPerPixel, mask.r,mask.g,mask.b, mask.a);
    if ( pSrc == NULL )
    {
        NEWarning << "Fail to produce the copy of the sprite for RSDL :: drawTile\n";
        return false;

    }

    // The masking is done in CreateRGBSurface
    if ( SDL_BlitSurface(pSDLSurface, &sdlSrcRect, pSrc, NULL)  != 0 )
    {
        NEWarning << "Fail to copy the sprite in a temporary surface\n";
        SDL_FreeSurface(pSrc);
        return false;
    }

    // Making a pre blit with the original image
    if ( SDL_BlitSurface(pSDLSurface, &sdlSrcRect, pSDLWindow, &sdlDestRect)  != 0 )
    {
        NEWarning << "Fail to copy the sprite in a temporary surface\n";
        SDL_FreeSurface(pSrc);
        return false;
    }

    // Apply the filter
    if ( SDL_BlitSurface(pSrc, NULL, pSDLWindow, &sdlDestRect) != 0 )
    {
        NEWarning << "Fail to blit the surface\n";
        SDL_FreeSurface(pSrc);
        return false;
    }

    SDL_FreeSurface(pSrc);

    return true;
}

bool NE :: SDL_Renderer :: updateWindow(void)
{
    SDL_Surface* pSDLWindow = static_cast<SDL_Surface*>(this->getNativeWindow());

    // We are using SDL_Flip since SDL_UpdateRect does not do the job on GP2X
    // SDL_UpdateRect(pSDLWindow,0,0,0,0);
    if ( SDL_Flip(pSDLWindow) != 0 )
    {
        NEError << "Fail to draw on the screen\n";
        return false;
    }

    return true;
}
