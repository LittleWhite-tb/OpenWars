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
#include <sstream>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "NEngine/NE.h"
#include "NEngine/NEngine.h"

#include "Game/GameEngine.h"

#include "Types/Vec2.h"

#include "Utils/Logger.h"
#include "Utils/Scaler.h"

#include "globals.h"

int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;

	unsigned int i = 1;

	USize2 winSize(640,480);
	bool needFullscreen=false;
	std::string loadMapName= MAP_PATH "maw.map";

	// Check the arguments passed
	while ( i < static_cast<unsigned int>(argc) )
	{
		if ( strcmp(argv[i],"--width") == 0 )
		{
			if ( i+1 < static_cast<unsigned int>(argc) )
			{
				std::istringstream iss(argv[i+1]);
				iss >> winSize.width;
				i+=2;
			}
			else
			{
				LError << "Missing option for --width!";
				return -1;
			}
		}
		else if ( strcmp(argv[i],"--height") == 0 )
		{
			if ( i+1 < static_cast<unsigned int>(argc) )
			{
				std::istringstream iss(argv[i+1]);
				iss >> winSize.height;
				i+=2;
			}
			else
			{
				LError << "Missing option for --height!";
				return -1;
			}
		}
		else if ( strcmp(argv[i],"--fullscreen") == 0 )
		{
			needFullscreen = true;
			i++;
		}
		else if ( strcmp(argv[i],"--load") == 0 )
		{
			if ( i+1 < static_cast<unsigned int>(argc) )
			{
				loadMapName = std::string(argv[i+1]);
				i+=2;
			}
			else
			{
				LError << "Missing option for --mapName!";
				return -1;
			}
		}
	}

	// Starting the native engine
	if ( NE::init(winSize,32,needFullscreen,"OpenAWars") == false )
	{
		return 1;
	}

	{
		int flags = IMG_INIT_PNG;
		int initIMG = IMG_Init(flags);

		// Starting SDL_image and SDL_ttf
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

				Scaler::initScaleFactor();

				GameEngine gEngine;
					
				if ( gEngine.init() )
				{
					bool engineLoadingState = false;

					engineLoadingState = gEngine.load(loadMapName);
					if ( engineLoadingState )
					{
						gEngine.run();
					}
				}
			}

			// Stopping SDL_ttf
			TTF_Quit();
			// Bye bye SDL_image
			IMG_Quit();
		}
	}

	// Stopping the Native Engine
	NE::stop();

	Logger::deleteLogger();

	return 0;
}
