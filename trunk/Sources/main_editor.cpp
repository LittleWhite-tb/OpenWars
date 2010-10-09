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

#include <string>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "Engine/Window.h"

#include "Engine/ResourcesManager/SpriteManager.h"
#include "Engine/ResourcesManager/FontManager.h"
#include "Engine/AnimatedSprite.h"
#include "Engine/Sprite.h"

#include "Game/EditorEngine.h"

#include "Types/Vec2.h"

#include "Utils/Logger.h"
#include "Utils/Scaler.h"

#include "globals.h"

#ifdef _DEBUG
	// Some specials globals to check if all memory cleaning is properly done
	unsigned int nbASAllocation = 0;
	unsigned int nbASDestruction = 0;
	unsigned int nbSAllocation = 0;
	unsigned int nbSDestruction = 0;
	unsigned int nbFAllocation = 0;
	unsigned int nbFDestruction = 0;
#endif

int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;

	Uint32 startTime = 0;

	// Starting SDL
	if ( SDL_Init(SDL_INIT_VIDEO) == -1 )
	{
		LError << "Error while initializing SDL -> SDL_INIT_VIDEO";
		return 1;
	}

	{
		Window win;

		int flags = IMG_INIT_PNG;
		int initIMG = IMG_Init(flags);

		// Starting SDL_image 
		if ( (initIMG & flags) != flags )
		{
			LError << "Fail to init the SDL_image with PNG support (" << IMG_GetError() << ")";
		}
		else
		{
			if ( TTF_Init() != 0 )
			{
				LError << "Fail to init the SDL_tff " << TTF_GetError() << ")";
			}
			else
			{
				std::vector<ResolutionInfo> riList;

				win.getResolutionsAvailable(false,riList);
				win.setCaption("OpenAWars Editor","");
				win.showCursor(false);

				// Window test
				if ( win.openWindow(640,480,32,false,false) )
				{
					Scaler::setScaleFactor(win);
					EditorEngine eEngine;
					
					if ( eEngine.init(&win, RAPI_SDL) )
					{
						if ( eEngine.load(UVec2(MAP_MIN_WIDTH, MAP_MIN_HEIGHT)) )
						{
							eEngine.run();
							eEngine.saveMap("mapTest.txt");
						}
					}
				}
			}

			// Stopping SDL_ttf
			TTF_Quit();
			// Bye bye SDL_image
			IMG_Quit();
		}
	}

	// Bye bye SDL
	SDL_Quit();

#ifdef _DEBUG
	// Final check
	LDebug << "Number of Sprite Alloc/Destruction: " << nbSAllocation << " / " << nbSDestruction;
	LDebug << "Number of Animated Sprite Alloc/Destruction: " << nbASAllocation << " / " << nbASDestruction;
	LDebug << "Number of Font Alloc/Destruction: " << nbFAllocation << " / " << nbFDestruction;
#endif

	Logger::deleteLogger();

	return 0;
}