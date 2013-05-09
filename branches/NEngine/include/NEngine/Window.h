#ifndef __NE_WINDOW_H__
#define __NE_WINDOW_H__

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

#include <string>

#include "NEngine/Types/Size2.h"

namespace NE
{
    class Window
    {
    protected:

        // void* pWindow;   /*!< The pointer on the native window */

        virtual void* getNativeWindow(void)const = 0;

    public:
        Window(void) {};
        virtual ~Window(void) {}

        virtual bool createWindow(const USize2& winSize, const unsigned short bpp, const bool isFullscreen, const std::string& windowName, const std::string& windowIcon ="", const bool showCursor = false)=0;
        virtual USize2 getWindowSize(void)const=0;
        virtual int getBitsPerPixel(void)const=0;
        virtual void destroyWindow(void)=0;

        virtual bool needWindowClosure(void)const=0;

        friend class Renderer;
    };
}

/*! \class NE::Window Window.h "NEngine/Window.h"
 *  \brief Window interface
 *
 * The Window class gives an interface to implement new platform specific windows in the game.
 * Only basic features are implemented (e.g.: the strict minimum for games) such as opening the window, closing it, get the size.
 * An additional function 'needWindowClosure()' should report if the window need to be closed or not (e.g.: after an event on the red cross)
 */

/*! \fn NE::Window::Window(void)
 */

/*! \fn virtual NE::Window::~Window(void)
 */

/*! \fn virtual void* NE::Window::getNativeWindow(void)const = 0
 *  \brief return a pointer to the native window handle
 *  \return a pointer to the native window handler
 *  The use of a void* is done to avoid specific code
 */

/*! \fn virtual bool NE::Window::createWindow(const USize2& winSize, const unsigned short bpp, const bool isFullscreen, const std::string& windowName, const std::string& windowIcon ="", const bool showCursor = false)=0
 * \brief open the window
 * \param winSize the size of the window to open
 * \param bpp the bits per pixel needed by the window
 * \param isFullscreen true if the window must be fullscreen
 * \param windowName the name of the window to display
 * \param windowIcon the path to the icon to use
 * \param showCursor true if the cursor is visible when on the window
 * \return true if all goes right (window opened)
 */

/*! \fn virtual USize2 NE::Window::getWindowSize(void)const=0
 * \brief Get the size of the Window
 * \return the size of the Window
 */

/*! \fn virtual int NE::Window::getBitsPerPixel(void)const=0
 * \brief Get the number of bits per pixel
 * \return the number of bits per pixel for the window
 */

/*! \fn virtual void NE::Window::destroyWindow(void)=0
 * \brief Close the Window
 */

/*! \fn virtual bool NE::Window::needWindowClosure(void)const=0;
 * \brief Return if the window should be closed
 * \return true if the Window should be closed
 */

#endif
