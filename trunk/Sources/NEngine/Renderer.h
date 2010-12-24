#ifndef __RENDERER_H__
#define __RENDERER_H__

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

#include "../Types/Vec2.h"

struct Colour;
struct Rect;

class Sprite;
class Window;

class Renderer
{
protected:

	Window* pWin;

	void* getNativeWindow(void)const;
	void* getNativeSurface(const Sprite& sprite)const;

public:
	Renderer(Window* pWin):pWin(pWin) {}
	virtual ~Renderer(void) {}

	virtual bool clearScreen(const Colour& colour)=0;

	virtual bool drawRect(const Rect& tile, const Colour& colour)const=0;
	virtual bool drawSurface(const IVec2& position,const Sprite& pSurface)const=0;
	virtual bool drawSurface(const IVec2& position,const Sprite& pSurface, const Colour& mask)const=0;
	virtual bool drawSurface(const IVec2& position,const Sprite& pSurface, const Rect& srcRect)const=0;
	virtual bool drawSurface(const IVec2& position,const Sprite& pSurface, const Rect& srcRect, const Colour& mask)const=0;

	virtual bool updateWindow(void)=0;
};

#endif