#ifndef __WINDOW_H__
#define __WINDOW_H__

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

#include <SDL/SDL.h>

#include <vector>

typedef struct ResolutionInfo
{
	int w;			/*!< Width of the resolution */
	int h;			/*!< Height of the resolution */
	int bpp;		/*!< Bits per pixel of the resolution */

	ResolutionInfo():w(0),h(0),bpp(0) {}

	//! Basic constructor
	/*!
		\param w the width of the resolution
		\param h the height of the resolution
		\param bpp the bits per pixel of the resolution
	*/
	ResolutionInfo(const int w, const int h, const int bpp):w(w),h(h),bpp(bpp) {}
}ResolutionInfo;

class Window
{
private:
	const SDL_VideoInfo* pVideoInfo;	/*!< Info from SDL on the machine's abilities */
	SDL_Surface* pWindowSurface;		/*!< Surface of the window */

	bool isFullscreen;					/*!< Remember if the window is in fullscreen mode */
	bool isOpenGL;						/*!< Remember if the window is built for OpenGL */

	// Disallow the copy
	Window(const Window& w);
	void operator= (const Window& w);

	/** Gets the flags needed to build a window (or other SDL functions), following the parameters and the SDL_VideoInfo
     *  \param isFillscreen Says if we wants flags for fullscreen mode 
	 *  \param isOpenGL Says if we wants flags for OpenGL compatibilities
     */
	Uint32 getFlags(const bool isFullscreen, const bool isOpenGL)const;

public:
	
	//! Basic constructor
	/*!
      Do nothing by itself, will just initialised the fields with defaults value (0) and get the SDL_VideoInfo
	  \warning don't open a window itself, to do this, you need to call openWindow()
    */
	Window();	

	//! Basic destructor
	/*!
		Do nothing because SDL will clear the window surface in SDL_Quit()
	*/
	~Window();

	//! Open a window following the parameters passed
    /*!
      \param width The width of the window to open
      \param height The height of the window to open
	  \param bpp The bit per pixel of the window to open
	  \param isFullscreen asks for a fullscreen window or not
	  \param isOpenGL asks for a OpenGL compatible window or not
	  \return true if all goes correctly (window is open)
    */
	bool openWindow(const unsigned int width, const unsigned int height, const unsigned short int bpp, const bool isFullscreen, const bool isOpenGL);

	//! Reopen a window with a different resolution. If a window is not open yet, it doesn't matter, it will open a window if possible.
    /*!
      \param width The width of the window to open
      \param height The height of the window to open
	  \param bpp The bit per pixel of the window to open
	  \param isFullscreen asks for a fullscreen window or not
	  \param isOpenGL asks for a OpenGL compatible window or not
	  \return true if all goes correctly (window is open)
    */
	bool changeResolution(const unsigned int width, const unsigned int height, const unsigned short int bpp, const bool isFullscreen, const bool isOpenGL);

	//! get a list of resolution available on the current machine. To do this, the function will check the resolution with SDL_VideoModeOK(). The test is always done in fullscreen mode to have the best results.
    /*!
	  \param isOpenGL asks for a OpenGL compatible window during the test
      \param riList is a list of the resolution available
	*/
	void getResolutionsAvailable(const bool isOpenGL, std::vector<ResolutionInfo>& riList)const;

	//! get the window surface
    /*!
	  \return the window surface, where to draw final image
	*/
	SDL_Surface* const getWindowSurface(void)const { return pWindowSurface; }

	//! get the height of the window surface
    /*!
	  \return the height
	*/
	int getHeight(void)const;

	//! get the width of the window surface
    /*!
	  \return the width
	*/
	int getWidth(void)const;

	//! get the bits per pixel of the window surface
    /*!
	  \return the bits per pixel
	*/
	int getBitsPerPixel(void)const;

	//! get if the window is OpenGL compatible
    /*!
	  \return true if the window is OpenGL compatible
	*/
	bool isOpenGLWindow(void)const { return isOpenGL; }

	//! get if the window is in fullscreen mode
    /*!
	  \return true if the window is in fullscreen mode
	*/
	bool isFullscreenWindow(void)const { return isFullscreen; }

	//! get if the cursor is actually visible
    /*!
	  \return true if the cursor is visible
	*/
	bool isCursorVisible(void)const;

	//! Set the visibility of the cursor
    /*!
	  \param isShowed true if the cursor needs to be visible (default).
	*/
	void showCursor(const bool isShowed)const;

	//! Set the window name and the icon assigned to it
    /*!
	  \param windowName the name of the window
	  \param iconName the name of the file to load for the window (should be .ico file)
	*/
	void setCaption(const std::string& windowName, const std::string& iconName)const;
};

/*! \struct ResolutionInfo Window.h "Engine/Window.h"
 *  \brief Keep some information on resolutions
 */

/*! \class Window Window.h "Engine/Window.h"
 *  \brief Window management class
 *
 * Give an easy interface to manage a window with the following features:
 *		- Open a window
 *		- Reopen a window with different settings
 *		- Set a name and an icon
 *		- Display / hide the cursor
 *		- Get some information about the resolutions available
 */

#endif