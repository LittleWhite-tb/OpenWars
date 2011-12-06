#ifndef __NE_SDL_RENDERER_H__
#define __NE_SDL_RENDERER_H__

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

#include <NEngine/Renderer.h>
#include <NEngine/Types/Vec2.h>

struct Colour;
struct Rect;

class Window;
class Sprite;

namespace NE
{
	class SDL_Renderer : public Renderer
	{
	private:

	public:
		SDL_Renderer(Window* pWin):Renderer(pWin) {}
		~SDL_Renderer(void) {}

		bool clearScreen(const Colour& colour);

		bool drawRect(const Rect& tile, const Colour& colour)const;
		bool drawSurface(const IVec2& position,const Sprite& pSprite)const;
		bool drawSurface(const IVec2& position, const Sprite& pSprite, const Colour& mask)const;
		bool drawSurface(const IVec2& position, const Sprite& pSprite, const Rect& srcRect)const;
		bool drawSurface(const IVec2& position, const Sprite& pSprite, const Rect& srcRect, const Colour& mask)const;

		bool updateWindow(void);
	};
}

/*! \class NE::SDL_Renderer SDL_Renderer.h "NEngine/Native/SDL/SDL_Renderer.h"
 *  \brief SDL implementation for Renderer
 */

/*! \fn NE::SDL_Renderer::SDL_Renderer(Window* pWin)
 * \param pWin Window to use by the Renderer
 */

#endif
