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

#include "Engine/Window.h"
#include "Engine/Renderer.h"
#include "Engine/ResourcesManager/SpriteManager.h"
#include "Engine/AnimatedSprite.h"
#include "Engine/Sprite.h"

#include "Game/Map.h"
#include "Game/Camera.h"
#include "Game/Cursor.h"

#include "Types/Vec2.h"

#include "Utils/Logger.h"
#include "Utils/Scaler.h"

#include "UI/TileBar.h"

#include "globals.h"

#ifdef _DEBUG
	// Some specials globals to check if all memory cleaning is properly done
	unsigned int nbASAllocation = 0;
	unsigned int nbASDestruction = 0;
	unsigned int nbSAllocation = 0;
	unsigned int nbSDestruction = 0;

	unsigned int nbTAllocation = 0;
	unsigned int nbTDestruction = 0;
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
		Renderer* r = RendererFactory(&win, RAPI_SDL);
		int flags = IMG_INIT_PNG;
		int initIMG = IMG_Init(flags);

		// Starting SDL_image
		if ( (initIMG & flags) != flags )
		{
			LError << "Fail to init the SDL_image with PNG support (" << IMG_GetError() << ")";
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

				SpriteManager sm;
				Map m(sm,UVec2(15,10));
				Cursor c(sm,"./data/gfx/cursor_alpha.png",&m,UVec2(5,5));
				Camera cam;
				Keyboard kb;

				TileBar tb(sm,win);

				if ( m.isValidMap() )
				{
					while ( kb.isEscapePressed() == 0 )
					{
						r->clearScreen();

						m.draw(*r,cam,0);
						c.draw(*r,cam,0);

						tb.draw(*r,0);
						
						
						SDL_UpdateRect(win.getWindowSurface(),0,0,0,0);

						cam.update(c,m);

						if ( kb.isKey('a') || kb.isKey('A')  )
						{
							tb.open();
						}
						if ( kb.isKey('c') || kb.isKey('C')  )
						{
							tb.close();
						}
						if ( tb.isOpened() )
						{
							if ( kb.isKey(SDLK_LEFT) )
							{
								tb.moveLeft();
							}

							if ( kb.isKey(SDLK_RIGHT) )
							{
								tb.moveRight();
							}
						}
						else 
						{
							c.move(kb.getDirectionPressed());
							if ( kb.isKey(SDLK_SPACE) )
							{
								m.setTile(sm,c.getPosition(),tb.getSelected());
							}
						}

						kb.update();
						tb.update(0);
						SDL_Delay(15);
					}
				}

				m.save("map_test.txt");
			}

			// Bye bye SDL_image
			IMG_Quit();
		}

		delete r;
	}

	// Bye bye SDL
	SDL_Quit();

#ifdef _DEBUG
	// Final check
	LDebug << "Number of Sprite Alloc/Destruction: " << nbSAllocation << " / " << nbSDestruction;
	LDebug << "Number of Animated Sprite Alloc/Destruction: " << nbASAllocation << " / " << nbASDestruction;
	LDebug << "Number of Tile Alloc/Destruction: " << nbTAllocation << " / " << nbTDestruction;
#endif

	Logger::deleteLogger();

	return 0;
}