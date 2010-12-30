#ifdef EDITOR
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

#include "TileViewer.h"

#include "../Engine/ResourcesManager/SpriteManager.h"
#include "../Engine/ResourcesManager/FontManager.h"
#include "../Engine/Sprite.h"
#include "../Engine/AnimatedSprite.h"
#include "../Engine/Font.h"

#include "../Utils/Logger.h"
#include "../Types/Vec2.h"

TileViewer :: TileViewer(SpriteManager& sm, FontManager& fm, const std::string& fileNameBackground, const std::string& fileNameFont, const USize2& windowSize)
:windowSize(windowSize)
{
	SDL_Color white = {255,255,255,255};

	pBackground = new Sprite(sm,fileNameBackground,true);
	pFont = new Font(fm,fileNameFont,16,white);

	position = IVec2(windowSize.width - pBackground->getWidth() - 10, windowSize.height - pBackground->getHeight() - 10);
	
	title = "Element";

	LDebug << "TileViewer created";
}

TileViewer :: ~TileViewer(void)
{
	LDebug << "TileViewer deleted";

	delete pFont;
	delete pBackground;
}

void TileViewer :: putOnLeft(void)
{
		position.x = 10;	
}

void TileViewer :: putOnRight(void)
{
	position.x = windowSize.x - pBackground->getWidth() - 10;
}

bool TileViewer :: draw(const NE::Renderer& r)
{
	bool error = true;

	IVec2 titleSize = pFont->getSize(title);
	IVec2 nameSize = pFont->getSize(tileName);
	IVec2 titlePosition((position.x + (pBackground->getWidth() - titleSize.x)/2) , position.y - titleSize.y/2);
	IVec2 tilePosition(position.x + (pBackground->getWidth() - pTileSprite->getWidth())/2 , position.y + (pBackground->getHeight() - pTileSprite->getHeight())/2);
	IVec2 namePosition(position.x + (pBackground->getWidth() - nameSize.x)/2 , tilePosition.y + pTileSprite->getHeight() + 2);

	LDebug << "TileViewer draw";

	error &= pBackground->draw(r,position);
	error &= pFont->draw(r,title,titlePosition);
	error &= pTileSprite->draw(r,tilePosition,0);
	error &= pFont->draw(r,tileName,namePosition);

	return error;
}

#endif