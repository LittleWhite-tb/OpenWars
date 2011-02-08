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

#include "MapGame.h"

#include "../NEngine/SpriteLoader.h"
#include "../NEngine/Sprite.h"

#include "../NEngine/Renderer.h"

#include "../Game/Camera.h"

#include "../Types/Vec2.h"
#include "../Types/Colour.h"

#include "../Utils/Logger.h"

#include "../NEngine/Exceptions/ConstructionFailedException.h"
#include "../globals.h"

MapGame :: MapGame(NE::SpriteLoader* const pSL, const std::string& fileName,const std::string& fileNameHighlight, const std::string& fileNameAttackable):Map(pSL,fileName),pHighlightSprite(NULL),pAttackableSprite(NULL)
{
	unitMap = new Unit**[this->height];
	if ( unitMap == NULL )
	{
		LError << "Fail to allocate memory for the unit map";
		valid = false;
		return;
	}

	for (unsigned int y = 0 ; y < this->height ; y++ )
	{
		unitMap[y] = new Unit*[this->width];
		if ( unitMap[y] == NULL)
		{
			LError << "Fail to allocate memory for the unit map (y=" << y << ")";
			valid = false;
			// It's smelling good the memory leak ...
			delete [] unitMap;
			return;
		}

		for ( unsigned int x = 0 ; x < this->width ; x++ )
		{
			unitMap[y][x] = NULL;
		}
	}
    
    effectMap = new TileEffect*[this->height];
    if ( effectMap == NULL )
    {
        LError << "Fail to allocate memory for the effect map";
		valid = false;
		return;
    }
    
    for ( unsigned int y = 0 ; y < this->height ; y++ )
    {
        effectMap[y] = new TileEffect[this->width];
        if ( effectMap[y] == NULL )
        {
            LError << "Fail to allocate memory for the effect map (y=" << y << ")";
            valid = false;
            // Memory leak ?
            delete [] effectMap;
            return;
        }
    }
    
    try
    {
        pHighlightSprite = pSL->loadSpriteFromFile(fileNameHighlight);
        pAttackableSprite = pSL->loadSpriteFromFile(fileNameAttackable);
    }
    catch ( ConstructionFailedException& cfe)
    {
        LError << "Fail to construct: " << cfe.what();
        valid = false;
    }

	LDebug << "MapGame created";
}

MapGame :: ~MapGame()
{
	for ( unsigned int y = 0 ; y < this->height ; y++ )
	{
		for ( unsigned int x = 0 ; x < this->width ; x++ )
		{
			delete unitMap[y][x];
		}

		delete[] unitMap[y];
	}

	delete[] unitMap;
    
    for ( unsigned int y = 0 ; y < this->height ; y++ )
    {
        delete [] effectMap[y];
    }
    
    delete [] effectMap;
}

void MapGame :: enableUnits(void)
{
    for ( unsigned int y = 0 ; y < height ; y++ )
	{
		for ( unsigned int x = 0 ; x < width ; x++ )
		{
			if ( this->unitViewMap[y][x] != UT_NO_UNIT )
			{
				unitMap[y][x]->enabled = true;
			}
        }
    }
}

bool MapGame :: draw(const NE::Renderer& r, const Camera& c, const unsigned int time)
{
	UVec2 cameraPosition = c.getPosition();
	// USize2 mapOffset = Scaler::getOffset();
	IVec2 tilePos(0,0/*mapOffset.height*/);
	bool bError = true;

	LDebug << "Map :: draw";

	this->drawTerrain(r,c,time);

	// The camera is an offset of the Map drawing
	// For each lines
	for ( unsigned int y = cameraPosition.y ; y < MAP_MIN_HEIGHT+cameraPosition.y ; y++ )
	{
		tilePos.x = 0;//mapOffset.width;
		// For each columns
		for ( unsigned int x = cameraPosition.x ; x < MAP_MIN_WIDTH+cameraPosition.x ; x++ )
		{
			// Calculation of the offset for sprite with higher size than normal Tile (e.g.: Mountains)
			unsigned int yOffset = tilesSet[map[y][x]].pASprite->getSize().height - TILE_DEFAULT_HEIGHT;

			// Apply offset
			tilePos.y -= yOffset;

			if ( unitViewMap[y][x] != UT_NO_UNIT )	// If we have a unit
			{
                if ( unitMap[y][x]->enabled )
                {
                    bError &= unitsSet[unitViewMap[y][x]].pASprite->draw(r,tilePos,time);
                }
                else
                {
					bError &= unitsSet[unitViewMap[y][x]].pASprite->draw(r,tilePos,Colour(128,128,128,255),0);
                }
			}

			// Remove offset ( to not affect other sprite )
            tilePos.y += yOffset;
            
            // Effects
            if ( effectMap[y][x].isHighlight )
            {
                bError &= r.drawSurface(tilePos,*pHighlightSprite);
            }
            if ( effectMap[y][x].isAttackable )
            {
                bError &= r.drawSurface(tilePos,*pAttackableSprite);
            }
            
            // Move on the right
            tilePos.x += tilesSet[map[y][x]].pASprite->getSize().width;
        }

        // To put 0 here, can be a bit dangerous
        tilePos.y += TILE_DEFAULT_HEIGHT;
    }

    return bError;
}

