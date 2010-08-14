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

#include "Renderer_sdl.h"

#include <SDL/SDL.h>

#include <cassert>

#include "../Window.h"
#include "../Sprite.h"

#include "../../Utils/Logger.h"

RSDL :: RSDL(void)
	:Renderer(RAPI_SDL)
{
	LDebug << "RSDL created";
}

RSDL :: ~RSDL(void)
{
	LDebug << "RSDL deleted";
}

bool RSDL :: clearScreen(Window& window)
{
	SDL_Surface* pWindowSurface = window.getWindowSurface();

	LDebug << "RSDL :: clearScreen";

	SDL_FillRect(pWindowSurface,NULL,SDL_MapRGB(pWindowSurface->format,0,0,0));

	return true;
}

bool RSDL :: drawTile(Window& window, SDL_Rect& tile, const SDL_Color& colour)
{
	SDL_Surface* pWindowSurface = window.getWindowSurface();

	LDebug << "RSDL :: drawTile from colour (pos: " << tile.x << "x" << tile.y << " size: " << tile.w << "x" << tile.h << " colour: " << static_cast<int>(colour.r) << "," <<  static_cast<int>(colour.g) << "," << static_cast<int>(colour.b) << "," << static_cast<int>(colour.unused) << ")";

	if ( SDL_FillRect(pWindowSurface, &tile, SDL_MapRGBA(pWindowSurface->format, colour.r, colour.g, colour.b, colour.unused)) == -1 )
	{
		LWarning << "Failed to draw";
		return false;
	}

	return true;
}

bool RSDL :: drawTile(Window& window, Sprite& sprite, const SDL_Rect& pos)
{
	LDebug << "RSDL :: drawTile from Sprite @ " << pos.x << ";" << pos.y;

	

	return true;
}

bool RSDL :: drawBackground(Window& window, SDL_Surface* const pImage)
{
	assert(pImage);

	(void)window;

	LDebug << "RSDL :: drawBackground";

	return true;
}
