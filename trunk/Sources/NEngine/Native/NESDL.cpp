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
#include <cassert>

#include "../NETypes.h"
#include "../../Types/Vec2.h"
#include "../../Types/Colour.h"
#include "../../Types/Rect.h"

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

Window* NESDL :: createWindow(const USize2& winSize, const unsigned short bpp, const bool isFullscreen, const bool isOpenGL)
{
	Uint32 sdlVideoFlags = this->getFlags(isFullscreen,isOpenGL);

	LDebug << "NESDL :: createWindow (" << winSize << " ; " << bpp << "|" << isFullscreen << "|" << isOpenGL << ")";

	Window* pWindowSurface = SDL_SetVideoMode(winSize.width,winSize.height,bpp,sdlVideoFlags);

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

void NESDL :: destroyWindow(Window* const pWin)
{
	assert(pWin);
	// Nothing to do for SDL ... SDL_Quit() does the job
	(void)pWin;
}

USize2 NESDL :: getWindowSize(const Window* const pWin)
{
	assert(pWin);

	return USize2(pWin->w,pWin->h);
}

int NESDL :: getBitsPerPixel(const Window* const pWin)
{
	assert(pWin);

	return pWin->format->BitsPerPixel;
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

//Drawing

USize2 NESDL :: getSurfaceSize(const Surface* const pSurface)
{
	assert(pSurface);
	return USize2(pSurface->w,pSurface->h);
}

bool NESDL :: clearScreen(Window* const pWin, const Colour& colour)
{
	assert(pWin);

	if ( SDL_FillRect(pWin,NULL,SDL_MapRGB(pWin->format,colour.r,colour.g,colour.b)) != 0 )
	{
		LWarning << "Fail to clear the screen";
		return false;
	}

	return true;
}

bool NESDL :: drawTile(Window* const pWin, const Rect& tile, const Colour& colour)const
{
	SDL_Rect sdlTile = { static_cast<short int>(tile.position.x),
						static_cast<short int>(tile.position.y),
						static_cast<unsigned short int>(tile.position.width),
						static_cast<unsigned short int>(tile.position.height) };

	if ( SDL_FillRect(pWin, &sdlTile, SDL_MapRGBA(pWin->format, colour.r, colour.g, colour.b, colour.a)) == -1 )
	{
		LWarning << "Failed to draw";
		return false;
	}

	return true;
}

bool NESDL :: drawSurface(Window* const pWin, const IVec2& position, Surface* const pSurface)
{
	assert(pWin);
	assert(pSurface);

	SDL_Rect sdlDestRect = { static_cast<short int>(position.x),
						static_cast<short int>(position.y),
						static_cast<unsigned short int>(pSurface->w),
						static_cast<unsigned short int>(pSurface->h) };

	if ( SDL_BlitSurface(pSurface, NULL, pWin, &sdlDestRect) != 0 )
	{
		LWarning << "Fail to blit the surface";
		return false;
	}

	return true;
}

bool NESDL :: drawSurface(Window* const pWin, const IVec2& position, Surface* const pSurface, const Colour& mask)
{
	assert(pWin);
	assert(pSurface);

	SDL_Rect sdlDestRect = { static_cast<short int>(position.x),
						static_cast<short int>(position.y),
						static_cast<unsigned short int>(pSurface->w),
						static_cast<unsigned short int>(pSurface->h) };

	SDL_Surface* pSrc = SDL_CreateRGBSurface(SDL_SWSURFACE | SDL_SRCALPHA, pSurface->w, pSurface->h, pSurface->format->BitsPerPixel, mask.r,mask.g,mask.b, mask.a);
	if ( pSrc == NULL )
    {
		LWarning << "Fail to produce the copy of the sprite for RSDL :: drawTile";
        return false;

    }

	// The masking is done in CreateRGBSurface
	if ( SDL_BlitSurface(pSurface, NULL, pSrc, NULL)  != 0 )
	{
		LWarning << "Fail to copy the sprite in a temporary surface";
		SDL_FreeSurface(pSrc);
		return false;
	}

	// Making a pre blit with the original image
	if ( SDL_BlitSurface(pSurface, NULL, pWin, &sdlDestRect)  != 0 )
	{
		LWarning << "Fail to copy the sprite in a temporary surface";
		SDL_FreeSurface(pSrc);
		return false;
	}

	// Apply the filter
	if ( SDL_BlitSurface(pSrc, NULL, pWin, &sdlDestRect) != 0 )
	{
		LWarning << "Fail to blit the surface";
		SDL_FreeSurface(pSrc);
		return false;
	}

	SDL_FreeSurface(pSrc);

	return true;
}

/*
bool drawSurface(Window* const pWin, const Rect& destRect, Surface* const pSurface)
{
	assert(pWin);
	assert(pSurface);

	SDL_Rect sdlDestRect = { static_cast<short int>(destRect.position.x),
						static_cast<short int>(destRect.position.y),
						static_cast<unsigned short int>(destRect.position.width),
						static_cast<unsigned short int>(destRect.position.height) };

	if ( SDL_BlitSurface(pSurface, NULL, pWin, &sdlDestRect) != 0 )
	{
		LWarning << "Fail to blit the surface";
		return false;
	}

	return true;
}
*/

bool NESDL :: drawSurface(Window* const pWin, const IVec2& position, Surface* const pSurface, const Rect& srcRect)
{
	assert(pWin);
	assert(pSurface);

	SDL_Rect sdlDestRect = { static_cast<short int>(position.x),
						static_cast<short int>(position.y),
						static_cast<unsigned short int>(srcRect.size.width),
						static_cast<unsigned short int>(srcRect.size.height) };

	SDL_Rect sdlSrcRect = { static_cast<short int>(srcRect.position.x),
						static_cast<short int>(srcRect.position.y),
						static_cast<unsigned short int>(srcRect.size.width),
						static_cast<unsigned short int>(srcRect.size.height) };

	if ( SDL_BlitSurface(pSurface, &sdlSrcRect, pWin, &sdlDestRect) != 0 )
	{
		LWarning << "Fail to blit the surface";
		return false;
	}

	return true;
}

bool NESDL :: drawSurface(Window* const pWin, const IVec2& position, Surface* const pSurface, const Rect& srcRect, const Colour& mask)
{
	assert(pWin);
	assert(pSurface);

	SDL_Rect sdlDestRect = { static_cast<short int>(position.x),
						static_cast<short int>(position.y),
						static_cast<unsigned short int>(srcRect.size.width),
						static_cast<unsigned short int>(srcRect.size.height) };

	SDL_Rect sdlSrcRect = { static_cast<short int>(srcRect.position.x),
						static_cast<short int>(srcRect.position.y),
						static_cast<unsigned short int>(srcRect.size.width),
						static_cast<unsigned short int>(srcRect.size.height) };

	SDL_Surface* pSrc = SDL_CreateRGBSurface(SDL_SWSURFACE | SDL_SRCALPHA, srcRect.size.width, srcRect.size.height, pSurface->format->BitsPerPixel, mask.r,mask.g,mask.b, mask.a);
	if ( pSrc == NULL )
    {
		LWarning << "Fail to produce the copy of the sprite for RSDL :: drawTile";
        return false;

    }

	// The masking is done in CreateRGBSurface
	if ( SDL_BlitSurface(pSurface, &sdlSrcRect, pSrc, NULL)  != 0 )
	{
		LWarning << "Fail to copy the sprite in a temporary surface";
		SDL_FreeSurface(pSrc);
		return false;
	}

	// Making a pre blit with the original image
	if ( SDL_BlitSurface(pSurface, &sdlSrcRect, pWin, &sdlDestRect)  != 0 )
	{
		LWarning << "Fail to copy the sprite in a temporary surface";
		SDL_FreeSurface(pSrc);
		return false;
	}

	// Apply the filter
	if ( SDL_BlitSurface(pSrc, NULL, pWin, &sdlDestRect) != 0 )
	{
		LWarning << "Fail to blit the surface";
		SDL_FreeSurface(pSrc);
		return false;
	}

	SDL_FreeSurface(pSrc);

	return true;
}