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

#include "SDL_Engine.h"

#include <SDL/SDL.h>

#include "SDL_Window.h"
#include "SDL_Renderer.h"
#include "SDL_Input.h"
#include "SDL_Time.h"

#include "../../../Utils/Logger.h"

bool SDL_Engine :: init(void)
{
	if ( SDL_Init(SDL_INIT_VIDEO) != 0 )
	{
		LError << "Error while initializing SDL -> SDL_INIT_VIDEO";
		return false;
	}

	pWin = new SDL_Window();
	pRenderer = new SDL_Renderer(pWin);
	pTime = new SDL_Time();
	pInput = new SDL_Input();

	if ( pWin == NULL || pRenderer == NULL || pTime == NULL || pInput == NULL )
	{
		LError << "Fail to allocate memory for SDL_Engine components";
		return false;
	}

	LDebug << "Native Engine SDL started";
	return true;
}

bool SDL_Engine :: stop(void)
{
	delete pTime; pTime = NULL;
	delete pInput; pInput = NULL;
	delete pRenderer; pRenderer = NULL;
	delete pWin; pWin = NULL;

	SDL_Quit();

	LDebug << "Native Engine SDL stopped";

	return true;
}