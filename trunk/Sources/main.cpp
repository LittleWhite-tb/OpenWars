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

#include <iostream>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "Engine/Window.h"
#include "Engine/Renderer.h"
#include "Engine/ResourcesManager/SpriteManager.h"
#include "Engine/Sprite.h"

#include "Types/Vec2.h"

#include "Utils/Logger.h"

int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;

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

			SDL_Rect rect = { 64, 64, 128, 128 };
			IVec2 iv2(256,256);
			SDL_Color col = { 255, 0, 0, 128 };
			Sprite s(sm,"./data/sprite.png");
			Sprite s2(sm,"./data/sprite.png");

			std::vector<ResolutionInfo> riList;

			win.getResolutionsAvailable(false,riList);
			win.setCaption("Hello SDL","");
			win.showCursor(false);

			// Window test
			win.openWindow(640,480,32,false,false);
			r->clearScreen(win);
			r->drawTile(win,rect,col);
			r->drawTile(win,s,iv2);
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