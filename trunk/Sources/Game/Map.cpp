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

#include "Tile.h"
#include "Unit.h"

#include "NEngine/SpriteLoader.h"
#include "Engine/AnimatedSprite.h"

#include "Camera.h"

#include "Engine/Theme.h"
#include "Engine/Library.h"
#include "Engine/Params.h"

#include "Types/Vec2.h"
#include "Types/Colour.h"

#include "Utils/LineParser.h"
#include "Utils/Logger.h"

#include "NEngine/Exceptions/ConstructionFailedException.h"
#include "Utils/Exceptions/FileNotOpenedException.h"

#include "globals.h"

Map :: Map(const Theme* pTheme)
	:pTheme(pTheme),width(0),height(0)
{
}

Map :: ~Map(void)
{
	LDebug << "Map deleted";
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

bool Map :: drawTerrain(const NE::Renderer& r, const Camera& c, const unsigned int time)
{
	UVec2 cameraPosition = c.getPosition();
	// USize2 mapOffset = Scaler::getOffset();
	IVec2 tilePos(0,0/*mapOffset.height*/);
	bool bResult = true;

	LDebug << "Map :: drawTerrain";

	// The camera is an offset of the Map drawing
	// For each lines
	for ( unsigned int y = cameraPosition.y ; y < MAP_MIN_HEIGHT+cameraPosition.y ; y++ )
	{
		tilePos.x = 0; //mapOffset.width;
		// For each columns
		for ( unsigned int x = cameraPosition.x ; x < MAP_MIN_WIDTH+cameraPosition.x ; x++ )
		{
			// Calculation of the offset for sprite with higher size than normal Tile (e.g.: Mountains)
			unsigned int yOffset = tileMap[y][x]->getSprite()->getSize().height - TILE_DEFAULT_HEIGHT;

			// Draw the background sprite ( Plain )
			if ( tileMap[y][x]->getParams()->getAs<bool>("needBackground",false) )
			{
				bResult &= pTheme->getTile("Plain")->getSprite()->draw(r,tilePos,0);
			}

			// Apply offset
			tilePos.y -= yOffset;

			bResult &= tileMap[y][x]->getSprite()->draw(r,tilePos,time);
			
			// Move on the right
			tilePos.x += tileMap[y][x]->getSprite()->getSize().width;

			// Remove offset ( to not affect other sprite )
			tilePos.y += yOffset;
		}

		tilePos.y += TILE_DEFAULT_HEIGHT;
	}

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

/*
bool Map :: testTile(const UVec2& position, const UnitType unitType)const
{
	TileType tileType = this->getTileType(position);

	if ( tileType >= TT_Invalid )
	{
		assert(0);
		return false;
	}

	switch ( unitType )
	{
		case UT_NO_UNIT:
			return true;
			break;

		case UT_R_INFANTRY:
		case UT_B_INFANTRY:
		case UT_G_INFANTRY:
		case UT_Y_INFANTRY:
		case UT_R_BAZOOKA:
		case UT_B_BAZOOKA:
		case UT_G_BAZOOKA:
		case UT_Y_BAZOOKA:
			{
				if ( !tilesSet.find(tileType)->second.isSea )
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			break;

		case UT_R_RECON:
		case UT_B_RECON:
		case UT_G_RECON:
		case UT_Y_RECON:
		case UT_R_TANK:
		case UT_B_TANK:
		case UT_G_TANK:
		case UT_Y_TANK:
		case UT_R_TANKM:
		case UT_B_TANKM:
		case UT_G_TANKM:
		case UT_Y_TANKM:
		case UT_R_NEOTANK:
		case UT_B_NEOTANK:
		case UT_G_NEOTANK:
		case UT_Y_NEOTANK:
		case UT_R_ANTIAIR:
		case UT_B_ANTIAIR:
		case UT_G_ANTIAIR:
		case UT_Y_ANTIAIR:
		case UT_R_ARTILLERY:
		case UT_B_ARTILLERY:
		case UT_G_ARTILLERY:
		case UT_Y_ARTILLERY:
		case UT_R_ROCKETS:
		case UT_B_ROCKETS:
		case UT_G_ROCKETS:
		case UT_Y_ROCKETS:
		case UT_R_MISSILES:
		case UT_B_MISSILES:
		case UT_G_MISSILES:
		case UT_Y_MISSILES:
		case UT_R_APC:
		case UT_B_APC:
		case UT_G_APC:
		case UT_Y_APC:
			{
				if ( !tilesSet.find(tileType)->second.isSea && !tilesSet.find(tileType)->second.isRiver && !tilesSet.find(tileType)->second.isBeach && tileType != TT_Mountain_1 && tileType != TT_Mountain_2 )
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			break;


		case UT_R_LANDER:
		case UT_B_LANDER:
		case UT_G_LANDER:
		case UT_Y_LANDER:
			{
				if ( tilesSet.find(tileType)->second.isSea && tilesSet.find(tileType)->second.isBeach )
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			break;

		case UT_R_SUB:
		case UT_B_SUB:
		case UT_G_SUB:
		case UT_Y_SUB:
		case UT_R_BOMBERSHIP:
		case UT_B_BOMBERSHIP:
		case UT_G_BOMBERSHIP:
		case UT_Y_BOMBERSHIP:
		case UT_R_CRUISER:
		case UT_B_CRUISER:
		case UT_G_CRUISER:
		case UT_Y_CRUISER:
			{
				if ( tilesSet.find(tileType)->second.isSea )
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			break;

		case UT_R_TCOPTER:
		case UT_B_TCOPTER:
		case UT_G_TCOPTER:
		case UT_Y_TCOPTER:
		case UT_R_COPTER:
		case UT_B_COPTER:
		case UT_G_COPTER:
		case UT_Y_COPTER:
		case UT_R_FIGHTER:
		case UT_B_FIGHTER:
		case UT_G_FIGHTER:
		case UT_Y_FIGHTER:
		case UT_R_BOMBER:
		case UT_B_BOMBER:
		case UT_G_BOMBER:
		case UT_Y_BOMBER:
			return true;
			break;
		// Should not be used
		case UT_END_LIST:
			assert(0);
			break;
	}

	return true;
}
*/

bool Map :: isValidPosition(const UVec2& position)
{
	if ( position.x < this->width && position.y < this->height )
	{
		return true;
	}

	return false;
}

bool Map :: testTile(const UVec2& position, const Tile* pTile)
{
	// TODO

	return true;
}

bool Map :: testUnit(const UVec2& position, const UnitTemplate* pUnitTemplate)
{
	// TODO

	return true;
}

const Unit* Map :: getUnit(const UVec2& position)
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

bool Map :: draw(const NE::Renderer& r, const Camera& c, const unsigned int time)
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

bool Map :: setUnit(const UVec2& position, const std::string& unitName, unsigned int faction)
{
	unitMap[position.y][position.x] = Unit(pTheme->getUnit(unitName,faction));
    return true;
}

bool Map :: setTile(const UVec2& position, const std::string& tileName)
{
	// Extra protections
	assert(position.x < this->width);
	assert(position.y < this->height);

	LDebug << "Map :: setTile " << position << " Tile: " << tileName;

	if ( this->testTile(position,pTheme->getTile(tileName)) == false )
	{
		return false;
	}

	// Check if the tile below is the same // or one equivalent
	if ( tileMap[position.y][position.x]->getID() == tileMap[position.y][position.x]->getID() )
		return true;
	
	if ( pTheme->getTile(tileName)->getParams()->getAs<bool>("isRoad",false) == true )
		if ( tileMap[position.y][position.x]->getParams()->getAs<bool>("isRoad",false) == true )
			return true;
	
/*
	Test a bit too difficult to not restrict user

	if ( pTheme->getTile(tileName)->getParams()->getAs<bool>("isSea",false) == true )
		if ( tileMap[position.y][position.x]->getParams()->getAs<bool>("isSea",false) == true )
			return true;
	
	if ( pTheme->getTile(tileName)->getParams()->getAs<bool>("isBeach",false) ==  true )
		if ( tileMap[position.y][position.x]->getParams()->getAs<bool>("isBeach",false) == true )
			return true;
*/
	if ( pTheme->getTile(tileName)->getParams()->getAs<bool>("isRiver",false) == true )
		if ( tileMap[position.y][position.x]->getParams()->getAs<bool>("isRiver",false) == true )
			return true;
	
	if ( pTheme->getTile(tileName)->getParams()->getAs<bool>("isBridge",false) == true )
		if ( tileMap[position.y][position.x]->getParams()->getAs<bool>("isBridge",false) == true )
			return true;

	std::string name = this->getTile(position)->getInternalName();
	if ( name == "Plain" )
	{
		return setPlain(position);
	}
	else if ( name == "Tree" )
	{
		return setTree(position);
	}
	else if ( name == "Montain_1" || name == "Montain_2" )
	{
		return setMountain(position);
	}
	else if ( name == "Road_H" )
	{
		return setRoad(position);
	}
	else if ( name == "Sea" )
	{
		return setSea(position);
	}
	else if ( name == "Reef" )
	{
		return setReef(position);
	}
	else if ( name == "Beach_T" )
	{
		return setBeach(position);
	}
	else if ( name == "River_H" )
	{
		return setRiver(position);
	}
	else if ( name == "Bridge_H" )
	{
		return setBridge(position);
	}

	// For buildings
	if ( pTheme->getTile(tileName)->getParams()->getAs<bool>("isBuilding",false) == true )
	{
		return setBuilding(position,tileName);
	}

	assert(0);	// All cases have to be handled

	return false;
}

void Map :: checkCoherencyAround(const UVec2& position)
{
	checkCoherency(UVec2(position.x-1,position.y)); // Left
	checkCoherency(UVec2(position.x+1,position.y)); // Right
	checkCoherency(UVec2(position.x,position.y-1)); // Up
	checkCoherency(UVec2(position.x,position.y+1)); // Down

	// Diagonals
	checkCoherency(UVec2(position.x-1,position.y+1)); // Down Left
	checkCoherency(UVec2(position.x+1,position.y+1)); // Down Right
	checkCoherency(UVec2(position.x-1,position.y-1)); // Up Left
	checkCoherency(UVec2(position.x+1,position.y-1)); // Up Right

	// Check if the unit that was here can stay or not
	/*
	TODO back this line
	if ( this->Map::testTile(position,this->getUnitType(position)) == false )
	{
		// If not, removing it
		unitMap[position.y][position.x].state = US_NO_UNIT;
	}
	*/
}

void Map :: checkCoherency(const UVec2& position)
{
	// We check the type
	if ( isValidPosition(position) )
	{
		if ( tileMap[position.y][position.x]->getParams()->getAs<bool>("isRoad",false) )	// For road, we have to count the number of road.
		{
			checkCoherencyForRoad(position);
		}
		
		if ( tileMap[position.y][position.x]->getParams()->getAs<bool>("isSea",false) )
		{
			checkCoherencyForSee(position);
		}
		
		if ( tileMap[position.y][position.x]->getParams()->getAs<bool>("isRiver",false) )
		{
			checkCoherencyForRiver(position);
		}
	}
}

void Map :: checkCoherencyForRoad(const UVec2& position)
{
	unsigned char nbRoadAround = 0;
	bool isVerticalRoad = false;
	bool isHorizontalRoad = false;
	bool onLeft = false;
	bool onRight = false;
	bool onUp = false;
	bool onDown = false;
		
	if ( this->getTile(UVec2(position.x-1,position.y))->getParams()->getAs<bool>("isRoad",false) || 
		this->getTile(UVec2(position.x-1,position.y))->getParams()->getAs<bool>("isBridge",false) || 
		this->getTile(UVec2(position.x-1,position.y))->getParams()->getAs<bool>("isHQ",false) )	// Left
	{
		nbRoadAround++;
		isHorizontalRoad = true;
		onLeft = true;
	}
	
	if ( this->getTile(UVec2(position.x+1,position.y))->getParams()->getAs<bool>("isRoad",false) || 
		this->getTile(UVec2(position.x+1,position.y))->getParams()->getAs<bool>("isBridge",false) || 
		this->getTile(UVec2(position.x+1,position.y))->getParams()->getAs<bool>("isHQ",false) ) // Right
	{
		nbRoadAround++;
		isHorizontalRoad = true;
		onRight = true;
	}

	if ( this->getTile(UVec2(position.x,position.y-1))->getParams()->getAs<bool>("isRoad",false) || 
		this->getTile(UVec2(position.x,position.y-1))->getParams()->getAs<bool>("isBridge",false) || 
		this->getTile(UVec2(position.x,position.y-1))->getParams()->getAs<bool>("isHQ",false) ) // Up
	{
		nbRoadAround++;
		isVerticalRoad = true;
		onUp = true;
	}

	if ( this->getTile(UVec2(position.x,position.y+1))->getParams()->getAs<bool>("isRoad",false) || 
		this->getTile(UVec2(position.x,position.y+1))->getParams()->getAs<bool>("isBridge",false) || 
		this->getTile(UVec2(position.x,position.y+1))->getParams()->getAs<bool>("isHQ",false) ) // Down
	{
		nbRoadAround++;
		isVerticalRoad = true;
		onDown = true;
	}

	switch(nbRoadAround)
	{
		case 0:
			this->tileMap[position.y][position.x] = pTheme->getTile("Road_H");	// The default one
			break;
		case 1:
			if ( isVerticalRoad )
			{
				this->tileMap[position.y][position.x] = pTheme->getTile("Road_V");	// The default one
			}
			else if ( isHorizontalRoad )
			{
				this->tileMap[position.y][position.x] = pTheme->getTile("Road_H");
			}
			break;
		case 2: // Can be a line or a corner
			// Line case
			if ( isVerticalRoad && !isHorizontalRoad )
			{
				this->tileMap[position.y][position.x] = pTheme->getTile("Road_V");
			}

			if ( isHorizontalRoad && !isVerticalRoad )
			{
				this->tileMap[position.y][position.x] = pTheme->getTile("Road_H");
			}

			if ( onLeft && onUp )
			{
				this->tileMap[position.y][position.x] = pTheme->getTile("Road_TL");
			}

			if ( onRight && onUp )
			{
				this->tileMap[position.y][position.x] = pTheme->getTile("Road_TR");
			}

			if ( onLeft && onDown )
			{
				this->tileMap[position.y][position.x] = pTheme->getTile("Road_BL");
			}

			if ( onRight && onDown )
			{
				this->tileMap[position.y][position.x] = pTheme->getTile("Road_BR");
			}
			break;

		case 3: // Will be a T
			if ( onLeft && onRight && onUp )
			{
				this->tileMap[position.y][position.x] = pTheme->getTile("Road_T_T");
			}

			if ( onLeft && onRight && onDown )
			{
				this->tileMap[position.y][position.x] = pTheme->getTile("Road_T_B");
			}

			if ( onUp && onDown && onLeft )
			{
				this->tileMap[position.y][position.x] = pTheme->getTile("Road_T_L");
			}

			if ( onUp && onDown && onRight )
			{
				this->tileMap[position.y][position.x] = pTheme->getTile("Road_T_R");
			}
			break;
		case 4:
			this->tileMap[position.y][position.x] = pTheme->getTile("Road_X");
			break;
	}
}

void Map :: checkCoherencyForSee(const UVec2& position)
{
	unsigned char nbSeeAround = 0;
	bool isVerticalSee = false;
	bool isHorizontalSee = false;
	bool onLeft = false;
	bool onRight = false;
	bool onUp = false;
	bool onDown = false;
	bool onUpLeft = false;
	bool onUpRight = false;
	bool onDownLeft = false;
	bool onDownRight = false;
	bool isBeach = this->getTile(position)->getParams()->getAs<bool>("isBeach",false);
	bool beachOnLeft = false;
	bool beachOnRight = false;
	bool beachOnDown = false;
	bool beachOnUp = false;
	unsigned char nbSeeDiagonal = 0;
		
	// Check the 8 tiles around and set the flags
	if ( this->getTile(UVec2(position.x-1,position.y))->getParams()->getAs<bool>("isSea",false) || 
		this->getTile(UVec2(position.x-1,position.y))->getParams()->getAs<bool>("isBridge",false) )	// Left
	{
		nbSeeAround++;
		isHorizontalSee = true;
		onLeft = true;

		if ( this->getTile(UVec2(position.x-1,position.y))->getParams()->getAs<bool>("isBeach",false) )
		{
			beachOnLeft = true;
		}
	}
	
	if ( this->getTile(UVec2(position.x+1,position.y))->getParams()->getAs<bool>("isSea",false) || 
		this->getTile(UVec2(position.x+1,position.y))->getParams()->getAs<bool>("isBridge",false) ) // Right
	{
		nbSeeAround++;
		isHorizontalSee = true;
		onRight = true;

		if ( this->getTile(UVec2(position.x+1,position.y))->getParams()->getAs<bool>("isBeach",false) )
		{
			beachOnRight = true;
		}
	}

	if ( this->getTile(UVec2(position.x,position.y-1))->getParams()->getAs<bool>("isSea",false) || 
		this->getTile(UVec2(position.x,position.y-1))->getParams()->getAs<bool>("isBridge",false) ) // Up
	{
		nbSeeAround++;
		isVerticalSee = true;
		onUp = true;

		if ( this->getTile(UVec2(position.x,position.y-1))->getParams()->getAs<bool>("isBeach",false) )
		{
			beachOnUp = true;
		}
	}

	if ( this->getTile(UVec2(position.x,position.y+1))->getParams()->getAs<bool>("isSea",false) || 
		this->getTile(UVec2(position.x,position.y+1))->getParams()->getAs<bool>("isBridge",false) ) // Down
	{
		nbSeeAround++;
		isVerticalSee = true;
		onDown = true;

		if ( this->getTile(UVec2(position.x,position.y+1))->getParams()->getAs<bool>("isBeach",false) )
		{
			beachOnDown = true;
		}
	}

	if ( this->getTile(UVec2(position.x-1,position.y-1))->getParams()->getAs<bool>("isSea",false) || 
		this->getTile(UVec2(position.x-1,position.y-1))->getParams()->getAs<bool>("isBridge",false) ) // Up Left
	{
		// nbSeeAround++;
		nbSeeDiagonal++;
		onUpLeft = true;
	}

	if ( this->getTile(UVec2(position.x+1,position.y-1))->getParams()->getAs<bool>("isSea",false) || 
		this->getTile(UVec2(position.x+1,position.y-1))->getParams()->getAs<bool>("isBridge",false) ) // Up Right
	{
		// nbSeeAround++;
		nbSeeDiagonal++;
		onUpRight = true;
	}

	if ( this->getTile(UVec2(position.x-1,position.y+1))->getParams()->getAs<bool>("isSea",false) || 
		this->getTile(UVec2(position.x-1,position.y+1))->getParams()->getAs<bool>("isBridge",false) ) // Down Left
	{
		// nbSeeAround++;
		nbSeeDiagonal++;
		onDownLeft = true;
	}

	if ( this->getTile(UVec2(position.x+1,position.y+1))->getParams()->getAs<bool>("isSea",false) || 
		this->getTile(UVec2(position.x+1,position.y+1))->getParams()->getAs<bool>("isBridge",false) ) // Down Right
	{
		// nbSeeAround++;
		nbSeeDiagonal++;
		onDownRight = true;
	}


	switch(nbSeeAround)
	{
		case 0:
			// Diagonals are not important here
			this->tileMap[position.y][position.x] = pTheme->getTile("Coast");	// The default one
			break;
		case 1:
			// Diagonals are not important here
			if ( onLeft )
			{
				if ( isBeach )
				{
					this->tileMap[position.y][position.x] = pTheme->getTile("Beach_ER");
				}
				else
				{
					this->tileMap[position.y][position.x] = pTheme->getTile("Coast_ER");
				}
			}
			else if ( onRight )
			{
				if ( isBeach )
				{
					this->tileMap[position.y][position.x] = pTheme->getTile("Beach_EL");
				}
				else
				{
					this->tileMap[position.y][position.x] = pTheme->getTile("Coast_EL");
				}
			}
			else if ( onUp )
			{
				if ( isBeach )
				{
					this->tileMap[position.y][position.x] = pTheme->getTile("Beach_EB");
				}
				else
				{
					this->tileMap[position.y][position.x] = pTheme->getTile("Coast_EB");
				}
			}
			else if ( onDown )
			{
				if ( isBeach )
				{
					this->tileMap[position.y][position.x] = pTheme->getTile("Beach_ET");
				}
				else
				{
					this->tileMap[position.y][position.x] = pTheme->getTile("Coast_ET");
				}
			}
			break;
		case 2: // Can be a line or a corner
			// Line case
			if ( isVerticalSee && !isHorizontalSee )
			{
				this->tileMap[position.y][position.x] = pTheme->getTile("Coast_V");
			}

			if ( isHorizontalSee && !isVerticalSee )
			{
				this->tileMap[position.y][position.x] = pTheme->getTile("Coast_H");
			}

			// Corners
			if ( onLeft && onUp )
			{
				if ( onUpLeft )
				{
					if ( isBeach )
					{
						this->tileMap[position.y][position.x] = pTheme->getTile("Beach_BR");
						if ( beachOnUp )
						{
							this->tileMap[position.y][position.x] = pTheme->getTile("Beach_BR_T");
						}
						else if ( beachOnLeft )
						{
							this->tileMap[position.y][position.x] = pTheme->getTile("Beach_BR_L");
						}
						if ( beachOnUp && beachOnLeft )
						{
							this->tileMap[position.y][position.x] = pTheme->getTile("Beach_BR_2");
						}
					}
					else
					{
						this->tileMap[position.y][position.x] = pTheme->getTile("Coast_BR");
					}
				}
				else
				{
					this->tileMap[position.y][position.x] = pTheme->getTile("Coast_RBR");
				}
			}

			if ( onRight && onUp )
			{
				if ( onUpRight )
				{
					if ( isBeach )
					{
						this->tileMap[position.y][position.x] = pTheme->getTile("Beach_BL");
						if ( beachOnUp )
						{
							this->tileMap[position.y][position.x] = pTheme->getTile("Beach_BL_T");
						}
						else if ( beachOnRight )
						{
							this->tileMap[position.y][position.x] = pTheme->getTile("Beach_BL_R");
						}
						if ( beachOnUp && beachOnRight )
						{
							this->tileMap[position.y][position.x] = pTheme->getTile("Beach_BL_2");
						}
					}
					else
					{
						this->tileMap[position.y][position.x] = pTheme->getTile("Coast_BL");
					}					
				}
				else
				{
					this->tileMap[position.y][position.x] = pTheme->getTile("Coast_RBL");
				}
			}

			if ( onLeft && onDown )
			{
				if ( onDownLeft )
				{
					if ( isBeach )
					{
						this->tileMap[position.y][position.x] = pTheme->getTile("Beach_TR");
						if ( beachOnDown )
						{
							this->tileMap[position.y][position.x] = pTheme->getTile("Beach_TR_B");
						}
						else if ( beachOnLeft )
						{
							this->tileMap[position.y][position.x] = pTheme->getTile("Beach_TR_L");
						}
						if ( beachOnDown && beachOnLeft )
						{
							this->tileMap[position.y][position.x] = pTheme->getTile("Beach_TR_2");
						}
					}
					else
					{
						this->tileMap[position.y][position.x] = pTheme->getTile("Coast_TR");
					}
				}
				else
				{
					this->tileMap[position.y][position.x] = pTheme->getTile("Coast_RTR");
				}
			}

			if ( onRight && onDown )
			{
				if ( onDownRight )
				{
					if ( isBeach )
					{
						this->tileMap[position.y][position.x] = pTheme->getTile("Beach_TL");
						if ( beachOnDown )
						{
							this->tileMap[position.y][position.x] = pTheme->getTile("Beach_TL_B");
						}
						else if ( beachOnRight )
						{
							this->tileMap[position.y][position.x] = pTheme->getTile("Beach_TL_R");
						}
						if ( beachOnDown && beachOnRight )
						{
							this->tileMap[position.y][position.x] = pTheme->getTile("Beach_TL_2");
						}
					}
					else
					{
						this->tileMap[position.y][position.x] = pTheme->getTile("Coast_TL");
					}
				}
				else
				{
					this->tileMap[position.y][position.x] = pTheme->getTile("Coast_RTL");
				}
			}

			break;

		case 3: // Can be a T, or a corner 
			if ( onLeft && onRight && onUp )
			{
				this->tileMap[position.y][position.x] = pTheme->getTile("Coast_T_B");

				if ( nbSeeDiagonal >= 1 )
				{
					if ( onUpLeft )
					{
						this->tileMap[position.y][position.x] = pTheme->getTile("Coast_T_BR");
					}
					
					if ( onUpRight )
					{
						this->tileMap[position.y][position.x] = pTheme->getTile("Coast_T_BL");
					}	

					if ( onUpLeft && onUpRight )
					{
						if ( isBeach )
						{
							this->tileMap[position.y][position.x] = pTheme->getTile("Beach_B");
							if ( beachOnLeft )
							{
								this->tileMap[position.y][position.x] = pTheme->getTile("Beach_B_L");
							}
							else if ( beachOnRight )
							{
								this->tileMap[position.y][position.x] = pTheme->getTile("Beach_B_R");
							}
							if ( beachOnRight && beachOnLeft )
							{
								this->tileMap[position.y][position.x] = pTheme->getTile("Beach_B_2");
							}
						}
						else
						{
							this->tileMap[position.y][position.x] = pTheme->getTile("Coast_B");
						}

						if ( this->getTile(UVec2(position.x,position.y+1)) == pTheme->getTile("River_V") && this->getTile(UVec2(position.x,position.y+2)) == pTheme->getTile("River_V") )
						{
							this->tileMap[position.y][position.x] = pTheme->getTile("River_See_B");
						}
					}
				}
			}

			if ( onLeft && onRight && onDown )
			{
				this->tileMap[position.y][position.x] = pTheme->getTile("Coast_T_T");

				if ( nbSeeDiagonal >= 1 )
				{
					if ( onDownLeft )
					{
						this->tileMap[position.y][position.x] = pTheme->getTile("Coast_T_TR");
					}
					
					if ( onDownRight )
					{
						this->tileMap[position.y][position.x] = pTheme->getTile("Coast_T_TL");
					}	

					if ( onDownLeft && onDownRight )
					{
						if ( isBeach )
						{
							this->tileMap[position.y][position.x] = pTheme->getTile("Beach_T");
							if ( beachOnLeft )
							{
								this->tileMap[position.y][position.x] = pTheme->getTile("Beach_T_L");
							}
							else if ( beachOnRight )
							{
								this->tileMap[position.y][position.x] = pTheme->getTile("Beach_T_R");
							}
							if ( beachOnRight && beachOnLeft )
							{
								this->tileMap[position.y][position.x] = pTheme->getTile("Beach_T_2");
							}
						}
						else
						{
							this->tileMap[position.y][position.x] = pTheme->getTile("Coast_T");
						}

						if ( this->getTile(UVec2(position.x,position.y-1)) == pTheme->getTile("River_V") && this->getTile(UVec2(position.x,position.y-2)) == pTheme->getTile("River_V") )
						{
							this->tileMap[position.y][position.x] = pTheme->getTile("River_See_T");
						}
					}
				}
			}

			if ( onUp && onDown && onLeft )
			{
				this->tileMap[position.y][position.x] = pTheme->getTile("Coast_T_R");

				if ( nbSeeDiagonal >= 1 )
				{
					if ( onUpLeft )
					{
						this->tileMap[position.y][position.x] = pTheme->getTile("Coast_T_RB");
					}
					
					if ( onDownLeft )
					{
						this->tileMap[position.y][position.x] = pTheme->getTile("Coast_T_RT");
					}	

					if ( onUpLeft && onDownLeft )
					{
						if ( isBeach )
						{
							this->tileMap[position.y][position.x] = pTheme->getTile("Beach_R");
							if ( beachOnUp )
							{
								this->tileMap[position.y][position.x] = pTheme->getTile("Beach_R_T");
							}
							else if ( beachOnDown )
							{
								this->tileMap[position.y][position.x] = pTheme->getTile("Beach_R_B");
							}
							if ( beachOnUp && beachOnDown )
							{
								this->tileMap[position.y][position.x] = pTheme->getTile("Beach_R_2");
							}
						}
						else
						{
							this->tileMap[position.y][position.x] = pTheme->getTile("Coast_R");
						}

						if ( this->getTile(UVec2(position.x+1,position.y)) == pTheme->getTile("River_H") && this->getTile(UVec2(position.x+2,position.y)) == pTheme->getTile("River_H") )
						{
							this->tileMap[position.y][position.x] = pTheme->getTile("River_See_R");
						}
					}
				}
			}

			if ( onUp && onDown && onRight )
			{
				this->tileMap[position.y][position.x] = pTheme->getTile("Coast_T_L");

				if ( nbSeeDiagonal >= 1 )
				{
					if ( onUpRight)
					{
						this->tileMap[position.y][position.x] = pTheme->getTile("Coast_T_LB");
					}
					
					if ( onDownRight )
					{
						this->tileMap[position.y][position.x] = pTheme->getTile("Coast_T_LT");
					}	

					if ( onDownRight && onUpRight )
					{
						if ( isBeach )
						{
							this->tileMap[position.y][position.x] = pTheme->getTile("Beach_L");
							if ( beachOnUp )
							{
								this->tileMap[position.y][position.x] = pTheme->getTile("Beach_L_T");
							}
							else if ( beachOnDown )
							{
								this->tileMap[position.y][position.x] = pTheme->getTile("Beach_L_B");
							}
							if ( beachOnUp && beachOnDown )
							{
								this->tileMap[position.y][position.x] = pTheme->getTile("Beach_L_2");
							}
						}
						else
						{
							this->tileMap[position.y][position.x] = pTheme->getTile("Coast_L");
						}

						if ( this->getTile(UVec2(position.x-1,position.y)) == pTheme->getTile("River_H") && this->getTile(UVec2(position.x-2,position.y)) == pTheme->getTile("River_H") )
						{
							this->tileMap[position.y][position.x] = pTheme->getTile("River_See_L");
						}
					}
				}
			}
			break;
			

		case 4:
			switch(nbSeeDiagonal)
			{
				case 0:
					this->tileMap[position.y][position.x] = pTheme->getTile("Coast_X");
					break;
				case 1:
					if ( onUpLeft )
					{
						this->tileMap[position.y][position.x] = pTheme->getTile("Coast_XBR");
					}
					if ( onUpRight )
					{
						this->tileMap[position.y][position.x] = pTheme->getTile("Coast_XBL");
					}
					if ( onDownLeft )
					{
						this->tileMap[position.y][position.x] = pTheme->getTile("Coast_XTR");
					}
					if ( onDownRight )
					{
						this->tileMap[position.y][position.x] = pTheme->getTile("Coast_XTL");
					}
					break;
				case 2:
					if ( onUpLeft && onUpRight )
					{
						this->tileMap[position.y][position.x] = pTheme->getTile("Coast_XB");
					}
					if ( onUpLeft && onDownLeft )
					{
						this->tileMap[position.y][position.x] = pTheme->getTile("Coast_XR");
					}
					if ( onDownLeft && onDownRight )
					{
						this->tileMap[position.y][position.x] = pTheme->getTile("Coast_XT");
					}
					if ( onDownRight && onUpRight )
					{
						this->tileMap[position.y][position.x] = pTheme->getTile("Coast_XL");
					}
					if ( onDownRight && onUpLeft )
					{
						this->tileMap[position.y][position.x] = pTheme->getTile("Coast_XBLTR");
					}
					if ( onDownLeft && onUpRight )
					{
						this->tileMap[position.y][position.x] = pTheme->getTile("Coast_XTLBR");
					}
					break;
				case 3:
					if ( onDownRight && onUpRight && onUpLeft )
					{
						this->tileMap[position.y][position.x] = pTheme->getTile("Sea_BL");
					}
					if ( onUpRight && onUpLeft && onDownLeft )
					{
						this->tileMap[position.y][position.x] = pTheme->getTile("Sea_BR");
					}
					if ( onUpLeft && onDownLeft && onDownRight )
					{
						this->tileMap[position.y][position.x] = pTheme->getTile("Sea_TR");
					}
					if ( onDownLeft && onDownRight && onUpRight )
					{
						this->tileMap[position.y][position.x] = pTheme->getTile("Sea_TL");
					}
					break;
				case 4:
					this->tileMap[position.y][position.x] = pTheme->getTile("Sea");
					break;

				default:
					assert(0); // Not possible to go here, or we have a bug
					break;
			}
			break;

		default:
			assert(0); // Not possible to go here, or we have a bug in counting tiles around
			break;
	}
}

void Map :: checkCoherencyForRiver(const UVec2& position)
{
	unsigned char nbRiverAround = 0;
	bool isVerticalRiver = false;
	bool isHorizontalRiver = false;
	bool onLeft = false;
	bool onRight = false;
	bool onUp = false;
	bool onDown = false;
		
	if ( this->getTile(UVec2(position.x-1,position.y))->getParams()->getAs<bool>("isRiver",false) || this->getTile(UVec2(position.x-1,position.y))->getParams()->getAs<bool>("isBridge",false) )	// Left
	{
		nbRiverAround++;
		isHorizontalRiver = true;
		onLeft = true;
	}
	
	if ( this->getTile(UVec2(position.x+1,position.y))->getParams()->getAs<bool>("isRiver",false) || this->getTile(UVec2(position.x+1,position.y))->getParams()->getAs<bool>("isBridge",false) ) // Right
	{
		nbRiverAround++;
		isHorizontalRiver = true;
		onRight = true;
	}

	if ( this->getTile(UVec2(position.x,position.y-1))->getParams()->getAs<bool>("isRiver",false) || this->getTile(UVec2(position.x,position.y-1))->getParams()->getAs<bool>("isBridge",false) ) // Up
	{
		nbRiverAround++;
		isVerticalRiver = true;
		onUp = true;
	}

	if ( this->getTile(UVec2(position.x,position.y+1))->getParams()->getAs<bool>("isRiver",false) || this->getTile(UVec2(position.x,position.y+1))->getParams()->getAs<bool>("isBridge",false) ) // Down
	{
		nbRiverAround++;
		isVerticalRiver = true;
		onDown = true;
	}

	switch(nbRiverAround)
	{
		case 0:
			this->tileMap[position.y][position.x] = pTheme->getTile("River_H");	// The default one
			break;
		case 1:
			if ( isVerticalRiver )
			{
				this->tileMap[position.y][position.x] = pTheme->getTile("River_V");	// The default one
			}
			else if ( isHorizontalRiver )
			{
				this->tileMap[position.y][position.x] = pTheme->getTile("River_H");
			}

			// Test for the river to see tiles
			if ( onLeft && this->getTile(UVec2(position.x,position.y-1))->getParams()->getAs<bool>("isSea",false) && 
				this->getTile(UVec2(position.x,position.y+1))->getParams()->getAs<bool>("isSea",false) && 
				this->getTile(UVec2(position.x+1,position.y))->getParams()->getAs<bool>("isSea",false) && 
				this->getTile(UVec2(position.x+1,position.y+1))->getParams()->getAs<bool>("isSea",false) && 
				this->getTile(UVec2(position.x+1,position.y-1))->getParams()->getAs<bool>("isSea",false) )
			{
				this->tileMap[position.y][position.x] = pTheme->getTile("River_See_L");
			}

			if ( onRight && this->getTile(UVec2(position.x,position.y-1))->getParams()->getAs<bool>("isSea",false) && 
				this->getTile(UVec2(position.x,position.y+1))->getParams()->getAs<bool>("isSea",false) &&
				this->getTile(UVec2(position.x-1,position.y))->getParams()->getAs<bool>("isSea",false) && 
				this->getTile(UVec2(position.x-1,position.y+1))->getParams()->getAs<bool>("isSea",false) && 
				this->getTile(UVec2(position.x-1,position.y-1))->getParams()->getAs<bool>("isSea",false) )
			{
				this->tileMap[position.y][position.x] = pTheme->getTile("River_See_R");
			}

			if ( onDown && this->getTile(UVec2(position.x-1,position.y))->getParams()->getAs<bool>("isSea",false) && 
				this->getTile(UVec2(position.x+1,position.y))->getParams()->getAs<bool>("isSea",false) && 
				this->getTile(UVec2(position.x,position.y-1))->getParams()->getAs<bool>("isSea",false) && 
				this->getTile(UVec2(position.x+1,position.y-1))->getParams()->getAs<bool>("isSea",false) && 
				this->getTile(UVec2(position.x-1,position.y-1))->getParams()->getAs<bool>("isSea",false) )
			{
				this->tileMap[position.y][position.x] = pTheme->getTile("River_See_B");
			}

			if ( onUp && this->getTile(UVec2(position.x-1,position.y))->getParams()->getAs<bool>("isSea",false) && 
				this->getTile(UVec2(position.x+1,position.y))->getParams()->getAs<bool>("isSea",false) && 
				this->getTile(UVec2(position.x,position.y+1))->getParams()->getAs<bool>("isSea",false) && 
				this->getTile(UVec2(position.x+1,position.y+1))->getParams()->getAs<bool>("isSea",false) && 
				this->getTile(UVec2(position.x-1,position.y+1))->getParams()->getAs<bool>("isSea",false) )
			{
				this->tileMap[position.y][position.x] = pTheme->getTile("River_See_T");
			}
			break;
		case 2: // Can be a line or a corner
			// Line case
			if ( isVerticalRiver && !isHorizontalRiver )
			{
				this->tileMap[position.y][position.x] = pTheme->getTile("River_V");
			}

			if ( isHorizontalRiver && !isVerticalRiver )
			{
				this->tileMap[position.y][position.x] = pTheme->getTile("River_H");
			}

			if ( onLeft && onUp )
			{
				this->tileMap[position.y][position.x] = pTheme->getTile("River_BR");
			}

			if ( onRight && onUp )
			{
				this->tileMap[position.y][position.x] = pTheme->getTile("River_BL");
			}

			if ( onLeft && onDown )
			{
				this->tileMap[position.y][position.x] = pTheme->getTile("River_TR");
			}

			if ( onRight && onDown )
			{
				this->tileMap[position.y][position.x] = pTheme->getTile("River_TL");
			}
			break;

		case 3: // Will be a T
			if ( onLeft && onRight && onUp )
			{
				this->tileMap[position.y][position.x] = pTheme->getTile("River_T_B");
			}

			if ( onLeft && onRight && onDown )
			{
				this->tileMap[position.y][position.x] = pTheme->getTile("River_T_T");
			}

			if ( onUp && onDown && onLeft )
			{
				this->tileMap[position.y][position.x] = pTheme->getTile("River_T_R");
			}

			if ( onUp && onDown && onRight )
			{
				this->tileMap[position.y][position.x] = pTheme->getTile("River_T_L");
			}
			break;
		case 4:
			this->tileMap[position.y][position.x] = pTheme->getTile("River_X");
			break;
	}
}

bool Map :: setPlain(const UVec2& position)
{
	// The plain will be set on the actual tile, in any case
	tileMap[position.y][position.x] = pTheme->getTile("Plain");

	checkCoherencyAround(position);

	return true;
}

bool Map :: setTree(const UVec2& position)
{
	// The tree will be set on the actual tile, in any case
	tileMap[position.y][position.x] = pTheme->getTile("Tree");

	checkCoherencyAround(position);

	return true;
}

bool Map :: setMountain(const UVec2& position)
{
	// The tree will be set on the actual tile, in any case
	tileMap[position.y][position.x] = pTheme->getTile("Mountain_2");

	checkCoherencyAround(position);

	return true;
}

bool Map :: setRoad(const UVec2& position)
{
	if (this->getTile(position) == pTheme->getTile("River_H") || this->getTile(position) == pTheme->getTile("River_V") )
	{
		// We use the function setBridge, because, the function has all the logic needed (I don"t want to rewrite it ;))
		return setBridge(position);
	}

	tileMap[position.y][position.x] = pTheme->getTile("Road_H");

	checkCoherencyForRoad(position);
	checkCoherencyAround(position);

	return true;
}

bool Map :: setSea(const UVec2& position)
{
	tileMap[position.y][position.x] = pTheme->getTile("TT_Sea");

	checkCoherencyForSee(position);
	checkCoherencyAround(position);

	return true;
}

bool Map :: setReef(const UVec2& position)
{
	tileMap[position.y][position.x] = pTheme->getTile("Reef");

	//checkCoherencyForSee(position);
	//checkCoherencyAround(position);

	return true;
}

bool Map :: setBeach(const UVec2& position)
{
	tileMap[position.y][position.x] = pTheme->getTile("Beach_B");

	checkCoherencyForSee(position);
	checkCoherencyAround(position);

	return true;
}

bool Map :: setRiver(const UVec2& position)
{
	tileMap[position.y][position.x] = pTheme->getTile("River_H");

	checkCoherencyForRiver(position);
	checkCoherencyAround(position);

	return true;
}

bool Map :: setBridge(const UVec2& position)
{
	std::string tileName = this->getTile(position)->getInternalName();
	if ( tileName == "River_V" )
	{
		tileMap[position.y][position.x] = pTheme->getTile("Bridge_H");
	}
	else if ( tileName == "River_H" )
	{
		tileMap[position.y][position.x] = pTheme->getTile("Bridge_V");
	}
	else if ( tileName == "Coast_V" || tileName == "Coast_L" || tileName == "Coast_R" )
	{
		tileMap[position.y][position.x] = pTheme->getTile("Bridge_H");
	}
	else if ( tileName == "Coast_H" || tileName == "Coast_B" || tileName == "Coast_T" )
	{
		tileMap[position.y][position.x] = pTheme->getTile("Bridge_V");
	}
	else if ( tileName == "Sea" )
	{
			if ( this->getTile(UVec2(position.x-1,position.y))->getParams()->getAs<bool>("isBridge",false) || 
				this->getTile(UVec2(position.x+1,position.y))->getParams()->getAs<bool>("isBridge",false) )
			{
				tileMap[position.y][position.x] = pTheme->getTile("Bridge_H");
			}
			else if ( this->getTile(UVec2(position.x,position.y-1))->getParams()->getAs<bool>("isBridge",false) || 
				this->getTile(UVec2(position.x,position.y+1))->getParams()->getAs<bool>("isBridge",false) )
			{
				tileMap[position.y][position.x] = pTheme->getTile("Bridge_V");
			}
			else
			{
				assert(0);	// If we are here, it's because the test function is wrong
			}
	}
	else
	{
		assert(0);	// If we are here, it's because the test function is wrong
	}

	checkCoherencyAround(position);

	return true;
}

bool Map :: setHQ(const UVec2& position, const std::string& hqName)
{
	assert(hqName == "TT_Green_HQ" ||
		hqName == "TT_Red_HQ" ||
		hqName == "TT_Blue_HQ" ||
		hqName == "TT_Yellow_HQ" );

	// For each lines
	for ( unsigned int y = 0 ; y < this->height ; y++ )
	{
		// For each columns
		for ( unsigned int x = 0 ; x < this->width ; x++ )
		{
			if ( tileMap[y][x]->getName() == hqName )
			{
				tileMap[y][x] = pTheme->getTile(0);
			}
		}
	}

	tileMap[position.y][position.x] = pTheme->getTile(hqName);

	checkCoherencyAround(position);

	return true;
}

bool Map :: setBuilding(const UVec2& position, const std::string& buildingName)
{
	if ( buildingName == "TT_Green_HQ" ||
		buildingName == "TT_Red_HQ" ||
		buildingName == "TT_Blue_HQ" ||
		buildingName == "TT_Yellow_HQ" )
	{
		return setHQ(position,buildingName);
	}

	tileMap[position.y][position.x] = pTheme->getTile(buildingName);

	checkCoherencyAround(position);

	return true;
}