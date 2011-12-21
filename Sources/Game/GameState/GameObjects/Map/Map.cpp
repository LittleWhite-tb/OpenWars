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

#include "Map.h"

#include <string>

#include <string>
#include <sstream>
#include <fstream>
#include <cassert>

#include "NEngine/NEngine.h"
#include "NEngine/SpriteLoader.h"

#include "Engine/AnimatedSprite.h"
#include "Engine/Theme.h"
#include "Engine/Library.h"
#include "Engine/Params.h"

#include "Game/GameState/GameObjects/Map/ClassicMapIntegrityChecker.h"
#include "Game/GameState/GameObjects/Tile.h"
#include "Game/GameState/GameObjects/Unit.h"
#include "Game/GameState/GameObjects/Camera.h"

#include "NEngine/Types/Vec2.h"
#include "NEngine/Types/Colour.h"

#include "Utils/LineParser.h"

#include "NEngine/Exceptions/ConstructionFailedException.h"

#include "globals.h"

Map :: Map(const Theme* pTheme)
    :pTheme(pTheme),width(0),height(0)
{
    pIntegrityChecker = new ClassicMapIntegrityChecker(this);
}

Map :: ~Map(void)
{
    delete pIntegrityChecker;

    NE::NEngine::logger()->log(NE::LL_Debug,"Map deleted");
}

bool Map :: allocateMemory(const USize2& size)
{
    // Allocation tile map
    tileMap.resize(size.height);
    for ( unsigned int y = 0 ; y < size.height ; y++ )
    {
        tileMap[y].resize(size.width);
    }

    // Allocation of the unit map
    unitMap.resize(size.height);
    for ( unsigned int y = 0 ; y < size.height; y++ )
    {
        unitMap[y].resize(size.width);
    }

    this->width = size.width;
    this->height = size.height;

    return true;
}

const Tile* Map :: getTile(const UVec2& position)const
{
#ifdef VERBOSE
    LDebug << "Map :: getTile " << position;
#endif

    if ( position.x < this->width && position.y < this->height )
    {
        return tileMap[position.y][position.x];
    }
    else
    {
        return NULL;
    }
}

bool Map :: isValidPosition(const UVec2& position)const
{
    if ( position.x < this->width && position.y < this->height )
    {
        return true;
    }

    return false;
}

bool Map :: testTile(const UVec2& position, const Tile* pTile)const
{
    assert(pTile);

    return pIntegrityChecker->testTile(position,pTile);
}

bool Map :: testUnit(const UVec2& position, const UnitTemplate* pUnitTemplate)const
{
    assert(pUnitTemplate);

    return pIntegrityChecker->testUnit(position,pUnitTemplate);
}

Unit* Map :: getUnit(const UVec2& position)
{
    if ( isValidPosition(position) )
    {
            return &unitMap[position.y][position.x];
    }
    else
    {
            return NULL;
    }
}

const Unit* Map :: getUnit(const UVec2& position)const
{
    if ( isValidPosition(position) )
    {
            return &unitMap[position.y][position.x];
    }
    else
    {
            return NULL;
    }
}

void Map :: enableUnits(void)
{
    for ( unsigned int y = 0 ; y < height ; y++ )
    {
        for ( unsigned int x = 0 ; x < width ; x++ )
        {
            if ( this->unitMap[y][x].state != US_NO_UNIT )
            {
                unitMap[y][x].state = US_ACTIVE;
            }
        }
    }
}

bool Map :: move(const UVec2& origPosition, const UVec2& destPosition)
{
/*
    if ( effectMap[destPosition.y][destPosition.x].isHighlight == false )
    {
        return false;
    }
*/
    if ( origPosition == destPosition )
    {
        return false;
    }

    if ( origPosition.x >= this->width && origPosition.y >= this->height )
    {
        return false;
    }

    if ( unitMap[origPosition.y][origPosition.x].state != US_ACTIVE )
    {
        return false;
    }

/*
    // TODO, reimplement this !
    if ( !testTile(destPosition, unitMap[origPosition.y][origPosition.x]))
    {
        return false;
    }
 */

    // Move physical unit data
    unitMap[destPosition.y][destPosition.x] = unitMap[origPosition.y][origPosition.x];
    unitMap[origPosition.y][origPosition.x].state = US_NO_UNIT;

    // Unit moved
    unitMap[destPosition.y][destPosition.x].state = US_MOVED;

    return true;
}

