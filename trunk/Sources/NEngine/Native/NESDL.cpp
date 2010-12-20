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

#include "NESDL.h"

#include <SDL/SDL.h>

#include <string>

#include "../NETypes.h"
#include "../../Types/Vec2.h"

#include "../../Utils/Logger.h"
#include "../../Utils/Exceptions/ConstructionFailedException.h"

bool NESDL::isRedCrossPressed = false;

// Callback called once SDL_Quit event appear
int sdlQuitEventFilter(const SDL_Event* pEvent)
{
	if ( pEvent->type == SDL_QUIT )
	{
		NESDL::isRedCrossPressed = true;
	}

	return 0;	
}

NESDL :: NESDL(void)
{
	if ( SDL_Init(SDL_INIT_VIDEO) != 0 )
	{
		LError << "Error while initializing SDL -> SDL_INIT_VIDEO";
		throw ConstructionFailedException("NESDL");
	}

	LDebug << "Native Engine SDL started";
}

NESDL :: ~NESDL(void)
{
	SDL_Quit();

	LDebug << "Native Engine SDL stopped";
}

Uint32 NESDL :: getFlags(const bool isFullscreen, const bool isOpenGL)const
{
	Uint32 sdlVideoFlags = SDL_DOUBLEBUF | SDL_ANYFORMAT;
	const SDL_VideoInfo* pVideoInfo = SDL_GetVideoInfo();	// The documentation does not descrive a case of this function returning NULL pointer

	LDebug << "Window :: getFlags (" << isFullscreen << ";" << isOpenGL << ")";

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

Window NESDL :: createWindow(const USize2& winSize, const unsigned short bpp, const bool isFullscreen, const bool isOpenGL)
{
	Uint32 sdlVideoFlags = this->getFlags(isFullscreen,isOpenGL);

	LDebug << "NESDL :: createWindow (" << winSize << " ; " << bpp << "|" << isFullscreen << "|" << isOpenGL << ")";

	Window pWindowSurface = SDL_SetVideoMode(winSize.width,winSize.height,bpp,sdlVideoFlags);

	if ( pWindowSurface != NULL )
	{
		LDebug << "Obtained: " << pWindowSurface->w << "x" << pWindowSurface->h << "x" << pWindowSurface->format->BitsPerPixel;

		// Installing the event 
		SDL_SetEventFilter(&sdlQuitEventFilter);

		return pWindowSurface;
	}
	
	LError << "Error while opening the window";
	return NULL;
}

void NESDL :: destroyWindow(Window win)
{
	// Nothing to do for SDL ... SDL_Quit() does the job
	(void)win;
}

USize2 NESDL :: getWindowSize(const Window win)
{
	return USize2(win->w,win->h);
}

int NESDL :: getBitsPerPixel(const Window win)
{
	return win->format->BitsPerPixel;
}

bool NESDL :: isCursorVisible(void)const
{
	bool cursorState = false;

	if ( SDL_ShowCursor(SDL_QUERY) == SDL_ENABLE )
	{
		cursorState = true;
	}
	else
	{
		cursorState = false;
	}

	return cursorState;
}

void NESDL :: setCursorVisible(const bool mustShowCursor)const
{
	LDebug << "NESDL :: showCursor (" << mustShowCursor << ")";

	if ( mustShowCursor )
	{
		SDL_ShowCursor(SDL_ENABLE);
	}
	else
	{
		SDL_ShowCursor(SDL_DISABLE);
	}
}

void NESDL :: setCaption(const std::string& windowName, const std::string& iconName)const
{
	const SDL_VideoInfo* pVideoInfo = SDL_GetVideoInfo();

	LDebug << "NESDL :: setName (" << windowName.c_str() << " ; " << iconName.c_str() << ")";

	if ( pVideoInfo->wm_available )
	{
		SDL_WM_SetCaption(windowName.c_str(), iconName.c_str());
	}
}