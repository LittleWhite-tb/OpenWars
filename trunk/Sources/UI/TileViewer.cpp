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

#include "../NEngine/SpriteLoader.h"
#include "../NEngine/Renderer.h"

#include "../Engine/ResourcesManager/FontManager.h"
#include "../NEngine/Sprite.h"
#include "../Engine/AnimatedSprite.h"
#include "../Engine/Font.h"

#include "../Utils/Logger.h"
#include "../Types/Vec2.h"
#include "../Types/Colour.h"

TileViewer :: TileViewer(NE::SpriteLoader* const pSL, FontManager& fm, const std::string& fileNameBackground, const std::string& fileNameFont, const USize2& windowSize)
:windowSize(windowSize)
{
	Colour white(255,255,255,255);

	pBackground = pSL->loadSpriteFromFile(fileNameBackground);
	pFont = new Font(fm,fileNameFont,16,white);
    
    USize2 backgroundSize = pBackground->getSize();
	position = IVec2(windowSize.width - backgroundSize.width - 10, windowSize.height - backgroundSize.height - 10);
	
	title = "Element";

	LDebug << "TileViewer created";
}

TileViewer :: ~TileViewer(void)
{
	LDebug << "TileViewer deleted";

	delete pFont;
}

void TileViewer :: putOnLeft(void)
{
		position.x = 10;	
}

void TileViewer :: putOnRight(void)
{
	position.x = windowSize.width - pBackground->getSize().width - 10;
}

bool TileViewer :: draw(const NE::Renderer& r)
{
	bool error = true;
    USize2 backgroundSize = pBackground->getSize();

	IVec2 titleSize = pFont->getSize(title);
	IVec2 nameSize = pFont->getSize(tileName);
	IVec2 titlePosition((position.x + (backgroundSize.width - titleSize.x)/2) , position.y - titleSize.y/2);
	IVec2 tilePosition(position.x + (backgroundSize.width - pTileSprite->getSize().width)/2 , position.y + (backgroundSize.height - pTileSprite->getSize().height)/2);
	IVec2 namePosition(position.x + (backgroundSize.width - nameSize.x)/2 , tilePosition.y + pTileSprite->getSize().height + 2);

	LDebug << "TileViewer draw";

	error &= r.drawSurface(position,*pBackground);
	error &= pFont->draw(r,title,titlePosition);
	error &= pTileSprite->draw(r,tilePosition,0);
	error &= pFont->draw(r,tileName,namePosition);

	return error;
}

#endif
