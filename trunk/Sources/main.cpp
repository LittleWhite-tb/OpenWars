#ifndef DOXYGEN_IGNORE_TAG
/**
OpenAWars is an open turn by turn strategic game aiming to recreate the feeling of advance (famicon) wars (c)
Copyright (C) 2010-2011  Alexandre LAURENT

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
#include <cstring>

#include "NEngine/NEngine.h"
#include "NEngine/Window.h"
#include "NEngine/Native/SDL/SDL_Engine.h"

#include "Game/GameEngine.h"

#include "Types/Vec2.h"

#include "Utils/Logger.h"

#include "globals.h"

int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;

	unsigned int i = 1;

	USize2 winSize(480,320);
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
	NE::NEngine* pNE = new NE::SDL_Engine();
	if ( pNE->init()  == false )
	{
		return 1;
	}

	{
        if ( pNE->getWindow()->createWindow(winSize,32,needFullscreen,"OpenAWars") )
        {
            GameEngine* pGEngine = new GameEngine(pNE);
			if ( pGEngine == NULL )
			{
				LError << "Fail to allocate GameEngine";
			}
            else if ( pGEngine->init() )
            {
                bool engineLoadingState = true;

				engineLoadingState &= pGEngine->load();
                
                if ( engineLoadingState )
                {
                    pGEngine->run();
                }
            }

			delete pGEngine;

            pNE->getWindow()->destroyWindow();
        }
	}

	// Stopping the Native Engine
	pNE->stop();
	delete pNE;

	Logger::deleteLogger();

	return 0;
}
