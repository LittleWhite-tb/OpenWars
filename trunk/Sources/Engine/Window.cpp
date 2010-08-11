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

website: 
e-mail: lw.demoscene@gmail.com
**/

#include "Window.h"

#include <SDL/SDL.h>

#include <iostream>
#include <cassert>

Window :: Window()
	:pWindowSurface(NULL),isFullscreen(false),isOpenGL(false)
{
	pVideoInfo = SDL_GetVideoInfo();
	// The documentation does not descrive a case of this function returning NULL pointer

	std::cout << "Hardware surface: " << pVideoInfo->hw_available << std::endl;
	std::cout << "Window manager: " << pVideoInfo->wm_available << std::endl;
	std::cout << "Window created" << std::endl;
}

Window :: ~Window()
{
	// We don't need to close anything

	// pVideoInfo doesn't have to be deleted because it's a read only pointer.

	std::cout << "Window deleted";
}

Uint32 Window :: getFlags(const bool isFullscreen, const bool isOpenGL)const
{
	Uint32 sdlVideoFlags = SDL_DOUBLEBUF | SDL_ANYFORMAT;

	std::cout << "Window :: getFlags (" << isFullscreen << ";" << isOpenGL << ")" << std::endl;

	if ( pVideoInfo->hw_available ) // is Hardware surface possible?
	{
		sdlVideoFlags = sdlVideoFlags | SDL_HWSURFACE;
	}
	else
	{
		sdlVideoFlags = sdlVideoFlags | SDL_SWSURFACE;
	}

	if ( isFullscreen )
	{
		// We add the flag for fullscreen
		sdlVideoFlags = sdlVideoFlags | SDL_FULLSCREEN;
	}

	if ( !pVideoInfo->wm_available ) // In case of the platform doesn't have a Window Manager, we go in fullscreen
	{
		sdlVideoFlags = sdlVideoFlags | SDL_FULLSCREEN;
	}

	if ( isOpenGL )
	{
		// We just want to force double buffering when OpenGL is
		SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

		sdlVideoFlags = sdlVideoFlags | SDL_OPENGL;
	}

	return sdlVideoFlags;
}

bool Window :: openWindow(const unsigned int width, const unsigned int height, const unsigned short int bpp, const bool isFullscreen, const bool isOpenGL)
{
	Uint32 sdlVideoFlags = this->getFlags(isFullscreen,isOpenGL);

	std::cout << "Window :: openWindow (" << width << ";" << height << "x" << bpp << "|" << isFullscreen << "|" << isOpenGL << ")" << std::endl;

	pWindowSurface = SDL_SetVideoMode(width,height,bpp,sdlVideoFlags);

	if ( pWindowSurface != NULL )
	{
		if ( (sdlVideoFlags & SDL_FULLSCREEN) == SDL_FULLSCREEN )
		{
			this->isFullscreen = true;
		}
		else
		{
			this->isFullscreen = false;
		}
		this->isOpenGL = isOpenGL;

		std::cout << "Obtained: " << this->getWidth() << "x" << this->getHeight() << "x" << this->getBitsPerPixel() << " (Fullscreen: " << this->isFullscreen << ")" << std::endl;

		return true;
	}
	else
	{
		std::cerr << "Error while opening the window" << std::endl;
		return false;
	}
}

bool Window :: changeResolution(const unsigned int width, const unsigned int height, const unsigned short int bpp, const bool isFullscreen, const bool isOpenGL)
{
	bool error = true;

	std::cout << "Window :: changeResolution (" << width << ";" << height << "x" << bpp << "|" << isFullscreen << "|" << isOpenGL << ")" << std::endl;

	// From the SDL documentation for the SDL_SetVideoMode():
	/*
		The surface returned is freed by SDL_Quit() and should nt be freed by the caller.
	*/
	// So we close the surface, we restart SDL and reopen the window
	SDL_Quit();
	if ( SDL_Init(SDL_INIT_VIDEO) == -1 )
	{
		std::cerr << "Error while reopening SDL" << std::endl;
		return false;
	}

	error = this->openWindow(width,height,bpp,isFullscreen,isOpenGL);
	
	return error;
}

void Window :: getResolutionsAvailable(const bool isOpenGL, std::vector<ResolutionInfo>& riList)const
{
	Uint32 flags = this->getFlags(true,isOpenGL);
	int bpp = 0;

	std::cout << "Window :: getResolutionsAvailable (" << isOpenGL << ")" << std::endl;

	for ( unsigned int w = 2 ; w <= 1280 ; w+=2 )
		for ( unsigned int h = 2 ; h <= 768 ; h+=2 )
		{
			if ( (bpp = SDL_VideoModeOK(w, h, 32, flags)) != 0 )
			{
				ResolutionInfo ri(w,h,bpp);

				std::cout << "Test (" << w << "x" << h << "x" << bpp << ") Passed" << std::endl;

				riList.push_back(ri);
			}
		}
}

int Window :: getHeight(void)const
{
	assert(pWindowSurface);

	int height = pWindowSurface->h;

	std::cout << "Window :: getHeight (" << height << ")" << std::endl;

	return height;
}

int Window :: getWidth(void)const
{
	assert(pWindowSurface);

	int width = pWindowSurface->w;

	std::cout << "Window :: getWidth (" << width << ")" << std::endl;

	return width;
}

int Window :: getBitsPerPixel(void)const
{
	assert(pWindowSurface);

	int bpp = pWindowSurface->format->BitsPerPixel;

	std::cout << "Window :: getBitsPerPixel (" << bpp << ")" << std::endl;

	return bpp;
}