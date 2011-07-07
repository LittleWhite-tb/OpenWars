#ifdef EDITOR

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

#include "MapEditor.h"

#include <fstream>

#include <cassert>

#include "NEngine/SpriteLoader.h"

#include "Engine/AnimatedSprite.h"
#include "Engine/Theme.h"
#include "Engine/Params.h"

#include "Engine/Params.h"
#include "Game/Camera.h"
#include "Tile.h"
#include "Unit.h"

#include "Utils/Logger.h"

#include "globals.h"

MapEditor :: MapEditor(const Library<Theme>* const pThemes, const UVec2& size)
	:Map(pThemes)
{
	width = size.x;
	height = size.y;
	valid = true;	// By default the map is valid, but maybe just after, we will fail, so invalidate it

	this->allocateMemory(size);
	for ( unsigned int y = 0 ; y < size.y ; y++ )
	{
		for ( unsigned int x = 0 ; x < size.x ; x++ )
		{
			tileMap[y][x] = pThemes->get(themeName)->getTile(0);
		}
	}

	LDebug << "MapEditor created " << size;
}

bool MapEditor :: draw(const NE::Renderer& r, const Camera& c, const unsigned int time)
{
	UVec2 cameraPosition = c.getPosition();
	// USize2 mapOffset = Scaler::getOffset();
	IVec2 tilePos(0,0 /*mapOffset.height*/);
	bool bError = true;

	LDebug << "Map :: draw";

	this->drawTerrain(r,c,time);

	// The camera is an offset of the Map drawing
	// For each lines
	for ( unsigned int y = cameraPosition.y ; y < MAP_MIN_HEIGHT+cameraPosition.y ; y++ )
	{
		tilePos.x = 0; // mapOffset.width;
		// For each columns
		for ( unsigned int x = cameraPosition.x ; x < MAP_MIN_WIDTH+cameraPosition.x ; x++ )
		{
			// Calculation of the offset for sprite with higher size than normal Tile (e.g.: Mountains)
			unsigned int yOffset = tileMap[y][x]->getSprite()->getSize().height - TILE_DEFAULT_HEIGHT;

			// Apply offset
			tilePos.y -= yOffset;

			if ( unitMap[y][x].state != US_NO_UNIT )	// If we have a unit
			{
                bError &= unitMap[y][x].getSprite()->draw(r,tilePos,time);
			}
			tilePos.x += tileMap[y][x]->getSprite()->getSize().width;

			// Remove offset ( to not affect other sprite )
			tilePos.y += yOffset;
		}

		// To put 0 here, can be a bit dangerous
		tilePos.y += TILE_DEFAULT_HEIGHT;
	}

	return bError;
}

void MapEditor :: checkCoherencyAround(const UVec2& position)
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

void MapEditor :: checkCoherency(const UVec2& position)
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

void MapEditor :: checkCoherencyForRoad(const UVec2& position)
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
			this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Road_H");	// The default one
			break;
		case 1:
			if ( isVerticalRoad )
			{
				this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Road_V");	// The default one
			}
			else if ( isHorizontalRoad )
			{
				this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Road_H");
			}
			break;
		case 2: // Can be a line or a corner
			// Line case
			if ( isVerticalRoad && !isHorizontalRoad )
			{
				this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Road_V");
			}

			if ( isHorizontalRoad && !isVerticalRoad )
			{
				this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Road_H");
			}

			if ( onLeft && onUp )
			{
				this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Road_TL");
			}

			if ( onRight && onUp )
			{
				this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Road_TR");
			}

			if ( onLeft && onDown )
			{
				this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Road_BL");
			}

			if ( onRight && onDown )
			{
				this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Road_BR");
			}
			break;

		case 3: // Will be a T
			if ( onLeft && onRight && onUp )
			{
				this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Road_T_T");
			}

			if ( onLeft && onRight && onDown )
			{
				this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Road_T_B");
			}

			if ( onUp && onDown && onLeft )
			{
				this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Road_T_L");
			}

			if ( onUp && onDown && onRight )
			{
				this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Road_T_R");
			}
			break;
		case 4:
			this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Road_X");
			break;
	}
}

