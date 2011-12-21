#ifndef DOXYGEN_IGNORE_TAG
/**
OpenAWars is an open turn by turn strategic game aiming to recreate the feeling of advance (famicon) wars (c)
Copyright (C) 2010-2011  Alexandre LAURENT

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

#include <list>
#include <algorithm>
#include <cassert>

#include "NEngine/SpriteLoader.h"
#include "NEngine/Sprite.h"

#include "Engine/Library.h"
#include "AnimatedSprite.h"
#include "Game/GameState/GameObjects/Tile.h"

#include "XML/XMLObjectReader.h"

#include "NEngine/Exceptions/FileNotFoundException.h"
#include "Utils/LineParser.h"

#include "globals.h"

Theme :: ~Theme(void)
{
}

bool Theme :: load(NE::SpriteLoader* const pSL)
{
    bool bResult = true;

    try
    {
        // Tiles
        {
            XMLObjectReader xmlReader(THEME_PATH + name+"/tiles.xml");
            bResult &= xmlReader.parse<Tile>("tile",&tiles, pSL, GFX_TILES_PATH + name + "/");
        }

        // Units
        {
            XMLObjectReader xmlReader(THEME_PATH +name+"/units.xml");
            bResult &= xmlReader.parse<UnitTemplate>("unit",&units, pSL, GFX_UNITS_PATH + name + "/");
        }

        // UIItems
        {
            XMLObjectReader xmlReader(THEME_PATH + name + "/ui.xml");
            bResult &= xmlReader.parse<UIItem>("uiItem",&uiItems,pSL,GFX_UI_PATH + name + "/");
        }

        // Fonts
        {
            XMLObjectReader xmlReader(THEME_PATH + name + "/fonts.xml");
            bResult &= xmlReader.parse<FontObject>("font",&fontsObject,pSL,GFX_FONTS_PATH + name + "/");
        }
    }
	catch ( XMLParsingFailedException xmlpfe )
    {
        NE::NEngine::logger()->log(NE::LL_Error,"%s",xmlpfe.what());
        return false;
    }
    catch ( FileNotFoundException fnfe )
    {
        NE::NEngine::logger()->log(NE::LL_Error,"%s",fnfe.what());
        return false;
    }

    return bResult;
}

bool Theme :: containsTile(unsigned int id)const
{
    std::list<const Tile*> tilesList;
    tiles.getValues(&tilesList);

    for ( std::list<const Tile*>::const_iterator itTile = tilesList.begin() ; itTile != tilesList.end() ; ++itTile )
    {
        if ( (*itTile)->getID() == id )
        {
            return true;
        }
    }

    return false;
}

bool Theme :: containsTile(const std::string& tileName)const
{
    return tiles.exists(tileName);
}

const Tile* Theme :: getTile(unsigned int id)const
{
    std::list<const Tile*> tilesList;
    tiles.getValues(&tilesList);

    for ( std::list<const Tile*>::const_iterator itTile = tilesList.begin() ; itTile != tilesList.end() ; ++itTile )
    {
        if ( (*itTile)->getID() == id )
        {
            return *itTile;
        }
    }

    assert(false); // Invalid ID;
    return NULL;
}

const Tile* Theme :: getTile(const std::string& tileName)const
{
    return tiles.get(tileName);
}

void Theme :: getTilesList(std::list< const Tile* >* pTilesList)const
{
    tiles.getValues(pTilesList);
}

bool Theme :: containsUnit(unsigned int id)const
{
    std::list<const UnitTemplateFactionList*> unitsList;
    units.getValues(&unitsList);

    for ( std::list<const UnitTemplateFactionList*>::const_iterator itUnit = unitsList.begin() ; itUnit != unitsList.end() ; ++itUnit )
    {
        for ( unsigned int i = 0 ; i < (*itUnit)->getNumberFaction() ; i++ )
        {
            if ( (*itUnit)->get(i)->getID() == id )
            {
                return true;
            }
        }
    }

    return false;
}

bool Theme :: containsUnit(const std::string& unitName)const
{
    return units.exists(unitName);
}

const UnitTemplate* Theme :: getUnit(unsigned int id)const
{
    std::list<const UnitTemplateFactionList*> unitsList;
    units.getValues(&unitsList);

    for ( std::list<const UnitTemplateFactionList*>::const_iterator itUnit = unitsList.begin() ; itUnit != unitsList.end() ; ++itUnit )
    {
        for ( unsigned int i = 0 ; i < (*itUnit)->getNumberFaction() ; i++ )
        {
            if ( (*itUnit)->get(i)->getID() == id )
            {
                return (*itUnit)->get(i);
            }
        }
    }

    assert(false); // Invalid ID;
    return NULL;
}

const UnitTemplate* Theme :: getUnit(const std::string& unitName, const unsigned int faction)const
{
    return units.get(unitName)->get(faction);
}

void Theme :: getUnitsList(std::list< const UnitTemplateFactionList* >* pUnitsList)const
{
    units.getValues(pUnitsList);
}


bool Theme :: containsUIItem(const std::string& uiName)const
{
    return uiItems.exists(uiName);
}

const UIItem* Theme :: getUIItem(const std::string& uiName)const
{
    return uiItems.get(uiName);
}

void Theme :: getUIITemsList(std::list< const UIItem* >* pUIItemsList)const
{
    uiItems.getValues(pUIItemsList);
}

bool Theme :: containsFontObject(const std::string& fontName)const
{
    return fontsObject.exists(fontName);
}

const FontObject* Theme :: getFontObject(const std::string& fontName)const
{
    return fontsObject.get(fontName);
}

void Theme :: getFontObjectList(std::list< const FontObject* >* pFontsObjectsList)const
{
    fontsObject.getValues(pFontsObjectsList);
}
