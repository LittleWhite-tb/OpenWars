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

#include "Game/EditorEngine.h"

#include "Types/Vec2.h"

#include "Utils/Logger.h"

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

	unsigned int i = 1;

	USize2 winSize(480,320);
	bool needFullscreen=false;
	unsigned int mapWidth=15;
	unsigned int mapHeight=14;
	std::string loadMapName="";
	std::string mapName="save.map";
	std::string themeName="classic";

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
		else if ( strcmp(argv[i],"--mapWidth") == 0 )
		{
			if ( i+1 < static_cast<unsigned int>(argc) )
			{
				std::istringstream iss(argv[i+1]);
				iss >> mapWidth;
				if ( mapWidth < MAP_MIN_WIDTH )
				{
					LError << "The width for the map has to be higher or equal to " << MAP_MIN_WIDTH;
					return -1;
				}
				i+=2;
			}
			else
			{
				LError << "Missing option for --mapWidth!";
				return -1;
			}
		}
		else if ( strcmp(argv[i],"--mapHeight") == 0 )
		{
			if ( i+1 < static_cast<unsigned int>(argc) )
			{
				std::istringstream iss(argv[i+1]);
				iss >> mapHeight;
				if ( mapHeight < MAP_MIN_HEIGHT )
				{
					LError << "The width for the map has to be higher or equal to " << MAP_MIN_HEIGHT;
					return -1;
				}
				i+=2;
			}
			else
			{
				LError << "Missing option for --mapHeight!";
				return -1;
			}
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
		else if ( strcmp(argv[i],"--mapName") == 0 )
		{
			if ( i+1 < static_cast<unsigned int>(argc) )
			{
				mapName = std::string(argv[i+1]);
				i+=2;
			}
			else
			{
				LError << "Missing option for --mapName!";
				return -1;
			}
		}
		else if ( strcmp(argv[i],"--theme") == 0 )
		{
			if ( i+1 < static_cast<unsigned int>(argc) )
			{
				themeName = std::string(argv[i+1]);
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
	if ( pNE->init() == false )
	{
		return 1;
	}

	{
        if ( pNE->getWindow()->createWindow(winSize,32,needFullscreen,"OpenAWars Editor") )
        {
			EditorEngine* pEEngine = new EditorEngine(pNE);
			if ( pEEngine == NULL )
			{
				LError << "Fail to allocate memory for pEEngine";
			}
			else
			{
				try
				{
					
					if ( pEEngine->init() )
					{
						bool engineLoadingState = true;
						if ( !loadMapName.empty() )
						{
							engineLoadingState = pEEngine->Engine::load(loadMapName);
						}
						else
						{
							pEEngine->loadTheme(themeName);
							engineLoadingState &= pEEngine->load(UVec2(mapWidth, mapHeight));
						}
						if ( engineLoadingState )
						{
							pEEngine->run();
							pEEngine->saveMap(mapName);
						}
					}
				}
				catch ( EngineException& ee )
				{
					LError << ee.what();
				}

				delete pEEngine;
			}

            pNE->getWindow()->destroyWindow();
        }
	}

	// Stopping Native engine
	pNE->stop();
	delete pNE;

#ifdef _DEBUG
	// Final check
	LDebug << "Number of Sprite Alloc/Destruction: " << nbSAllocation << " / " << nbSDestruction;
	LDebug << "Number of Animated Sprite Alloc/Destruction: " << nbASAllocation << " / " << nbASDestruction;
	LDebug << "Number of Font Alloc/Destruction: " << nbFAllocation << " / " << nbFDestruction;
#endif

	Logger::deleteLogger();

	return 0;
}
