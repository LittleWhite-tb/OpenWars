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

#include "MapGame.h"

#include "NEngine/SpriteLoader.h"
#include "NEngine/Sprite.h"

#include "NEngine/Renderer.h"

#include "Engine/AnimatedSprite.h"
#include "Engine/Theme.h"

#include "Game/Camera.h"

#include "Types/Vec2.h"
#include "Types/Colour.h"

#include "Utils/Logger.h"

#include "NEngine/Exceptions/ConstructionFailedException.h"
#include "globals.h"

MapGame :: MapGame(const Library<Theme>* const pThemes):Map(pThemes)
{
}

MapGame :: ~MapGame()
{
	
}

void MapGame :: enableUnits(void)
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
			unsigned int yOffset = tileMap[y][x]->getSprite()->getSize().height - TILE_DEFAULT_HEIGHT;

			// Apply offset
			tilePos.y -= yOffset;

			if ( unitMap[y][x].state != US_NO_UNIT )	// If we have a unit
			{
                if ( unitMap[y][x].state == US_ACTIVE )
                {
					bError &= unitMap[y][x].getSprite()->draw(r,tilePos,time);
                }
                else
                {
					bError &= unitMap[y][x].getSprite()->draw(r,tilePos,Colour(128,128,128,255),0);
                }
			}

			// Remove offset ( to not affect other sprite )
            tilePos.y += yOffset;
            
            // Move on the right
            tilePos.x += tileMap[y][x]->getSprite()->getSize().width;
        }

        // To put 0 here, can be a bit dangerous
        tilePos.y += TILE_DEFAULT_HEIGHT;
    }

    return bError;
}

bool MapGame :: setUnit(const UVec2& position, const std::string& unitName, unsigned int faction)
{
	unitMap[position.y][position.x] = Unit(pThemes->get(themeName)->getUnit(unitName,faction));
    return true;
}

const Unit* MapGame :: getUnit(const UVec2& position)
{
    if ( position.x < this->width && position.y < this->height )
    {
            return &unitMap[position.y][position.x];
    }
    else
    {
            return NULL;
    }
}

bool MapGame :: move(const UVec2& origPosition, const UVec2& destPosition)
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

//void MapGame :: setMoveHighlight(const UVec2& origPosition, const Unit& u, const int movement)
//{
//    // ToDo: Cost of the tile for movement
//	// Stopping condition
//    if ( movement <= 0 )
//    {
//        return;
//    }
//    
//	// TODO: Add faction detection
//	// If not same faction -> stop
//	// else this
//    if ( unitMap[origPosition.y][origPosition.x].state == US_NO_UNIT )
//    {
//        // effectMap[origPosition.y][origPosition.x].isHighlight = true;
//    }
//
//	// Continue the recursivity
//	TileType nextTileType;
//
//	// Right
//	UVec2 rightPosition(origPosition.x+1,origPosition.y);
//	// TODO, add test valid position
//	nextTileType = this->getTileType(rightPosition);
//	/*
//    if ( !effectMap[rightPosition.y][rightPosition.x].isHighlight && testTile(rightPosition, ut) )
//	{
//		setMoveHighlight(rightPosition,ut,movement-1);	
//	}
//	*/
//
//	// Up
//	UVec2 upPosition(origPosition.x,origPosition.y-1);
//	/*
//	nextTileType = this->getTileType(upPosition);
//    if ( nextTileType != TT_Invalid && !effectMap[upPosition.y][upPosition.x].isHighlight && testTile(upPosition, ut) )
//	{
//		setMoveHighlight(upPosition,ut,movement-1);	
//	}
//	*/
//
//	// Down
//	UVec2 downPosition(origPosition.x,origPosition.y+1);
//	/*
//	nextTileType = this->getTileType(downPosition);
//    if ( nextTileType != TT_Invalid && !effectMap[downPosition.y][downPosition.x].isHighlight && testTile(downPosition, ut) )
//	{
//		setMoveHighlight(downPosition,ut,movement-1);	
//	}
//	*/
//
//	// Left
//	UVec2 leftPosition(origPosition.x-1,origPosition.y);
//	/*
//	nextTileType = this->getTileType(leftPosition);
//    if ( nextTileType != TT_Invalid && !effectMap[leftPosition.y][leftPosition.x].isHighlight && testTile(leftPosition, ut) )
//	{
//		setMoveHighlight(leftPosition,ut,movement-1);	
//	}
//	*/
//}
//    
//void MapGame :: setAttackableHighLight(const UVec2& origPosition)
//{
//	/*
//    effectMap[origPosition.y][origPosition.x+1].isAttackable = true;
//    effectMap[origPosition.y][origPosition.x-1].isAttackable = true;
//    effectMap[origPosition.y+1][origPosition.x].isAttackable = true;
//    effectMap[origPosition.y-1][origPosition.x].isAttackable = true;
//	*/
//}
//    
//void MapGame :: clearHighlight(void)
//{
//    for ( unsigned int y = 0 ; y < this->height ; y++ )
//	{
//		for ( unsigned int x = 0 ; x < this->width ; x++ )
//		{
//            // effectMap[y][x].clear();
//        }
//    }
//}
