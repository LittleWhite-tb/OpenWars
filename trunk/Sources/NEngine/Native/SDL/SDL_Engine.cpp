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
#include "SDL_Keyboard.h"
#include "SDL_Joy.h"
#include "SDL_Time.h"
#include "SDL_Sprite.h"
#include "SDL_SpriteLoader.h"
#include "SDL_SpriteFactory.h"

#include "../../../Utils/Logger.h"

bool NE :: SDL_Engine :: initAPI(void)
{
	if ( SDL_Init(SDL_INIT_VIDEO) != 0 )
	{
		LError << "Error while initializing SDL -> SDL_INIT_VIDEO";
		return false;
	}

	pWin = new NE::SDL_Window();
	pRenderer = new NE::SDL_Renderer(pWin);
	pTime = new NE::SDL_Time();
	pSpriteLoader = new NE::SDL_SpriteLoader();
	pSpriteFactory = new NE::SDL_SpriteFactory();

	if ( pWin == NULL || pRenderer == NULL || pTime == NULL || pSpriteLoader == NULL || pSpriteFactory == NULL )
	{
		LError << "Fail to allocate memory for SDL_Engine components";
		return false;
	}
    
    pInputManager->registerController(new SDL_Keyboard());
    pInputManager->registerController(new SDL_Joy());
    
	LDebug << "Native Engine SDL started";
	return true;
}

bool NE :: SDL_Engine :: stopAPI(void)
{
	delete pSpriteLoader; pSpriteLoader = NULL;
	delete pTime; pTime = NULL;
	delete pRenderer; pRenderer = NULL;
	delete pWin; pWin = NULL;

	SDL_Quit();

	LDebug << "Native Engine SDL stopped";

	return true;
}
