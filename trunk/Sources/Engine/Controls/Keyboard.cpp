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

#include "Keyboard.h"

#include <SDL/SDL.h>

#include <cassert>

#include "../../Utils/Logger.h"

Keyboard :: Keyboard(void)
	:keys(NULL)
{
	LDebug << "Keyboard created";

	this->update();	// We directly update the keys array to have a valid array in any cases
}

Keyboard :: ~Keyboard(void)
{
	// The pointer doesn't have to be freed because it's SDL internal array

	LDebug << "Keyboard deleted";
}

unsigned char Keyboard :: isEscapePressed(void)const
{
	LDebug << "Keyboard isEscapePressed (" << static_cast<int>(keys[SDLK_ESCAPE]) << ")";

	return keys[SDLK_ESCAPE];
}

ArrowsDirection Keyboard :: getDirectionPressed(void)const
{
	// Silly way to check it ... ( ToDo: Improve if possible )
	// Some cases are hidden, like DOWN and UP ... but I don't mind if the user is a bit silly ... :p
	if ( keys[SDLK_UP] )
	{
		if ( keys[SDLK_RIGHT] )
		{
			return AD_UPRIGHT;
		}
		else if ( keys[SDLK_LEFT] )
		{
			return AD_LEFTUP;
		}

		return AD_UP;
	}

	if ( keys[SDLK_DOWN] )
	{
		if ( keys[SDLK_RIGHT] )
		{
			return AD_RIGHTDOWN;
		}
		else if ( keys[SDLK_LEFT] )
		{
			return AD_DOWNLEFT;
		}

		return AD_DOWN;
	}

	if ( keys[SDLK_LEFT] )
	{
		return AD_LEFT;
	}
	else if ( keys[SDLK_RIGHT] )
	{
		return AD_RIGHT;
	}
	
	return AD_NONE;
}

unsigned char Keyboard :: isKey(unsigned int key)
{
	assert(static_cast<int>(key) < nbKeys);

	return keys[key];
}

void Keyboard :: update(void)
{
	int nbKeys = 0;

	LDebug << "Keyboard :: update";

	SDL_PumpEvents();
	keys = SDL_GetKeyState(&nbKeys);

	this->nbKeys = nbKeys;
}