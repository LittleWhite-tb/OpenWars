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

#include "SDL_SpriteFactory.h"

#include <SDL/SDL.h>

#include "SDL_Sprite.h"

#include <NEngine/Utils/Logger.h>

NE::Sprite* NE::SDL_SpriteFactory :: createSprite(const Colour& colour, const USize2& spriteSize)
{
    SDL_Surface* pSurface = NULL;
	pSurface = SDL_CreateRGBSurface(SDL_HWSURFACE,spriteSize.width,spriteSize.height,32,
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
												0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000
#else
												0xff000000,  0x00ff0000, 0x0000ff00, 0x000000ff
#endif
												);
	if ( pSurface == NULL )
	{
		LError << "SDL_CreateRGBSurfaceFrom() failed (" << SDL_GetError() << ")";
		return NULL;
	}
/*
	// Put half alpha for the bar
	if ( SDL_SetAlpha(pSurface,SDL_SRCALPHA,128) != 0 )
	{
		LWarning << "SDL_SetAlpha failed for putting half alpha on the bar";
	}
*/
	
	unsigned int* pPixel = reinterpret_cast<unsigned int*>(pSurface->pixels);
	for ( int i = 0 ; i < pSurface->w * pSurface->h ; i++ )
	{
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
		*pPixel = (colour.a << 24) + (colour.b << 16) + (colour.g << 8) + colour.r;
#else
		*pPixel = (colour.r << 24 + (colour.g << 16) + (colour.b << 8) + colour.a;
#endif
		pPixel++;
	}
    
    return new SDL_Sprite(pSurface);
}
