#ifndef __RENDERER_SDL_H__
#define __RENDERER_SDL_H__

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

#include "../Renderer.h"

struct SDL_Surface;
struct SDL_Colour;
struct SDL_Rect;

class Window;
class Sprite;
class AnimatedSprite;

class RSDL : public Renderer
{
private:

public:
	RSDL(const Window* const pWin);
	~RSDL(void);

	bool clearScreen(void)const;
	bool drawTile(SDL_Rect& tile, const SDL_Color& colour)const;
	bool drawTile(const Sprite& sprite, const IVec2& pos)const;
	bool drawTile(const Sprite& sprite, const IVec2& pos, const SDL_Colour& maskColour)const;
	bool drawTile(const Sprite& sprite, SDL_Rect& srcRect, const IVec2& pos)const;
	bool drawTile(AnimatedSprite& aSprite, const IVec2& pos, const unsigned int time)const;
	bool drawBackground(SDL_Surface* const pImage)const;
};

/*! \class RSDL Renderer_sdl.h "Engine/Renderers/Renderer_sdl.h"
 *  \brief SDL implementation for the Renderer
 *
 * Inherits the Renderer interface
 */

/*! \fn RSDL::RSDL(const Window* const pWin)
 * \param pWin the Window where the Renderer will draw
 */

#endif