bool MapGame :: setTile(const UVec2& position, const UnitType unitType)
{
    unitViewMap[position.y][position.x] = unitType;
    if ( unitMap[position.y][position.x] != NULL )
    {
            delete unitMap[position.y][position.x];
    }

    unitMap[position.y][position.x] = new Unit(unitType, unitsSet[unitType]);

    return true;
}

const Unit* MapGame :: getUnit(const UVec2& position)
{
    if ( position.x < this->width && position.y < this->height )
    {
            return unitMap[position.y][position.x];
    }
    else
    {
            return NULL;
    }
}

bool MapGame :: move(const UVec2& origPosition, const UVec2& destPosition)
{
    if ( effectMap[destPosition.y][destPosition.x].isHighlight == false )
    {
        return false;
    }
    
    if ( origPosition == destPosition )
    {
        return false;
    }
    
    if ( origPosition.x >= this->width && origPosition.y >= this->height )
    {
        return false;
    }
    
    Unit* unit = unitMap[origPosition.y][origPosition.x];
    if ( unit == NULL )
    {
        return false;
    }
    
    if ( !testTile(destPosition, unit->type))
    {
        return false;
    }
    
    // Move physical unit data
    unitMap[origPosition.y][origPosition.x] = NULL;
    unitMap[destPosition.y][destPosition.x] = unit;
    
    // Move representation unit data
    unitViewMap[destPosition.y][destPosition.x] = unitViewMap[origPosition.y][origPosition.x];
    unitViewMap[origPosition.y][origPosition.x] = UT_NO_UNIT;
    
    unit->enabled = false;
    
    return true;
}

void MapGame :: setMoveHighlight(const UVec2& origPosition, const UnitType ut, const int movement)
{
    // ToDo: Cost of the tile for movement
	// Stopping condition
    if ( movement <= 0 )
    {
        return;
    }
    
	// TODO: Add faction detection
	// If not same faction -> stop
	// else this
    if ( (this->getUnitType(origPosition) == UT_NO_UNIT) )
    {
        effectMap[origPosition.y][origPosition.x].isHighlight = true;
    }

	// Continue the recursivity
	TileType nextTileType;

	// Right
	UVec2 rightPosition(origPosition.x+1,origPosition.y);
	nextTileType = this->getTileType(rightPosition);
    if ( nextTileType != TT_Invalid && !effectMap[rightPosition.y][rightPosition.x].isHighlight && testTile(rightPosition, ut) )
	{
		setMoveHighlight(rightPosition,ut,movement-1);	
	}

	// Up
	UVec2 upPosition(origPosition.x,origPosition.y-1);
	nextTileType = this->getTileType(upPosition);
    if ( nextTileType != TT_Invalid && !effectMap[upPosition.y][upPosition.x].isHighlight && testTile(upPosition, ut) )
	{
		setMoveHighlight(upPosition,ut,movement-1);	
	}

	// Down
	UVec2 downPosition(origPosition.x,origPosition.y+1);
	nextTileType = this->getTileType(downPosition);
    if ( nextTileType != TT_Invalid && !effectMap[downPosition.y][downPosition.x].isHighlight && testTile(downPosition, ut) )
	{
		setMoveHighlight(downPosition,ut,movement-1);	
	}

	// Left
	UVec2 leftPosition(origPosition.x-1,origPosition.y);
	nextTileType = this->getTileType(leftPosition);
    if ( nextTileType != TT_Invalid && !effectMap[leftPosition.y][leftPosition.x].isHighlight && testTile(leftPosition, ut) )
	{
		setMoveHighlight(leftPosition,ut,movement-1);	
	}
}
    
void MapGame :: setAttackableHighLight(const UVec2& origPosition)
{
    effectMap[origPosition.y][origPosition.x+1].isAttackable = true;
    effectMap[origPosition.y][origPosition.x-1].isAttackable = true;
    effectMap[origPosition.y+1][origPosition.x].isAttackable = true;
    effectMap[origPosition.y-1][origPosition.x].isAttackable = true;
}
    
void MapGame :: clearHighlight(void)
{
    for ( unsigned int y = 0 ; y < this->height ; y++ )
	{
		for ( unsigned int x = 0 ; x < this->width ; x++ )
		{
            effectMap[y][x].clear();
        }
    }
}
