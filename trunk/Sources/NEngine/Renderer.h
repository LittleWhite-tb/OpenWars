#ifndef __NE_RENDERER_H__
#define __NE_RENDERER_H__

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

#include <NEngine/Types/Vec2.h>

struct Colour;
struct Rect;

namespace NE
{
	class Sprite;
	class Window;

	class Renderer
	{
	protected:

		Window* pWin;		/*!< Window where the Renderer will draw */

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
}

/*! \class NE::Renderer Renderer.h "NEngine/Renderer.h"
 *  \brief Renderer interface
 *
 * The Renderer class gives an interface to implement new platform specific drawing functions.
 */

/*! \fn void* NE::Renderer::getNativeWindow(void)const
 * \brief Give access to the native window to the childrens of the class
 * \return the pointer of the native window where to render
 */

/*! \fn void* NE::Renderer::getNativeSurface(const Sprite& sprite)const
 * \brief Give access to the native sprite to the childrens of the class
 * \param sprite the sprite to use
 * \return the pointer on the native sprite
 */

/*! \fn NE::Renderer::Renderer(Window* pWin)
 * \param pWin the Window where to render
 */

/*! \fn virtual NE::Renderer::~Renderer(void)
 */

/*! \fn virtual bool NE::Renderer::clearScreen(const Colour& colour)=0
 * \brief Clear the screen using a Colour
 * \param colour the Colour to use to clear the screen
 * \return true if all goes right
 */

/*! \fn virtual bool NE::Renderer::drawRect(const Rect& tile, const Colour& colour)const=0
 * \brief Draw a rectangle using a Colour
 * \param tile the Rect where to draw
 * \param colour the Colour of the rectangle
 * \return true if all goes right
 */

/*! \fn virtual bool NE::Renderer::drawSurface(const IVec2& position,const Sprite& pSurface)const=0
 * \brief Draw a Sprite
 * \param position the position where to draw
 * \param pSurface the sprite to draw
 * \return true if all goes right
 */

/*! \fn virtual bool NE::Renderer::drawSurface(const IVec2& position,const Sprite& pSurface, const Colour& mask)const=0
 * \brief Draw a Sprite using a mask
 * \param position the position where to draw
 * \param pSurface the sprite to draw
 * \param mask Colour of the mask to use
 * \return true if all goes right
 */

/*! \fn virtual bool NE::Renderer::drawSurface(const IVec2& position,const Sprite& pSurface, const Rect& srcRect)const=0
 * \brief Draw a part of a Sprite
 * \param position the position where to draw
 * \param pSurface the sprite to draw
 * \param srcRect the part of the Sprite to use
 * \return true if all goes right
 */

/*! \fn virtual bool NE::Renderer::drawSurface(const IVec2& position,const Sprite& pSurface, const Rect& srcRect, const Colour& mask)const=0
 * \brief Draw a part of a Sprite using a mask
 * \param position the position where to draw
 * \param pSurface the sprite to draw
 * \param srcRect the part of the Sprite to use
 * \param mask Colour of the mask to use
 * \return true if all goes right
 */

/*! \fn virtual bool NE::Renderer::updateWindow(void)=0
 * \brief Refresh the Window
 * \return true if all goes right
 */

#endif
