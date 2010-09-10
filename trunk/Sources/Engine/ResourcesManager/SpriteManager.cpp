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
		if ( itSprite->second.pSprite != itSprite->second.pScaledSprite ) // To avoid some double free corruption, when scaling fails
		{
			SDL_FreeSurface(itSprite->second.pScaledSprite);
		}
		SDL_FreeSurface(itSprite->second.pSprite);
	}
	spritesBank.clear();

	LDebug << "SpriteManager deleted";
}

SDL_Surface* SpriteManager :: getSurface(const std::string& fileName,const bool needScaling)
{
	LDebug << "SpriteManager :: getSurface (" << fileName << ") need scaling:" << needScaling;

	if ( spritesBank.find(fileName) == spritesBank.end() )
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
				spritesBank[fileName].pScaledSprite = pTmpScaledSurface;
			}
			else
			{
				// In this case, the scaled version is the same than the normal version
				LWarning << "Failed to scale the surface";
				spritesBank[fileName].pScaledSprite = pTmpSurface;
			}

			// Enable RLE acceleration
			if ( SDL_SetColorKey(pTmpSurface, SDL_RLEACCEL, pTmpSurface->format->colorkey) != 0 )
			{
				LWarning << "Fail to apply the RLE acceleration";
			}
			if ( SDL_SetColorKey(pTmpScaledSurface, SDL_RLEACCEL, pTmpScaledSurface->format->colorkey) != 0 )
			{
				LWarning << "Fail to apply the RLE acceleration for the scaled surface";
			}
		}
	}

	if ( needScaling )
	{
		return spritesBank[fileName].pScaledSprite;
	}
	else
	{
		return spritesBank[fileName].pSprite;
	}
}