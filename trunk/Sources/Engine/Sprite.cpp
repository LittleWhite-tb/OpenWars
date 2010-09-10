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

#include "Sprite.h"

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include <string>

#include <cassert>

#include "ResourcesManager/SpriteManager.h"

#include "../Utils/Logger.h"

#ifdef _DEBUG
	extern unsigned int nbSAllocation;
	extern unsigned int nbSDestruction;
#endif

Sprite :: Sprite(SpriteManager& sm, const std::string& fileName, const bool needScaling)
{
	surface = sm.getSurface(fileName,needScaling);

	LDebug << "Sprite created from file (" << fileName.c_str() << ")";

#ifdef _DEBUG
	nbSAllocation++;
#endif
}

Sprite :: ~Sprite(void)
{
	LDebug << "Sprite deleted";
#ifdef _DEBUG
	nbSDestruction++;
#endif
}

const int Sprite :: getWidth(void)const
{
	assert(surface);

	LDebug << "Sprite :: getWidth (" << this->surface->w << ")";

	return this->surface->w;
}

const int Sprite :: getHeight(void)const
{
	assert(surface);

	LDebug << "Sprite :: getHeight (" << this->surface->h << ")";

	return this->surface->h;
}