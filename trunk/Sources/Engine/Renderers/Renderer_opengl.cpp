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

#include "Renderer_opengl.h"

//#include <GL/gl.h>
#include <SDL/SDL.h>

#include <cassert>

#include "../Sprite.h"
#include "../AnimatedSprite.h"

#include "../../NEngine/NETypes.h"

#include "../../Utils/Logger.h"

ROpenGL :: ROpenGL(Window* const pWin)
	:Renderer(pWin,RAPI_OpenGL)
{
	/*
	if ( !pWin->isOpenGLWindow() )
	{
		LWarning << "The window passed to the OpenGL renderer is not compatible with OpenGL";
	}
	*/

	LDebug << "ROpenGL created";

	// Need some init
}

ROpenGL :: ~ROpenGL(void)
{
	LDebug << "ROpenGL deleted";
}

bool ROpenGL :: clearScreen(void)const
{
	LDebug << "ROpenGL :: clearScreen";

	return true;
}

bool ROpenGL :: drawTile(SDL_Rect& tile, const SDL_Color& colour)const
{
	LDebug << "RSDL :: drawTile from colour (pos: " << tile.x << "x" << tile.y << " size: " << tile.w << "x" << tile.h << " colour: " << static_cast<int>(colour.r) << "," <<  static_cast<int>(colour.g) << "," << static_cast<int>(colour.b) << "," << static_cast<int>(colour.unused);

	return true;
}

bool ROpenGL :: drawTile(const Sprite& sprite, const IVec2& pos)const
{
	LDebug << "ROpenGL :: drawTile from Sprite @ " << pos;

	(void)sprite;

	return true;
}

bool ROpenGL :: drawTile(const Sprite& sprite, const IVec2& pos, const SDL_Colour& maskColour)const
{
	LDebug << "ROpenGL :: drawTile from Sprite @ " << pos << " maskColour: " << static_cast<int>(maskColour.r) << "," <<  static_cast<int>(maskColour.g) << "," << static_cast<int>(maskColour.b) << "," << static_cast<int>(maskColour.unused);

	(void)sprite;

	return true;
}

bool ROpenGL :: drawTile(const Sprite& sprite, SDL_Rect& srcRect, const IVec2& pos)const
{
	LDebug << "ROpenGL :: drawTile from Sprite (" << srcRect.x << ";" << srcRect.y << ";" << srcRect.w << ";" << srcRect.h << ") @ " << pos;

	(void)sprite;

	return true;
}

bool ROpenGL :: drawTile(AnimatedSprite& aSprite, const IVec2& pos, const unsigned int time)const
{
	LDebug << "ROpenGL :: drawTile from AnimatedSprite @ " << pos.x << ";" << pos.y;

	(void)aSprite;
	(void)time;

	return true;
}

bool ROpenGL :: drawBackground(SDL_Surface* const pImage)const
{
	assert(pImage);

	LDebug << "ROpenGL :: drawBackground";

	return true;
}
