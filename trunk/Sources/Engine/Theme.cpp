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

#include "Theme.h"

#include <cassert>

#include "../NEngine/SpriteLoader.h"
#include "../NEngine/Sprite.h"

#include "AnimatedSprite.h"

#include "../Utils/Exceptions/FileNotOpenedException.h"
#include "../Utils/LineParser.h"
#include "../Utils/Logger.h"

Theme :: ~Theme(void)
{
    for ( std::map<UIType, AnimatedSprite*>::iterator itPASprite = ui.begin() ; itPASprite != ui.end() ; ++itPASprite )
    {
        // Since if we have a NULL value ... the next one will not be init at all
        if ( itPASprite->second == NULL )
        {
            break;
        }

        delete itPASprite->second;
    }

    for ( std::map<UnitType, AnimatedSprite*>::iterator itPASprite = units.begin() ; itPASprite != units.end() ; ++itPASprite )
    {
        // Since if we have a NULL value ... the next one will not be init at all
        if ( itPASprite->second == NULL )
        {
            break;
        }

        delete itPASprite->second;
    }

    for ( std::map<TileType, AnimatedSprite*>::iterator itPASprite = tiles.begin() ; itPASprite != tiles.end() ; ++itPASprite )
    {
        // Since if we have a NULL value ... the next one will not be init at all
        if ( itPASprite->second == NULL )
        {
            break;
        }

        delete itPASprite->second;
    }
}

AnimatedSprite* Theme :: loadFromThemeFile(NE::SpriteLoader* const pSL, LineParser& lpTiles, const std::string& subFolder, const int number, int* pSpriteID)
{
    bool notAtEnd = true;

    int tileID = lpTiles.getInt();
    if ( tileID >= number )
    {
        LError << "ID not corresponding to any tile (Max expected: " << number << " Received: " << tileID << ")";
        return NULL;
    }

    *pSpriteID = tileID;

    notAtEnd &= lpTiles.readNextLine();
    std::string tilePath = lpTiles.getLine();
    notAtEnd &= lpTiles.readNextLine();
    USize2 spriteSize = lpTiles.getUSize2();
    notAtEnd &= lpTiles.readNextLine();
    int timeAnimation = lpTiles.getInt();
    notAtEnd &= lpTiles.readNextLine();

    NE::Sprite* pSprite = pSL->loadSpriteFromFile(subFolder + tilePath);
    if ( pSprite == NULL )
    {
        LError << "Fail to load the sprite: '" << tilePath << "'";
        return NULL;
    }

    if ( notAtEnd == false )
    {
        LError << "End of file unexpected";
        return NULL;
    }

    AnimatedSprite* pASprite = new AnimatedSprite(pSprite,spriteSize,timeAnimation);
    if ( pASprite == NULL )
    {
        LError << "Fail to allocate memory for AnimatedSprite in loadTiles";
    }

    return pASprite;
}

bool Theme :: load(NE::SpriteLoader* const pSL)
{
    bool bResult = true;

    try
    {
        LineParser lpTiles("data/themes/"+name+"/tiles.thm");
        LineParser lpUnits("data/themes/"+name+"/units.thm");
        LineParser lpUI("data/themes/"+name+"/ui.thm");

        bResult &= loadSprites<TileType>(pSL,lpTiles,"data/themes/"+name+"/tiles/",tiles,TT_END_LIST);
        bResult &= loadSprites<UnitType>(pSL,lpUnits,"data/themes/"+name+"/units/",units,UT_END_LIST);
        bResult &= loadSprites<UIType>(pSL,lpUI,"data/themes/"+name+"/ui/",ui,UIT_END_LIST);
    }
    catch ( FileNotOpenedException fnoe )
    {
        return false;
    }

    return bResult;
}

AnimatedSprite* Theme :: getTile(const TileType tType)
{
    assert(tType != TT_Invalid &&  tType != TT_END_LIST);

    return tiles[tType];
}

AnimatedSprite* Theme :: getUnit(const UnitType uType)
{
    assert(uType != UT_NO_UNIT &&  uType != UT_END_LIST);

    return units[uType];
}

AnimatedSprite* Theme :: getUI(const UIType uiType)
{
    assert(uiType < UIT_END_LIST);

    return ui[uiType];
}