void MapEditor :: checkCoherencyForSee(const UVec2& position)
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
			this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Coast");	// The default one
			break;
		case 1:
			// Diagonals are not important here
			if ( onLeft )
			{
				if ( isBeach )
				{
					this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Beach_ER");
				}
				else
				{
					this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Coast_ER");
				}
			}
			else if ( onRight )
			{
				if ( isBeach )
				{
					this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Beach_EL");
				}
				else
				{
					this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Coast_EL");
				}
			}
			else if ( onUp )
			{
				if ( isBeach )
				{
					this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Beach_EB");
				}
				else
				{
					this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Coast_EB");
				}
			}
			else if ( onDown )
			{
				if ( isBeach )
				{
					this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Beach_ET");
				}
				else
				{
					this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Coast_ET");
				}
			}
			break;
		case 2: // Can be a line or a corner
			// Line case
			if ( isVerticalSee && !isHorizontalSee )
			{
				this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Coast_V");
			}

			if ( isHorizontalSee && !isVerticalSee )
			{
				this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Coast_H");
			}

			// Corners
			if ( onLeft && onUp )
			{
				if ( onUpLeft )
				{
					if ( isBeach )
					{
						this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Beach_BR");
						if ( beachOnUp )
						{
							this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Beach_BR_T");
						}
						else if ( beachOnLeft )
						{
							this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Beach_BR_L");
						}
						if ( beachOnUp && beachOnLeft )
						{
							this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Beach_BR_2");
						}
					}
					else
					{
						this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Coast_BR");
					}
				}
				else
				{
					this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Coast_RBR");
				}
			}

			if ( onRight && onUp )
			{
				if ( onUpRight )
				{
					if ( isBeach )
					{
						this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Beach_BL");
						if ( beachOnUp )
						{
							this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Beach_BL_T");
						}
						else if ( beachOnRight )
						{
							this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Beach_BL_R");
						}
						if ( beachOnUp && beachOnRight )
						{
							this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Beach_BL_2");
						}
					}
					else
					{
						this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Coast_BL");
					}					
				}
				else
				{
					this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Coast_RBL");
				}
			}

			if ( onLeft && onDown )
			{
				if ( onDownLeft )
				{
					if ( isBeach )
					{
						this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Beach_TR");
						if ( beachOnDown )
						{
							this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Beach_TR_B");
						}
						else if ( beachOnLeft )
						{
							this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Beach_TR_L");
						}
						if ( beachOnDown && beachOnLeft )
						{
							this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Beach_TR_2");
						}
					}
					else
					{
						this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Coast_TR");
					}
				}
				else
				{
					this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Coast_RTR");
				}
			}

			if ( onRight && onDown )
			{
				if ( onDownRight )
				{
					if ( isBeach )
					{
						this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Beach_TL");
						if ( beachOnDown )
						{
							this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Beach_TL_B");
						}
						else if ( beachOnRight )
						{
							this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Beach_TL_R");
						}
						if ( beachOnDown && beachOnRight )
						{
							this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Beach_TL_2");
						}
					}
					else
					{
						this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Coast_TL");
					}
				}
				else
				{
					this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Coast_RTL");
				}
			}

			break;

		case 3: // Can be a T, or a corner 
			if ( onLeft && onRight && onUp )
			{
				this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Coast_T_B");

				if ( nbSeeDiagonal >= 1 )
				{
					if ( onUpLeft )
					{
						this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Coast_T_BR");
					}
					
					if ( onUpRight )
					{
						this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Coast_T_BL");
					}	

					if ( onUpLeft && onUpRight )
					{
						if ( isBeach )
						{
							this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Beach_B");
							if ( beachOnLeft )
							{
								this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Beach_B_L");
							}
							else if ( beachOnRight )
							{
								this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Beach_B_R");
							}
							if ( beachOnRight && beachOnLeft )
							{
								this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Beach_B_2");
							}
						}
						else
						{
							this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Coast_B");
						}

						if ( this->getTile(UVec2(position.x,position.y+1)) == pThemes->get(themeName)->getTile("River_V") && this->getTile(UVec2(position.x,position.y+2)) == pThemes->get(themeName)->getTile("River_V") )
						{
							this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("River_See_B");
						}
					}
				}
			}

			if ( onLeft && onRight && onDown )
			{
				this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Coast_T_T");

				if ( nbSeeDiagonal >= 1 )
				{
					if ( onDownLeft )
					{
						this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Coast_T_TR");
					}
					
					if ( onDownRight )
					{
						this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Coast_T_TL");
					}	

					if ( onDownLeft && onDownRight )
					{
						if ( isBeach )
						{
							this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Beach_T");
							if ( beachOnLeft )
							{
								this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Beach_T_L");
							}
							else if ( beachOnRight )
							{
								this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Beach_T_R");
							}
							if ( beachOnRight && beachOnLeft )
							{
								this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Beach_T_2");
							}
						}
						else
						{
							this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Coast_T");
						}

						if ( this->getTile(UVec2(position.x,position.y-1)) == pThemes->get(themeName)->getTile("River_V") && this->getTile(UVec2(position.x,position.y-2)) == pThemes->get(themeName)->getTile("River_V") )
						{
							this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("River_See_T");
						}
					}
				}
			}

			if ( onUp && onDown && onLeft )
			{
				this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Coast_T_R");

				if ( nbSeeDiagonal >= 1 )
				{
					if ( onUpLeft )
					{
						this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Coast_T_RB");
					}
					
					if ( onDownLeft )
					{
						this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Coast_T_RT");
					}	

					if ( onUpLeft && onDownLeft )
					{
						if ( isBeach )
						{
							this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Beach_R");
							if ( beachOnUp )
							{
								this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Beach_R_T");
							}
							else if ( beachOnDown )
							{
								this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Beach_R_B");
							}
							if ( beachOnUp && beachOnDown )
							{
								this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Beach_R_2");
							}
						}
						else
						{
							this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Coast_R");
						}

						if ( this->getTile(UVec2(position.x+1,position.y)) == pThemes->get(themeName)->getTile("River_H") && this->getTile(UVec2(position.x+2,position.y)) == pThemes->get(themeName)->getTile("River_H") )
						{
							this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("River_See_R");
						}
					}
				}
			}

			if ( onUp && onDown && onRight )
			{
				this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Coast_T_L");

				if ( nbSeeDiagonal >= 1 )
				{
					if ( onUpRight)
					{
						this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Coast_T_LB");
					}
					
					if ( onDownRight )
					{
						this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Coast_T_LT");
					}	

					if ( onDownRight && onUpRight )
					{
						if ( isBeach )
						{
							this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Beach_L");
							if ( beachOnUp )
							{
								this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Beach_L_T");
							}
							else if ( beachOnDown )
							{
								this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Beach_L_B");
							}
							if ( beachOnUp && beachOnDown )
							{
								this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Beach_L_2");
							}
						}
						else
						{
							this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Coast_L");
						}

						if ( this->getTile(UVec2(position.x-1,position.y)) == pThemes->get(themeName)->getTile("River_H") && this->getTile(UVec2(position.x-2,position.y)) == pThemes->get(themeName)->getTile("River_H") )
						{
							this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("River_See_L");
						}
					}
				}
			}
			break;
			

		case 4:
			switch(nbSeeDiagonal)
			{
				case 0:
					this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Coast_X");
					break;
				case 1:
					if ( onUpLeft )
					{
						this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Coast_XBR");
					}
					if ( onUpRight )
					{
						this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Coast_XBL");
					}
					if ( onDownLeft )
					{
						this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Coast_XTR");
					}
					if ( onDownRight )
					{
						this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Coast_XTL");
					}
					break;
				case 2:
					if ( onUpLeft && onUpRight )
					{
						this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Coast_XB");
					}
					if ( onUpLeft && onDownLeft )
					{
						this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Coast_XR");
					}
					if ( onDownLeft && onDownRight )
					{
						this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Coast_XT");
					}
					if ( onDownRight && onUpRight )
					{
						this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Coast_XL");
					}
					if ( onDownRight && onUpLeft )
					{
						this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Coast_XBLTR");
					}
					if ( onDownLeft && onUpRight )
					{
						this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Coast_XTLBR");
					}
					break;
				case 3:
					if ( onDownRight && onUpRight && onUpLeft )
					{
						this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Sea_BL");
					}
					if ( onUpRight && onUpLeft && onDownLeft )
					{
						this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Sea_BR");
					}
					if ( onUpLeft && onDownLeft && onDownRight )
					{
						this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Sea_TR");
					}
					if ( onDownLeft && onDownRight && onUpRight )
					{
						this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Sea_TL");
					}
					break;
				case 4:
					this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Sea");
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

void MapEditor :: checkCoherencyForRiver(const UVec2& position)
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
			this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("River_H");	// The default one
			break;
		case 1:
			if ( isVerticalRiver )
			{
				this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("River_V");	// The default one
			}
			else if ( isHorizontalRiver )
			{
				this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("River_H");
			}

			// Test for the river to see tiles
			if ( onLeft && this->getTile(UVec2(position.x,position.y-1))->getParams()->getAs<bool>("isSea",false) && 
				this->getTile(UVec2(position.x,position.y+1))->getParams()->getAs<bool>("isSea",false) && 
				this->getTile(UVec2(position.x+1,position.y))->getParams()->getAs<bool>("isSea",false) && 
				this->getTile(UVec2(position.x+1,position.y+1))->getParams()->getAs<bool>("isSea",false) && 
				this->getTile(UVec2(position.x+1,position.y-1))->getParams()->getAs<bool>("isSea",false) )
			{
				this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("River_See_L");
			}

			if ( onRight && this->getTile(UVec2(position.x,position.y-1))->getParams()->getAs<bool>("isSea",false) && 
				this->getTile(UVec2(position.x,position.y+1))->getParams()->getAs<bool>("isSea",false) &&
				this->getTile(UVec2(position.x-1,position.y))->getParams()->getAs<bool>("isSea",false) && 
				this->getTile(UVec2(position.x-1,position.y+1))->getParams()->getAs<bool>("isSea",false) && 
				this->getTile(UVec2(position.x-1,position.y-1))->getParams()->getAs<bool>("isSea",false) )
			{
				this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("River_See_R");
			}

			if ( onDown && this->getTile(UVec2(position.x-1,position.y))->getParams()->getAs<bool>("isSea",false) && 
				this->getTile(UVec2(position.x+1,position.y))->getParams()->getAs<bool>("isSea",false) && 
				this->getTile(UVec2(position.x,position.y-1))->getParams()->getAs<bool>("isSea",false) && 
				this->getTile(UVec2(position.x+1,position.y-1))->getParams()->getAs<bool>("isSea",false) && 
				this->getTile(UVec2(position.x-1,position.y-1))->getParams()->getAs<bool>("isSea",false) )
			{
				this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("River_See_B");
			}

			if ( onUp && this->getTile(UVec2(position.x-1,position.y))->getParams()->getAs<bool>("isSea",false) && 
				this->getTile(UVec2(position.x+1,position.y))->getParams()->getAs<bool>("isSea",false) && 
				this->getTile(UVec2(position.x,position.y+1))->getParams()->getAs<bool>("isSea",false) && 
				this->getTile(UVec2(position.x+1,position.y+1))->getParams()->getAs<bool>("isSea",false) && 
				this->getTile(UVec2(position.x-1,position.y+1))->getParams()->getAs<bool>("isSea",false) )
			{
				this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("River_See_T");
			}
			break;
		case 2: // Can be a line or a corner
			// Line case
			if ( isVerticalRiver && !isHorizontalRiver )
			{
				this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("River_V");
			}

			if ( isHorizontalRiver && !isVerticalRiver )
			{
				this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("River_H");
			}

			if ( onLeft && onUp )
			{
				this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("River_BR");
			}

			if ( onRight && onUp )
			{
				this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("River_BL");
			}

			if ( onLeft && onDown )
			{
				this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("River_TR");
			}

			if ( onRight && onDown )
			{
				this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("River_TL");
			}
			break;

		case 3: // Will be a T
			if ( onLeft && onRight && onUp )
			{
				this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("River_T_B");
			}

			if ( onLeft && onRight && onDown )
			{
				this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("River_T_T");
			}

			if ( onUp && onDown && onLeft )
			{
				this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("River_T_R");
			}

			if ( onUp && onDown && onRight )
			{
				this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("River_T_L");
			}
			break;
		case 4:
			this->tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("River_X");
			break;
	}
}

