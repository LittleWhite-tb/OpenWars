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

#include "../NEngine/Renderer.h"
#include "../NEngine/Native/SDL/SDL_Sprite.h"

#include "ResourcesManager/SpriteManager.h"

#include "../Types/Vec2.h"
#include "../Types/Colour.h"
#include "../Types/Rect.h"

#include "../Utils/Logger.h"
#include "../Utils/Exceptions/ConstructionFailedException.h"

Sprite :: Sprite(SpriteManager& sm, const std::string& fileName, const bool needScaling)
{
	pSurface = sm.getSurface(fileName,needScaling);
	if ( pSurface == NULL )
	{
		throw ConstructionFailedException("Sprite");
	}

	LDebug << "Sprite created from file (" << fileName.c_str() << ")";
}

Sprite :: Sprite(SDL_Surface* pSurface)
	:pSurface(pSurface)
{
	assert(pSurface);
	LDebug << "Sprite created from SDL_Surface*";
}

Sprite :: ~Sprite(void)
{
	LDebug << "Sprite deleted";
}

USize2 Sprite :: getSize(void)const
{
	return USize2(pSurface->w,pSurface->h);
}

int Sprite :: getWidth(void)const
{
	return pSurface->w;
}

int Sprite :: getHeight(void)const
{
	return pSurface->h;
}

bool Sprite :: draw(const NE::Renderer& r, const IVec2& position)
{
	return r.drawSurface(position, NE::SDL_Sprite(this->pSurface));
}

bool Sprite :: draw(const NE::Renderer& r, const IVec2& position, const Colour& mask)
{
	return r.drawSurface(position, NE::SDL_Sprite(this->pSurface), mask);
}
