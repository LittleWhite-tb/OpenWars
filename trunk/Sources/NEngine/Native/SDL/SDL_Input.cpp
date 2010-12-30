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

#include "SDL_Input.h"

#include <SDL/SDL.h>

void NE :: SDL_Input :: update()
{
	int nbKeys = 0;

	SDL_PumpEvents();
	pKeys = SDL_GetKeyState(&nbKeys);

	this->nbKeys = nbKeys;
}

NE::Input::ArrowsDirection NE :: SDL_Input :: getDirection(void)
{
	update();

	// Silly way to check it ... ( ToDo: Improve if possible )
	// Some cases are hidden, like DOWN and UP ... but I don't mind if the user is a bit silly ... :p
	if ( pKeys[SDLK_UP] )
	{
		if ( pKeys[SDLK_RIGHT] )
		{
			return AD_UPRIGHT;
		}
		else if ( pKeys[SDLK_LEFT] )
		{
			return AD_LEFTUP;
		}

		return AD_UP;
	}

	if ( pKeys[SDLK_DOWN] )
	{
		if ( pKeys[SDLK_RIGHT] )
		{
			return AD_RIGHTDOWN;
		}
		else if ( pKeys[SDLK_LEFT] )
		{
			return AD_DOWNLEFT;
		}

		return AD_DOWN;
	}

	if ( pKeys[SDLK_LEFT] )
	{
		return AD_LEFT;
	}
	else if ( pKeys[SDLK_RIGHT] )
	{
		return AD_RIGHT;
	}
	
	return AD_NONE;
}

NE::Input::Buttons NE :: SDL_Input :: getButtons(void)
{
	update();

	NE::Input::Buttons buttonPressed = 0;

	if ( pKeys[SDLK_q] )
	{
		buttonPressed |= Input::INPUT_A;
	}
	if ( pKeys[SDLK_w] )
	{
		buttonPressed |= Input::INPUT_B;
	}
	if ( pKeys[SDLK_a] )
	{
		buttonPressed |= Input::INPUT_X;
	}
	if ( pKeys[SDLK_s] )
	{
		buttonPressed |= Input::INPUT_Y;
	}
	if ( pKeys[SDLK_z] )
	{
		buttonPressed |= Input::INPUT_START;
	}
	if ( pKeys[SDLK_x] )
	{
		buttonPressed |= Input::INPUT_SELECT;
	}

	return buttonPressed;
}