bool MapEditor :: setPlain(const UVec2& position)
{
	// The plain will be set on the actual tile, in any case
	tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Plain");

	checkCoherencyAround(position);

	return true;
}

bool MapEditor :: setTree(const UVec2& position)
{
	// The tree will be set on the actual tile, in any case
	tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Tree");

	checkCoherencyAround(position);

	return true;
}

bool MapEditor :: setMountain(const UVec2& position)
{
	// The tree will be set on the actual tile, in any case
	tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Mountain_2");

	checkCoherencyAround(position);

	return true;
}

bool MapEditor :: setRoad(const UVec2& position)
{
	if (this->getTile(position) == pThemes->get(themeName)->getTile("River_H") || this->getTile(position) == pThemes->get(themeName)->getTile("River_V") )
	{
		// We use the function setBridge, because, the function has all the logic needed (I don"t want to rewrite it ;))
		return setBridge(position);
	}

	tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Road_H");

	checkCoherencyForRoad(position);
	checkCoherencyAround(position);

	return true;
}

bool MapEditor :: setSea(const UVec2& position)
{
	tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("TT_Sea");

	checkCoherencyForSee(position);
	checkCoherencyAround(position);

	return true;
}

bool MapEditor :: setReef(const UVec2& position)
{
	tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Reef");

	//checkCoherencyForSee(position);
	//checkCoherencyAround(position);

	return true;
}

