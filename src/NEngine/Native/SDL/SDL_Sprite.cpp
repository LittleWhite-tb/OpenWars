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

#include "SDL_Sprite.h"

#include <SDL/SDL.h>

NE :: SDL_Sprite :: SDL_Sprite(SDL_Surface* pSprite)
	:Sprite(),pSurface(pSprite)
{
	/*
	if ( pSprite != NULL )
	{
		SDL_Surface* pOptimisedSurface = SDL_DisplayFormat(pSprite);
		if ( pOptimisedSurface != NULL )
		{
			pSurface = pOptimisedSurface;
		}
		else
		{
			LWarning << "Fail to optimise surface for screen";
			pSurface = pSprite;
		}
	}
	*/
}

NE :: SDL_Sprite :: ~SDL_Sprite(void)
{
	SDL_FreeSurface(this->pSurface);
}

USize2 NE :: SDL_Sprite :: getSize(void)const
{
	return USize2(pSurface->w,pSurface->h);
}
