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

SpriteManager :: SpriteManager(void)
{
	LDebug << "SpriteManager created";
}

SpriteManager :: ~SpriteManager(void)
{
	for( std::map<std::string, SDL_Surface*>::const_iterator itSprite = spriteBank.begin() ; itSprite != spriteBank.end() ; ++itSprite )
	{
		SDL_FreeSurface(itSprite->second);
	}
	spriteBank.clear();

	LDebug << "SpriteManager deleted";
}

SDL_Surface* SpriteManager :: getSurface(const std::string& fileName)
{
	LDebug << "SpriteManager :: getSurface (" << fileName << ")";

	if ( spriteBank.find(fileName) == spriteBank.end() )
	{
		spriteBank[fileName] = IMG_Load(fileName.c_str());
		if ( spriteBank[fileName] == NULL )
		{
			LError << "Fail to load image '" << fileName.c_str() << "' (" << IMG_GetError() << ")";
		}
	}
	else // Here the case when the sprite is already constructed
	{
		return spriteBank[fileName];
	}

	return spriteBank[fileName];
}