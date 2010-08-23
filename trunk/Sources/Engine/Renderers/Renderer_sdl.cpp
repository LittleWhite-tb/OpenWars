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

#include "Renderer_sdl.h"

#include <SDL/SDL.h>

#include <cassert>

#include "../Window.h"
#include "../Sprite.h"
#include "../AnimatedSprite.h"

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

bool RSDL :: drawTile(Window& window, Sprite& sprite, const IVec2& pos)
{
	SDL_Rect r = { static_cast<Sint16>(pos.x) , static_cast<Sint16>(pos.y) , static_cast<Uint16>(sprite.getWidth()) , static_cast<Uint16>(sprite.getHeight()) };

	LDebug << "RSDL :: drawTile from Sprite @ " << pos;

	if ( SDL_BlitSurface(sprite.getSurface(), NULL, window.getWindowSurface(), &r) != 0 )
	{
		LWarning << "Fail to blit the surface";
		return false;
	}

	return true;
}

bool RSDL :: drawTile(Window& window, Sprite& sprite, SDL_Rect& srcRect, const IVec2& pos)
{
	SDL_Rect r = { static_cast<Sint16>(pos.x) , static_cast<Sint16>(pos.y) , srcRect.w , srcRect.h };

	LDebug << "RSDL :: drawTile from Sprite (" << srcRect.x << ";" << srcRect.y << ";" << srcRect.w << ";" << srcRect.h << ") @ " << pos;

	if ( SDL_BlitSurface(sprite.getSurface(), &srcRect, window.getWindowSurface(), &r) != 0 )
	{
		LWarning << "Fail to blit the surface";
		return false;
	}

	return true;
}

bool RSDL :: drawTile(Window& window, AnimatedSprite& aSprite, const IVec2& pos, const unsigned int time)
{
	SDL_Rect srcRect = aSprite.getSrcRect(time);
	SDL_Rect r = { static_cast<Sint16>(pos.x) , static_cast<Sint16>(pos.y) , static_cast<Uint16>(aSprite.getWidth()) , static_cast<Uint16>(aSprite.getHeight()) };

	LDebug << "RSDL :: drawTile from AnimatedSprite @ " << pos.x << ";" << pos.y;

	if ( SDL_BlitSurface(aSprite.getSurface(), &srcRect, window.getWindowSurface(), &r) != 0 )
	{
		LWarning << "Fail to blit the surface";
		return false;
	}
}

bool RSDL :: drawBackground(Window& window, SDL_Surface* const pImage)
{
	SDL_Rect r = { 0, 0, static_cast<Uint16>(window.getWidth()), static_cast<Uint16>(window.getHeight()) };

	assert(pImage);

	LDebug << "RSDL :: drawBackground";

	if ( SDL_BlitSurface(window.getWindowSurface(), NULL, pImage, &r) != 0 )
	{
		LWarning << "Fail to blit the surface";
		return false;
	}

	return true;
}