bool MapEditor :: setBeach(const UVec2& position)
{
	tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Beach_B");

	checkCoherencyForSee(position);
	checkCoherencyAround(position);

	return true;
}

bool MapEditor :: setRiver(const UVec2& position)
{
	tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("River_H");

	checkCoherencyForRiver(position);
	checkCoherencyAround(position);

	return true;
}

bool MapEditor :: setBridge(const UVec2& position)
{
	std::string tileName = this->getTile(position)->getInternalName();
	if ( tileName == "River_V" )
	{
		tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Bridge_H");
	}
	else if ( tileName == "River_H" )
	{
		tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Bridge_V");
	}
	else if ( tileName == "Coast_V" || tileName == "Coast_L" || tileName == "Coast_R" )
	{
		tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Bridge_H");
	}
	else if ( tileName == "Coast_H" || tileName == "Coast_B" || tileName == "Coast_T" )
	{
		tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Bridge_V");
	}
	else if ( tileName == "Sea" )
	{
			if ( this->getTile(UVec2(position.x-1,position.y))->getParams()->getAs<bool>("isBridge",false) || 
				this->getTile(UVec2(position.x+1,position.y))->getParams()->getAs<bool>("isBridge",false) )
			{
				tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Bridge_H");
			}
			else if ( this->getTile(UVec2(position.x,position.y-1))->getParams()->getAs<bool>("isBridge",false) || 
				this->getTile(UVec2(position.x,position.y+1))->getParams()->getAs<bool>("isBridge",false) )
			{
				tileMap[position.y][position.x] = pThemes->get(themeName)->getTile("Bridge_V");
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

bool MapEditor :: setHQ(const UVec2& position, const std::string& hqName)
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
				tileMap[y][x] = pThemes->get(themeName)->getTile(0);
			}
		}
	}

	tileMap[position.y][position.x] = pThemes->get(themeName)->getTile(hqName);

	checkCoherencyAround(position);

	return true;
}

