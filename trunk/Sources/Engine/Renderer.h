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
	RenderingAPI rAPI;			/*!< Remember which API is actually implemented */
	
public:
	//! Basic constructor
	/*!
      Do nothing, just copying the enum of the API used
    */
	Renderer(const RenderingAPI rAPI):rAPI(rAPI) {};

	//! Basic destructor
	/*!
      Do nothing
    */
	virtual ~Renderer(void) {};

	//! Clear the screen (black)
	/*!
      \param window the window to clear
	  \return true if all goes right
    */
	virtual bool clearScreen(Window& window)=0;

	//! Draw a rectangle with a unified colour
	/*!
      \param window the window where to draw
	  \param tile the rectangle to fill
	  \param colour the colour to use to fill the rectangle
	  \return true if all goes right
    */
	virtual bool drawTile(Window& window, SDL_Rect& tile, const SDL_Color& colour)=0;

	//! Draw a complete Sprite
	/*!
      \param window the window where to draw
	  \param sprite the sprite to draw
	  \param pos where the sprite is drawn
	  \return true if all goes right
    */
	virtual bool drawTile(Window& window, Sprite& sprite, const IVec2& pos)=0;

	//! Draw a part of a Sprite
	/*!
      \param window the window where to draw
	  \param sprite the sprite to draw
	  \param srcRect the rectangle on the source Sprite to draw
	  \param pos the position where to draw the part of the sprite
	  \return true if all goes right
    */
	virtual bool drawTile(Window& window, Sprite& sprite, SDL_Rect& srcRect, const IVec2& pos)=0;

	//! Draw an AnimatedSprite
	/*!
      \param window the window where to draw
	  \param aSprite the animation to draw
	  \param pos where to draw the animation
	  \param time the actual time (to know which frame to draw)
	  \return true if all goes right
    */
	virtual bool drawTile(Window& window, AnimatedSprite& aSprite, const IVec2& pos, const unsigned int time)=0;

	//! Draw a background
	/*!
      \param window the window where to draw
	  \param pImage the imageto copy in background
	  \return true if all goes right
    */
	virtual bool drawBackground(Window& window, SDL_Surface* const pImage)=0;
	
	//! Get the current API used
	/*!
      \return the API actually used
    */
	const RenderingAPI getAPI(void)const { return rAPI; }
};

//! Renderer factory
/*!
 * Return the renderer corresponding to the parameter
 * \param renderingAPI the specific API renderer to return
 * \return the wanted renderer
*/
Renderer* RendererFactory(const RenderingAPI renderingAPI);

/*! \class Renderer Renderer.h "Engine/Renderer.h"
 *  \brief Base for the API specific renderer.
 *
 * Give an unified interface usable by the application, to draw on the screen
 * This interface has to be inherited to implement a new API specific renderer (SDL / OpenGL / ...)
 * The following functionnalities needs to be implemented:
 *		- Clear the screen
 *		- Draw a rectangle with a unified colour
 *		- Draw a Sprite
 *		- Draw a part of a Sprite
 *		- Draw an AnimatedSprite
 *		- Draw an image in background
 */

/*! \enum RenderingAPI
 * Identifiers to know which API it is
 */

#endif