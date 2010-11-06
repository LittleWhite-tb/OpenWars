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

#include "SpriteManager.h"

#include <map>
#include <string>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "../../Utils/Logger.h"
#include "../../Utils/Scaler.h"

SpriteManager :: SpriteManager(void)
{
	LDebug << "SpriteManager created";
}

SpriteManager :: ~SpriteManager(void)
{
	for( std::map<std::string, SurfacePair>::const_iterator itSprite = spritesBank.begin() ; itSprite != spritesBank.end() ; ++itSprite )
	{
		SDL_FreeSurface(itSprite->second.pSprite);
	}
	spritesBank.clear();

	LDebug << "SpriteManager deleted";
}

SDL_Surface* SpriteManager :: getSurface(const std::string& fileName,const bool needScaling)
{
	LDebug << "SpriteManager :: getSurface (" << fileName << ") need scaling:" << needScaling;

	if ( spritesBank.find(fileName) == spritesBank.end() ) // Not found
	{
		SDL_Surface* pTmpSurface = IMG_Load(fileName.c_str());
		if ( pTmpSurface == NULL )
		{
			LError << "Fail to load image '" << fileName.c_str() << "' (" << IMG_GetError() << ")";
		}
		else
		{
			// We save the normal version of the picture
			spritesBank[fileName].pSprite = pTmpSurface;

			SDL_Surface* pTmpScaledSurface = Scaler::scale(pTmpSurface);
			if ( pTmpScaledSurface != NULL )
			{
				spritesBank[fileName].pSprite = pTmpScaledSurface;
				SDL_FreeSurface(pTmpSurface);	// Delete the unscaled sprite
			}
			else
			{
				// In this case, the scaled version is the same than the normal version
				LWarning << "Failed to scale the surface";
				spritesBank[fileName].pSprite = pTmpSurface;
			}
/*
			// Update the Surface to have an optimised for our screen
			{
				SDL_Surface* pTmpOptimisedSurface = SDL_DisplayFormat(spritesBank[fileName].pSprite);
				if ( pTmpOptimisedSurface != NULL )
				{
					SDL_Surface* pOldSurface = spritesBank[fileName].pSprite;
					// We save the optimised picture
					spritesBank[fileName].pSprite = pTmpOptimisedSurface;
				    
					// We delete old one
					SDL_FreeSurface(pOldSurface);
				}
				else
				{
					// else nothing happened
					LWarning << "Fail to have enough memory to optimise the sprites";
				}
			}
*/
			// Enable RLE acceleration
			if ( SDL_SetColorKey(spritesBank[fileName].pSprite, SDL_RLEACCEL, spritesBank[fileName].pSprite->format->colorkey) != 0 )
			{
				LWarning << "Fail to apply the RLE acceleration";
			}
		}
	}

	return spritesBank[fileName].pSprite;
}