bool MapEditor :: setBuilding(const UVec2& position, const std::string& buildingName)
{
	if ( buildingName == "TT_Green_HQ" ||
		buildingName == "TT_Red_HQ" ||
		buildingName == "TT_Blue_HQ" ||
		buildingName == "TT_Yellow_HQ" )
	{
		return setHQ(position,buildingName);
	}

	tileMap[position.y][position.x] = pThemes->get(themeName)->getTile(buildingName);

	checkCoherencyAround(position);

	return true;
}

bool MapEditor :: setTile(const UVec2& position, const std::string& tileName)
{
	// Extra protections
	assert(position.x < this->width);
	assert(position.y < this->height);

	LDebug << "Map :: setTile " << position << " Tile: " << tileName;

	if ( this->testTile(position,pThemes->get(themeName)->getTile(tileName)) == false )
	{
		return false;
	}

	// Check if the tile below is the same // or one equivalent
	if ( tileMap[position.y][position.x]->getID() == tileMap[position.y][position.x]->getID() )
		return true;
	
	if ( pThemes->get(themeName)->getTile(tileName)->getParams()->getAs<bool>("isRoad",false) == true )
		if ( tileMap[position.y][position.x]->getParams()->getAs<bool>("isRoad",false) == true )
			return true;
	
/*
	Test a bit too difficult to not restrict user

	if ( pThemes->get(themeName)->getTile(tileName)->getParams()->getAs<bool>("isSea",false) == true )
		if ( tileMap[position.y][position.x]->getParams()->getAs<bool>("isSea",false) == true )
			return true;
	
	if ( pThemes->get(themeName)->getTile(tileName)->getParams()->getAs<bool>("isBeach",false) ==  true )
		if ( tileMap[position.y][position.x]->getParams()->getAs<bool>("isBeach",false) == true )
			return true;
*/
	if ( pThemes->get(themeName)->getTile(tileName)->getParams()->getAs<bool>("isRiver",false) == true )
		if ( tileMap[position.y][position.x]->getParams()->getAs<bool>("isRiver",false) == true )
			return true;
	
	if ( pThemes->get(themeName)->getTile(tileName)->getParams()->getAs<bool>("isBridge",false) == true )
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
	if ( pThemes->get(themeName)->getTile(tileName)->getParams()->getAs<bool>("isBuilding",false) == true )
	{
		return setBuilding(position,tileName);
	}

	assert(0);	// All cases have to be handled

	return false;
}


