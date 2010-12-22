#ifndef __NESDL_H__
#define __NESDL_H__

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

#include "../NEngine.h"
#include "../NETypes.h"
#include "../../Types/Vec2.h"

#include <string>

struct Colour;
struct Rect;

class NESDL : public NEngine
{
private:

	Uint32 getFlags(const bool isFullscreen, const bool isOpenGL)const;

	bool isCursorVisible(void)const;
	void setCursorVisible(const bool mustShowCursor)const;
	void setCaption(const std::string& windowName, const std::string& iconName)const;

public:
	static bool isRedCrossPressed;				/*!< Tell if the red cross button has been pressed */


	NESDL(void);
	~NESDL(void);

	// Windowing
	Window* createWindow(const USize2& winSize, const unsigned short bpp, const bool isFullscreen, const std::string& windowName, const std::string& windowIcon ="", const bool showCursor = false);
	USize2 getWindowSize(const Window* const pWin);
	int getBitsPerPixel(const Window* const pWin);
	void destroyWindow(Window* const pWin);

	bool needWindowClosure(void)const { return isRedCrossPressed; }

	// Drawing
	USize2 getSurfaceSize(const Surface* const pSurface);

	bool clearScreen(Window* const pWin, const Colour& colour);

	bool drawRect(Window* const pWin, const Rect& tile, const Colour& colour)const;
	bool drawSurface(Window* const pWin, const IVec2& position, Surface* const pSurface);
	bool drawSurface(Window* const pWin, const IVec2& position, Surface* const pSurface, const Colour& mask);
	// bool drawSurface(Window* const pWin, const Rect& destRect, Surface* const pSurface);
	bool drawSurface(Window* const pWin, const IVec2& position, Surface* const pSurface, const Rect& srcRect);
	bool drawSurface(Window* const pWin, const IVec2& position, Surface* const pSurface, const Rect& srcRect, const Colour& mask);

	bool updateScreen(Window* const pWin);
};

/*! \class NESDL NESDL.h NEngine\Native\NESDL.h
 * \brief SDL implementation
 *
 * \warning the SDL implementation may have some differencies because of the capability of the SDL library. This one can only manage one window at the same time.
 */

/*! \fn virtual bool NESDL::isCursorVisible(void)const=0
 * \brief Get if the cursor is visible
 * \return true if the cursor is visible
 */

/*! \fn virtual void NESDL::setCursorVisible(const bool mustShowCursor)const=0
 * \brief Set the visibility of the cursor
 * \param mustShowCursor true if the cursor must be visible
 */

/*! \fn virtual void NESDL::setCaption(const std::string& windowName, const std::string& iconName)const=0
 * \brief Set the name and icon for the Window
 * \param windowName the new name of the window
 * \param iconName the path to the icon
 */

/*! \fn Uint32 NESDL::getFlags(const bool isFullscreen, const bool isOpenGL)const
 * \brief Give flags following the platform capabilities and the flags passed
 * \param isFullscreen true if fullscreen is wanted
 * \param isOpenGL true if OpenGL is wanted
 * \return flags on 32bits for SDL API
 */

/*! \fn NESDL::NESDL(void)
 */

/*! \fn NESDL::~NESDL(void)
 */

#endif