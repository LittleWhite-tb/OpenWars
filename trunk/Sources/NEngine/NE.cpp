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

#include "NE.h"

#include <string>
#include <cassert>

#include "NETypes.h"
#include "Native/NESDL.h"

#include "../Types/Vec2.h"
#include "../Types/Colour.h"
#include "../Types/Rect.h"

#include "../Utils/Logger.h"
#include "../Utils/Exceptions/ConstructionFailedException.h"

NEngine* NE::pEngine = NULL;
Window* NE::pWin = NULL;

bool NE::init(const USize2& winSize, const unsigned short bpp, const bool isFullscreen, const std::string& windowName, const std::string& windowIcon)
{
	if ( NE::pEngine != NULL )
	{
		LError << "The native engine is already defined";
		return false;
	}

	try
	{
#ifdef SDL_ENGINE
		NE::pEngine = new NESDL();
#elif SFML_ENGINE
		NE::pEngine = new NESFML();
#elif GLUT_ENGINE
		NE::pEngine = new NEGLUT();
#endif
	}
	catch (ConstructionFailedException& cfe)
	{
		LError << cfe.what();
		return false;
	}

	NE::pWin = NE::pEngine->createWindow(winSize,bpp,isFullscreen,windowName,windowIcon);
	if ( NE::pWin == NULL )
	{
		return false;
	}

	return true;
}

void NE :: stop(void)
{
	assert(NE::pEngine);
	assert(NE::pWin);

	pEngine->destroyWindow(NE::pWin);

	delete NE::pEngine;
	NE::pEngine = NULL;
}

USize2 NE :: getWindowSize(void)
{
	return NE::pEngine->getWindowSize(pWin);
}

int NE :: getWindowBPP(void)
{
	return NE::pEngine->getBitsPerPixel(pWin);
}

bool NE :: needWindowClosure(void)
{
	assert(NE::pEngine);

	return NE::pEngine->needWindowClosure();
}

USize2 NE :: getSurfaceSize(const Surface* const pSurface)
{
	assert(NE::pEngine);

	return NE::pEngine->getSurfaceSize(pSurface);
}

bool NE :: clearScreen(const Colour& colour)
{
	assert(NE::pEngine);
	assert(NE::pWin);

	return pEngine->clearScreen(NE::pWin,colour);
}

bool NE :: drawRect(const Rect& tile, const Colour& colour)
{
	assert(NE::pEngine);
	assert(NE::pWin);

	return pEngine->drawRect(NE::pWin,tile,colour);
}

bool NE :: drawSurface(const IVec2& position, Surface* const pSurface)
{
	assert(NE::pEngine);
	assert(NE::pWin);

	return pEngine->drawSurface(NE::pWin,position,pSurface);
}

bool NE :: drawSurface(const IVec2& position, Surface* const pSurface, const Colour& mask)
{
	assert(NE::pEngine);
	assert(NE::pWin);

	return pEngine->drawSurface(NE::pWin,position,pSurface,mask);
}

bool NE :: drawSurface(const IVec2& position, Surface* const pSurface, const Rect& srcRect)
{
	assert(NE::pEngine);
	assert(NE::pWin);

	return pEngine->drawSurface(NE::pWin,position,pSurface,srcRect);
}

bool NE :: drawSurface(const IVec2& position, Surface* const pSurface, const Rect& srcRect, const Colour& mask)
{
	assert(NE::pEngine);
	assert(NE::pWin);

	return pEngine->drawSurface(NE::pWin,position,pSurface,srcRect,mask);
}

bool NE :: updateScreen(void)
{
	assert(NE::pEngine);
	assert(NE::pWin);

	return pEngine->updateScreen(NE::pWin);
}