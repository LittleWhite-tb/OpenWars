#ifndef DOXYGEN_IGNORE_TAG
/**
OpenAWars is an open turn by turn strategic game similar to Advance Wars (c)
Copyright (C) 2010-2015  Alexandre LAURENT

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

website: https://github.com/LittleWhite-tb/OpenWars
e-mail: lw.demoscene@gmail.com
**/
#endif

#include "TileViewer.h"

#include "NEngine/Renderer.h"
#include "NEngine/Sprite.h"

#include "CEngine/AnimatedSprite.h"
#include "CEngine/Font.h"

#include "Engine/Theme.h"

#include "Game/GameState/GameObjects/Tile.h"
#include "Game/GameState/GameObjects/UnitTemplate.h"

#include "NEngine/NEngine.h"
#include "NEngine/Types/Vec2.h"
#include "NEngine/Types/Colour.h"

TileViewer :: TileViewer(const Theme* pTheme, const USize2& windowSize)
:windowSize(windowSize)
{
    Colour white(255,255,255,255);

    pBackground = pTheme->getUIItem("UIBackground")->getSprite();
    pFont = pTheme->getFontObject("classic")->getFont();

    USize2 backgroundSize = pBackground->getSize();
    position = IVec2(windowSize.width - backgroundSize.width - 10, windowSize.height - backgroundSize.height - 10);

    title = "Element";

    NEDebug << "TileViewer created\n";
}

TileViewer :: ~TileViewer()
{
    NEDebug << "TileViewer deleted\n";
}

void TileViewer :: setTile(const Tile* pTile)
{
    assert(pTile);

    this->pTileSprite = pTile->getSprite();
    this->tileName = pTile->getName();

    this->title = "Element";
}

void TileViewer :: setTile(const UnitTemplate* pUnitTemplate)
{
    assert(pUnitTemplate);

    this->pTileSprite = pUnitTemplate->getSprite();
    this->tileName = pUnitTemplate->getName();

    this->title = "Unit";
}

void TileViewer :: putOnLeft(void)
{
        position.x = 10;
}

void TileViewer :: putOnRight(void)
{
    position.x = windowSize.width - pBackground->getSize().width - 10;
}

bool TileViewer :: draw(const NE::Renderer& r, const unsigned int time)
{
    bool error = true;
    USize2 backgroundSize = pBackground->getSize();

    USize2 titleSize = pFont->getStringSize(title);
    USize2 nameSize = pFont->getStringSize(tileName);
    IVec2 titlePosition((position.x + static_cast<int>(backgroundSize.width - titleSize.width)/2), position.y);
    IVec2 tilePosition(position.x + (backgroundSize.width - pTileSprite->getSize().width)/2 , position.y + (backgroundSize.height - pTileSprite->getSize().height)/2);
    IVec2 namePosition(position.x + static_cast<int>(backgroundSize.width - nameSize.width)/2 , tilePosition.y + pTileSprite->getSize().height + 2);

    error &= pBackground->draw(r,position,time);
    error &= pFont->draw(r,title,titlePosition);
    error &= pTileSprite->draw(r,tilePosition,0);
    error &= pFont->draw(r,tileName,namePosition);

    return error;
}
