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

#include "Font.h"

#include <SDL/SDL_ttf.h>

#include <string>

#include "../NEngine/Native/SDL/SDL_Sprite.h"
#include "../NEngine/Renderer.h"

#include "ResourcesManager/FontManager.h"

#include "../Utils/Logger.h"
#include "../Utils/Exceptions/ConstructionFailedException.h"

Font :: Font(FontManager& fm, const std::string& fileName, const int size, const Colour& colour)
	:colour(colour)
{
	pFont = fm.getFont(fileName,size);
	if ( pFont == NULL )
	{
		throw ConstructionFailedException("Font");
	}

	LDebug << "Font created from file (" << fileName.c_str() << ")";
}

Font :: ~Font(void)
{
	LDebug << "Font deleted";
}

IVec2 Font :: getSize(const std::string& text)
{
	IVec2 size;

	LDebug << "Font :: getSize( " << text.c_str() << ")";

	if ( TTF_SizeText(pFont,text.c_str(),&size.x,&size.y) != 0 )
	{
		LWarning << "getSize failed -> " << TTF_GetError();
	}

	return size;
}

bool Font :: draw(const NE::Renderer& r, const std::string& text, const IVec2& position)
{
	bool error = false;

	LDebug << "Font :: draw @" << position;

    SDL_Colour c = { colour.r, colour.g, colour.b };

	SDL_Surface* pTmpSurface = TTF_RenderText_Solid(pFont, text.c_str(), c); 

	if ( pTmpSurface == NULL )
	{
		LWarning << "Fail to generate texture for the font -> " << TTF_GetError();
		return false;
	}

    error = r.drawSurface(position,*(new NE::SDL_Sprite(pTmpSurface)));

	SDL_FreeSurface(pTmpSurface);

	return error;
}
