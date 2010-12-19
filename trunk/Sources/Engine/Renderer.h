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

#include <cassert>

#include "Window.h"

#include "../Types/Vec2.h"

struct SDL_Surface;
struct SDL_Rect;
struct SDL_Colour;

class Window;
class Sprite;
class AnimatedSprite;

typedef enum RenderingAPI
{
	RAPI_SDL,
	RAPI_OpenGL
}RenderingAPI;

class Renderer
{
private:

protected:
	const Window* pWin;				/*!< Keep the window where to draw */
	RenderingAPI rAPI;			/*!< Remember which API is actually implemented */
	
public:
	Renderer(const Window* const pWin, const RenderingAPI rAPI):pWin(pWin),rAPI(rAPI) {}
	virtual ~Renderer(void) {};

	virtual bool clearScreen(void)const=0;

	virtual bool drawTile(SDL_Rect& tile, const SDL_Color& colour)const=0;
	virtual bool drawTile(const Sprite& sprite, const IVec2& pos)const=0;
	virtual bool drawTile(const Sprite& sprite, const IVec2& pos, const SDL_Colour& maskColour)const=0;
	virtual bool drawTile(const Sprite& sprite, SDL_Rect& srcRect, const IVec2& pos)const=0;
	virtual bool drawTile(AnimatedSprite& aSprite, const IVec2& pos, const unsigned int time)const=0;
	virtual bool drawBackground(SDL_Surface* const pImage)const=0;

	RenderingAPI getAPI(void)const { return rAPI; }
};

Renderer* RendererFactory(const Window* const pWin, const RenderingAPI renderingAPI);

/*! \class Renderer Renderer.h "Engine/Renderer.h"
 *  \brief Base for the API specific renderer.
 *
 * Give an unified interface usable by the application, to draw on the screen
 * This interface has to be inherited to implement a new API specific renderer (SDL / OpenGL / ...)
 * A Window instance is stored in this class to know on which window it has to draw
 * The following functionnalities needs to be implemented:
 *		- Clear the screen
 *		- Draw a rectangle with a unified colour
 *		- Draw a Sprite
 *		- Draw a part of a Sprite
 *		- Draw an AnimatedSprite
 *		- Draw an image in background
 */

/*! \fn Renderer::Renderer(const Window* const pWin, const RenderingAPI rAPI)
 * \brief Do nothing, just copying the enum of the API used
 * \param pWin the Window where the Renderer will draw
 * \param rAPI the API of the current instance of the Renderer
 */

/*! \fn virtual Renderer::~Renderer(void)
 */

/*! \fn virtual bool Renderer::clearScreen(void)const=0
 * \brief Clear the screen (black)
 * \return true if all goes right
 */

/*! \fn virtual bool Renderer::drawTile(SDL_Rect& tile, const SDL_Color& colour)const=0
 * \brief Draw a rectangle with a unified colour
 * \param tile the rectangle to fill
 * \param colour the colour to use to fill the rectangle
 * \return true if all goes right
 */

/*! \fn virtual bool Renderer::drawTile(const Sprite& sprite, const IVec2& pos)const=0
 * \brief Draw a complete Sprite
 * \param sprite the sprite to draw
 * \param pos where the sprite is drawn
 * \return true if all goes right
 */

/*! \fn virtual bool Renderer::drawTile(const Sprite& sprite, const IVec2& pos, const SDL_Colour& maskColour)const=0
 * \brief Draw a complete Sprite using a masling colour
 * \param sprite the sprite to draw
 * \param pos where the sprite is drawn
 * \param maskColour the colour to use for the mask on the sprite
 * \return true if all goes right
 */

/*! \fn virtual bool Renderer::drawTile(const Sprite& sprite, SDL_Rect& srcRect, const IVec2& pos)const=0
 * \brief Draw a part of a Sprite
 * \param sprite the sprite to draw
 * \param srcRect the rectangle on the source Sprite to draw
 * \param pos the position where to draw the part of the sprite
 * \return true if all goes right
 */

/*! \fn virtual bool Renderer::drawTile(AnimatedSprite& aSprite, const IVec2& pos, const unsigned int time)const=0
 * \brief Draw an AnimatedSprite
 * \param aSprite the animation to draw
 * \param pos where to draw the animation
 * \param time the actual time (to know which frame to draw)
 * \return true if all goes right
 */

/*! \fn virtual bool Renderer::drawBackground(SDL_Surface* const pImage)const=0
 * \brief Draw a background
 * \param pImage the imageto copy in background
 * \return true if all goes right
 */

/*! \fn RenderingAPI Renderer::getAPI(void)const
 * \brief Get the current API used
 * \return the API actually used
 */

/*! \enum RenderingAPI
 * Identifiers to know which API it is
 */

/*! \fn Renderer* RendererFactory(const Window* const pWin, const RenderingAPI renderingAPI)
 * \brief Return the renderer corresponding to the parameter
 * \param pWin the Window where the Renderer will draw
 * \param renderingAPI the specific API renderer to return
 * \return the wanted Renderer
*/

#endif
