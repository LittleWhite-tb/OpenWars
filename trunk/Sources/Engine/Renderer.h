#ifndef __RENDERER_H__
#define __RENDERER_H__

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

#include "Window.h"

struct SDL_Surface;
struct SDL_Rect;
struct SDL_Colour;

class Window;
class Sprite;
class AnimatedSprite;

#include "../Types/Vec2.h"

typedef enum RenderingAPI
{
	RAPI_SDL,
	RAPI_OpenGL
}RenderingAPI;

class Renderer
{
private:

protected:
	RenderingAPI rAPI;
	
public:
	Renderer(const RenderingAPI rAPI):rAPI(rAPI) {};
	virtual ~Renderer(void) {};

	virtual bool clearScreen(Window& window)=0;
	virtual bool drawTile(Window& window, SDL_Rect& tile, const SDL_Color& colour)=0;
	virtual bool drawTile(Window& window, Sprite& sprite, const IVec2& pos)=0;
	virtual bool drawTile(Window& window, Sprite& sprite, SDL_Rect& srcRect, const IVec2& pos)=0;
	virtual bool drawTile(Window& window, AnimatedSprite& aSprite, const IVec2& pos, const unsigned int time)=0;
	virtual bool drawBackground(Window& window, SDL_Surface* const pImage)=0;
	
	const RenderingAPI getAPI(void)const { return rAPI; }
};

// The creator of the renderer
Renderer* RendererFactory(const RenderingAPI renderingAPI);

#endif