bool MapEditor :: setUnit(const UVec2& position, const std::string& unitName, unsigned int faction)
{
	// Extra protections
	assert(position.x < this->width);
	assert(position.y < this->height);

	LDebug << "Map :: setUnit" << position << " Unit: " << unitName;
/*
	if ( this->Map::testUnit(position,unitName) == false )
	{
		return false;
	}
*/
	unitMap[position.y][position.x] = pThemes->get(themeName)->getUnit(unitName,faction);

	return true;
}

/*
bool MapEditor :: testTile(const UVec2& position, const TileType tileType)const
{
	switch ( tileType )
	{
	case TT_Plain:
		return true;
		break;
	case TT_Tree:
		return true;
		break;
	case TT_Mountain_1:
	case TT_Mountain_2:
		return true;
		break;
	case TT_Road_H:
		return true;
		break;
	case TT_Sea:
		return true;
		break;
	case TT_Reef:
		if ( this->getTileType(position) == TT_Sea )
		{
			return true;
		}
		else
		{
			return false;
		}
	case TT_Beach_T:
		switch ( this->getTileType(position) )
		{
			case TT_Coast_B:
			case TT_Coast_T:
			case TT_Coast_R:
			case TT_Coast_L:
			case TT_Coast_ER:
			case TT_Coast_EL:
			case TT_Coast_EB:
			case TT_Coast_ET:
			case TT_Coast_BL:
			case TT_Coast_BR:
			case TT_Coast_TR:
			case TT_Coast_TL:
				return true;
				break;
			default:
				return false;
				break;
		}
		break;
	case TT_River_H:
		{
			// Check if it's a see tile
			if ( this->getTile(position).isSea )
			{
				return false;
			}

			// Check Top Left corner
			if ( this->getTile(UVec2(position.x-1,position.y)).isRiver && // Left
				 this->getTile(UVec2(position.x,position.y-1)).isRiver && // Top
				 this->getTile(UVec2(position.x-1,position.y-1)).isRiver ) // TopLeft
				 return false;

			// Check Top Right corner
			if ( this->getTile(UVec2(position.x+1,position.y)).isRiver && // Right
				 this->getTile(UVec2(position.x,position.y-1)).isRiver && // Top
				 this->getTile(UVec2(position.x+1,position.y-1)).isRiver ) // TopRight
				 return false;

			// Check Bottom Left corner
			if ( this->getTile(UVec2(position.x-1,position.y)).isRiver && // Left
				 this->getTile(UVec2(position.x,position.y+1)).isRiver && // Bottom
				 this->getTile(UVec2(position.x-1,position.y+1)).isRiver ) // BottomLeft
				 return false;

			// Check Bottom Right corner
			if ( this->getTile(UVec2(position.x+1,position.y)).isRiver && // Right
				 this->getTile(UVec2(position.x,position.y+1)).isRiver && // Bottom
				 this->getTile(UVec2(position.x+1,position.y+1)).isRiver ) // BottomRight
				 return false;
		}
		return true;
		break;
	case TT_Bridge_H:
		switch ( this->getTileType(position) )
		{
		case TT_River_H:
		case TT_River_V:
		case TT_Coast_H:
		case TT_Coast_V:
		case TT_Coast_T:
		case TT_Coast_R:
		case TT_Coast_B:
		case TT_Coast_L:
			return true;
			break;
		case TT_Sea:
			if ( this->getTile(UVec2(position.x-1,position.y)).isBridge ||	// Left
				 this->getTile(UVec2(position.x+1,position.y)).isBridge ||	// Right
				 this->getTile(UVec2(position.x,position.y-1)).isBridge ||	// Top
				 this->getTile(UVec2(position.x,position.y+1)).isBridge )	// Bottom
			{
				 return true;
			}
			return false;
			break;
		default:
			return false;
			break;
		}
	break;
	// Remove warnings
	default:
		break;
	}

	// For buildings (can be everywhere)
	if ( tilesSet.find(tileType)->second.isBuilding )
	{
		return true;
	}

	assert(0);	// All cases have to be handled

	return true;
}
*/
bool MapEditor :: save(const std::string& fileName)
{
	std::ofstream file;

	LDebug << "Map :: save -> '" << fileName.c_str() << "'";

	file.open(fileName.c_str(),std::ios::out);
    if ( file.is_open() == false )
    {
		LWarning << "Failed to open: '" << fileName.c_str() << "'";
		return false;
	}

	// Adding some comments for all curious opening the map with text editor
	file << "# Map created with the OpenAWars Editor" << std::endl;
	file << "# DO NOT EDIT !!!" << std::endl;

	// Now we can start to save the data

	// Name of the theme
	file << pThemes->get(themeName)->getName() << std::endl;

	// The size 'width height'
	file << this->width << " " << this->height << std::endl;

	// The tiles data
	file << "# Tiles" << std::endl;
	// For each lines
	for ( unsigned int y = 0 ; y < this->height ; y++ )
	{
		// For each columns
		for ( unsigned int x = 0 ; x < this->width ; x++ )
		{
			if ( x!=0 )
			{
				file << " ";
			}
			file << tileMap[y][x]->getID();
		}

		file << std::endl;
	}

	// The units data
	file << "# Units" << std::endl;
	// For each lines
	for ( unsigned int y = 0 ; y < this->height ; y++ )
	{
		// For each columns
		for ( unsigned int x = 0 ; x < this->width ; x++ )
		{
			if ( x!=0 )
			{
				file << " ";
			}
			if ( unitMap[y][x].state != US_NO_UNIT )
			{
				file << unitMap[y][x].getID();
			}
			else
			{
				file << -1;
			}
		}

		file << std::endl;
	}

	file.close();

	return true;
}

#endif
