#ifndef __NE_H__
#define __NE_H__

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

#include <string>

#include "NETypes.h"

#include "../Types/Vec2.h"
#include "../Types/Colour.h"
#include "../Types/Rect.h"

class NEngine;

class NE
{
private:
	static NEngine* pEngine;		/*!< Engine to use by the program */
	static Window* pWin;			/*!< Window for the application */

public:
	static bool init(const USize2& winSize, const unsigned short bpp, const bool isFullscreen, const std::string& windowName, const std::string& windowIcon="");
	static void stop(void);

	static USize2 getWindowSize(void);
	static int getWindowBPP(void);

	static bool needWindowClosure(void);

	static USize2 getSurfaceSize(const Surface* const pSurface);

	static bool clearScreen(const Colour& colour);

	static bool drawRect(const Rect& tile, const Colour& colour);
	static bool drawSurface(const IVec2& position, Surface* const pSurface);
	static bool drawSurface(const IVec2& position, Surface* const pSurface, const Colour& mask);
	static bool drawSurface(const IVec2& position, Surface* const pSurface, const Rect& srcRect);
	static bool drawSurface(const IVec2& position, Surface* const pSurface, const Rect& srcRect, const Colour& mask);

	static bool updateScreen(void);
};

/*! \class NE NE.h "NEngine/NE.h"
 *  \brief Layer giving the visibility of the NEngine to the application
 *
 * This class is a static class giving a global visibility of the NEngine to the application.
 * The function init() has to be called at the beginning of the application, and stop() at the end of the program.
 * NE could be implemented using a Singleton.
 */

/*! \fn static bool NE::init(const USize2& winSize, const unsigned short bpp, const bool isFullscreen, const std::string& windowName, const std::string& windowIcon="")
 * \brief Create a window where to render
 * \param winSize the size of the window
 * \param bpp the Bits per pixel wanted
 * \param isFullscreen true if the window should be fullscreen
 * \param windowName the name of the window
 * \param windowIcon the icon path for the window
 * \return true if all goes right
 */

/*! \fn static void NE::stop(void)
 * \brief clear the NEngine
 */

/*! \fn static USize2 NE::getWindowSize(void)
 * \brief Get the size of the Window
 * \return the size of the window
 */

/*! \fn static int NE::getWindowBPP(void)
 * \brief Get the number of bits per pixel of the Window
 * \return the number of bpp
 */

/*! \fn static bool NE::needWindowClosure(void)
 * \brief Get if the window should be closed
 * \return true if the window must be closed
 */

/*! \fn static USize2 NE::getSurfaceSize(const Surface* const pSurface)
 * \brief Get the size of the Surface
 * \param pSurface the surface to know the size
 * \return the size of the surface
 */

/*! \fn static bool NE::clearScreen(const Colour& colour)
 * \brief Clear the screen with colour
 * \param colour the colour to use to clear the screen
 * \return true if all goes right
 */

/*! \fn static bool NE::drawRect(const Rect& tile, const Colour& colour)
 * \brief Draw a coloured rect
 * \param tile the rectangle to colour
 * \param colour the colour to use
 * \return true if all goes right
 */

/*! \fn static bool NE::drawSurface(const IVec2& position, Surface* const pSurface)
 * \brief Draw a surface
 * \param position the position where to draw on the Window
 * \param pSurface the surface to copy
 * \return true if all goes right
 */

/*! \fn static bool NE::drawSurface(const IVec2& position, Surface* const pSurface, const Colour& mask)
 * \brief Draw a surface with an additional mask
 * \param position the position where to draw on the Window
 * \param pSurface the surface to copy
 * \param mask the mask to apply to the surface
 * \return true if all goes right
 */

/*! \fn static bool NE::drawSurface(const IVec2& position, Surface* const pSurface, const Rect& srcRect)
 * \brief Draw a part of a surface
 * \param position the position where to draw on the Window
 * \param pSurface the surface to copy
 * \param srcRect the rectangle to copy from pSurface
 * \return true if all goes right
 */

/*! \fn static bool NE::drawSurface(const IVec2& position, Surface* const pSurface, const Rect& srcRect, const Colour& mask)
 * \brief Draw a part of a surface
 * \param position the position where to draw on the Window
 * \param pSurface the surface to copy
 * \param srcRect the rectangle to copy from pSurface
 * \param mask the mask to apply to the surface
 * \return true if all goes right
 */

/*! \fn static bool NE::updateScreen()
 * \brief Update the screen (swap buffers)
 * \return true if all goes right
 */

#endif