bool Map :: setUnit(const UVec2& position, const std::string& unitName, unsigned int faction)
{
    if ( this->isValidPosition(position) )
    {
        if ( pIntegrityChecker->testUnit(position,pTheme->getUnit(unitName,faction)) )
        {
            unitMap[position.y][position.x] = Unit(pTheme->getUnit(unitName,faction));
            return true;
        }
    }
    return false;
}

bool Map :: setTile(const UVec2& position, const std::string& tileName)
{
    if ( this->isValidPosition(position) )
    {
        const Tile* pTileToPut = pTheme->getTile(tileName);
        if ( this->testTile(position,pTileToPut) == false )
        {
            return false;
        }

        // Only one HQ can be on the map
        if ( pTileToPut->getParams()->getAs<bool>("isHQ",false) )
        {
            // For each lines
            for ( unsigned int y = 0 ; y < this->height ; y++ )
            {
                // For each columns
                for ( unsigned int x = 0 ; x < this->width ; x++ )
                {
                    if ( tileMap[y][x] == pTileToPut )
                    {
                        tileMap[y][x] = pTheme->getTile(0);
                    }
                }
            }
        }

        this->checkCoherency(position,pTileToPut);
        // tileMap[position.y][position.x] = pTileToPut;

        const Unit* pUnit = this->getUnit(position);
        if ( pUnit && pUnit->state != US_NO_UNIT && this->testUnit(position,this->getUnit(position)->getTemplate()) == false )
        {
            // If not, removing it
            unitMap[position.y][position.x].state = US_NO_UNIT;
        }

        return true;
    }

    return false;
}

void Map :: checkCoherency(const UVec2& position, const Tile* pTileToPut)
{
    const Tile* pNewTile = NULL;
    pNewTile = pIntegrityChecker->checkCoherency(position,pTileToPut);
    if ( pNewTile != NULL )
    {
        tileMap[position.y][position.x] = pNewTile;
    }
    else
    {
        // No change on tile, so no need to check around
        return;
    }

    pNewTile = pIntegrityChecker->checkCoherency(UVec2(position.x-1,position.y)); // Left
    if ( pNewTile != NULL )
    {
        tileMap[position.y][position.x-1] = pNewTile;
    }

    pNewTile = pIntegrityChecker->checkCoherency(UVec2(position.x+1,position.y)); // Right
    if ( pNewTile != NULL )
    {
        tileMap[position.y][position.x+1] = pNewTile;
    }

    pNewTile = pIntegrityChecker->checkCoherency(UVec2(position.x,position.y-1)); // Up
    if ( pNewTile != NULL )
    {
        tileMap[position.y-1][position.x] = pNewTile;
    }

    pNewTile = pIntegrityChecker->checkCoherency(UVec2(position.x,position.y+1)); // Down
    if ( pNewTile != NULL )
    {
        tileMap[position.y+1][position.x] = pNewTile;
    }

    // Diagonals
    pNewTile = pIntegrityChecker->checkCoherency(UVec2(position.x-1,position.y+1)); // Down Left
    if ( pNewTile != NULL )
    {
        tileMap[position.y+1][position.x-1] = pNewTile;
    }

    pNewTile = pIntegrityChecker->checkCoherency(UVec2(position.x+1,position.y+1)); // Down Right
    if ( pNewTile != NULL )
    {
        tileMap[position.y+1][position.x+1] = pNewTile;
    }

    pNewTile = pIntegrityChecker->checkCoherency(UVec2(position.x-1,position.y-1)); // Up left
    if ( pNewTile != NULL )
    {
        tileMap[position.y-1][position.x-1] = pNewTile;
    }

    pNewTile = pIntegrityChecker->checkCoherency(UVec2(position.x+1,position.y-1)); // Up Right
    if ( pNewTile != NULL )
    {
        tileMap[position.y-1][position.x+1] = pNewTile;
    }
}
