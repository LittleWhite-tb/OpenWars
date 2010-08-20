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

#include <string>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "Engine/Window.h"
#include "Engine/Renderer.h"
#include "Engine/ResourcesManager/SpriteManager.h"
#include "Engine/AnimatedSprite.h"
#include "Engine/Sprite.h"

#include "Game/Map.h"

#include "Types/Vec2.h"

#include "Utils/Logger.h"

#include "globals.h"

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
		Renderer* r = RendererFactory(RAPI_SDL);
		int flags = IMG_INIT_PNG;
		int initIMG = IMG_Init(flags);

		// Starting SDL_image
		if ( (initIMG & flags) != flags )
		{
			LError << "Fail to init the SDL_image with PNG support (" << IMG_GetError() << ")";
		}
		else
		{
			SpriteManager sm;
			AnimatedSprite as(sm,"./data/asprite.png",32,32,1500);
			Map m(sm,MAP_PATH + std::string("m1.txt"));

			std::vector<ResolutionInfo> riList;

			win.getResolutionsAvailable(false,riList);
			win.setCaption("Hello SDL","");
			win.showCursor(false);

			// Window test
			win.openWindow(640,480,32,false,false);

			r->clearScreen(win);
			
			startTime = SDL_GetTicks();
			while ( SDL_GetTicks() - startTime < 15000 )
			{
				r->drawTile(win,as,IVec2(400,400),SDL_GetTicks());
				SDL_UpdateRect(win.getWindowSurface(),0,0,0,0);
			}

			r->clearScreen(win);
			if ( m.isValidMap() )
			{
				m.draw(win,*r,0);
			}
			SDL_UpdateRect(win.getWindowSurface(),0,0,0,0);
			SDL_Delay(5000);

			// Bye bye SDL_image
			IMG_Quit();
		}

		delete r;
	}

	// Bye bye SDL
	SDL_Quit();

	Logger::deleteLogger();

	return 0;
}