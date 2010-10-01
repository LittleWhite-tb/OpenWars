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

#include "MapEditor.h"

#include <fstream>

#include <cassert>

#include "../Engine/Sprite.h"
#include "Tile.h"

#include "../Utils/Logger.h"

#include "../globals.h"

MapEditor :: MapEditor(SpriteManager& sm, const UVec2& size)
	:Map()
{
	width = size.x;
	height = size.y;
	valid = true;	// By default the map is valid, but maybe just after, we will fail, so invalidate it
	m_theme = "classic"; // By default the theme is the classical one

	this->loadGraphics(sm,m_theme);

	map = new Tile*[this->height];
	if ( map == NULL )
	{
		LError << "Error to allocate memory for the map! (at height)";
		valid = false;
	}
	else
	{
		for ( unsigned int y = 0 ; y < this->height ; y++ )
		{
			map[y] = new Tile[this->width];
			if ( map[y] == NULL )
			{
				LError << "Error to allocate memory for the map! (at width (" << y << "))";
				valid = false;
			}
		}
	}

	for ( unsigned int y = 0 ; y < this->height ; y++ )
	{
		for ( unsigned int x = 0 ; x < this->width ; x++ )
		{
			map[y][x] = TileFactory(TT_Plain);;
		}
	}

	LDebug << "MapEditor created " << size;
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
}

void MapEditor :: checkCoherency(const UVec2& position)
{
	// We check the type
	if ( this->getTile(position).tileType != TT_Invalid )
	{
		if ( this->getTile(position).isRoad )	// For road, we have to count the number of road.
		{
			checkCoherencyForRoad(position);
		}
		
		if ( this->getTile(position).isSea )
		{
			checkCoherencyForSee(position);
		}
		
		if ( this->getTile(position).isRiver )
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
		
	if ( this->getTile(UVec2(position.x-1,position.y)).isRoad || this->getTile(UVec2(position.x-1,position.y)).isBridge || parseIsHQ(this->getTile(UVec2(position.x-1,position.y)).tileType) )	// Left
	{
		nbRoadAround++;
		isHorizontalRoad = true;
		onLeft = true;
	}
	
	if ( this->getTile(UVec2(position.x+1,position.y)).isRoad || this->getTile(UVec2(position.x+1,position.y)).isBridge || parseIsHQ(this->getTile(UVec2(position.x+1,position.y)).tileType) ) // Right
	{
		nbRoadAround++;
		isHorizontalRoad = true;
		onRight = true;
	}

	if ( this->getTile(UVec2(position.x,position.y-1)).isRoad || this->getTile(UVec2(position.x,position.y-1)).isBridge || parseIsHQ(this->getTile(UVec2(position.x,position.y-1)).tileType) ) // Up
	{
		nbRoadAround++;
		isVerticalRoad = true;
		onUp = true;
	}

	if ( this->getTile(UVec2(position.x,position.y+1)).isRoad || this->getTile(UVec2(position.x,position.y+1)).isBridge || parseIsHQ(this->getTile(UVec2(position.x,position.y+1)).tileType) ) // Down
	{
		nbRoadAround++;
		isVerticalRoad = true;
		onDown = true;
	}

	switch(nbRoadAround)
	{
		case 0:
			this->map[position.y][position.x] = TileFactory(TT_Road_H);	// The default one
			break;
		case 1:
			if ( isVerticalRoad )
			{
				this->map[position.y][position.x] = TileFactory(TT_Road_V);	// The default one
			}
			else if ( isHorizontalRoad )
			{
				this->map[position.y][position.x] = TileFactory(TT_Road_H);
			}
			break;
		case 2: // Can be a line or a corner
			// Line case
			if ( isVerticalRoad && !isHorizontalRoad )
			{
				this->map[position.y][position.x] = TileFactory(TT_Road_V);
			}

			if ( isHorizontalRoad && !isVerticalRoad )
			{
				this->map[position.y][position.x] = TileFactory(TT_Road_H);
			}

			if ( onLeft && onUp )
			{
				this->map[position.y][position.x] = TileFactory(TT_Road_TL);
			}

			if ( onRight && onUp )
			{
				this->map[position.y][position.x] = TileFactory(TT_Road_TR);
			}

			if ( onLeft && onDown )
			{
				this->map[position.y][position.x] = TileFactory(TT_Road_BL);
			}

			if ( onRight && onDown )
			{
				this->map[position.y][position.x] = TileFactory(TT_Road_BR);
			}
			break;

		case 3: // Will be a T
			if ( onLeft && onRight && onUp )
			{
				this->map[position.y][position.x] = TileFactory(TT_Road_T_T);
			}

			if ( onLeft && onRight && onDown )
			{
				this->map[position.y][position.x] = TileFactory(TT_Road_T_B);
			}

			if ( onUp && onDown && onLeft )
			{
				this->map[position.y][position.x] = TileFactory(TT_Road_T_L);
			}

			if ( onUp && onDown && onRight )
			{
				this->map[position.y][position.x] = TileFactory(TT_Road_T_R);
			}
			break;
		case 4:
			this->map[position.y][position.x] = TileFactory(TT_Road_X);
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
	bool isBeach = this->getTile(position).isBeach;
	bool beachOnLeft = false;
	bool beachOnRight = false;
	bool beachOnDown = false;
	bool beachOnUp = false;
	unsigned char nbSeeDiagonal = 0;
		
	// Check the 8 tiles around and set the flags
	if ( this->getTile(UVec2(position.x-1,position.y)).isSea || this->getTile(UVec2(position.x-1,position.y)).isBridge )	// Left
	{
		nbSeeAround++;
		isHorizontalSee = true;
		onLeft = true;

		if ( this->getTile(UVec2(position.x-1,position.y)).isBeach )
		{
			beachOnLeft = true;
		}
	}
	
	if ( this->getTile(UVec2(position.x+1,position.y)).isSea || this->getTile(UVec2(position.x+1,position.y)).isBridge ) // Right
	{
		nbSeeAround++;
		isHorizontalSee = true;
		onRight = true;

		if ( this->getTile(UVec2(position.x+1,position.y)).isBeach )
		{
			beachOnRight = true;
		}
	}

	if ( this->getTile(UVec2(position.x,position.y-1)).isSea || this->getTile(UVec2(position.x,position.y-1)).isBridge ) // Up
	{
		nbSeeAround++;
		isVerticalSee = true;
		onUp = true;

		if ( this->getTile(UVec2(position.x,position.y-1)).isBeach )
		{
			beachOnUp = true;
		}
	}

	if ( this->getTile(UVec2(position.x,position.y+1)).isSea || this->getTile(UVec2(position.x,position.y+1)).isBridge ) // Down
	{
		nbSeeAround++;
		isVerticalSee = true;
		onDown = true;

		if ( this->getTile(UVec2(position.x,position.y+1)).isBeach )
		{
			beachOnDown = true;
		}
	}

	if ( this->getTile(UVec2(position.x-1,position.y-1)).isSea || this->getTile(UVec2(position.x-1,position.y-1)).isBridge ) // Up Left
	{
		// nbSeeAround++;
		nbSeeDiagonal++;
		onUpLeft = true;
	}

	if ( this->getTile(UVec2(position.x+1,position.y-1)).isSea || this->getTile(UVec2(position.x+1,position.y-1)).isBridge ) // Up Right
	{
		// nbSeeAround++;
		nbSeeDiagonal++;
		onUpRight = true;
	}

	if ( this->getTile(UVec2(position.x-1,position.y+1)).isSea || this->getTile(UVec2(position.x-1,position.y+1)).isBridge ) // Down Left
	{
		// nbSeeAround++;
		nbSeeDiagonal++;
		onDownLeft = true;
	}

	if ( this->getTile(UVec2(position.x+1,position.y+1)).isSea || this->getTile(UVec2(position.x+1,position.y+1)).isBridge ) // Down Right
	{
		// nbSeeAround++;
		nbSeeDiagonal++;
		onDownRight = true;
	}


	switch(nbSeeAround)
	{
		case 0:
			// Diagonals are not important here
			this->map[position.y][position.x] = TileFactory(TT_Coast);	// The default one
			break;
		case 1:
			// Diagonals are not important here
			if ( onLeft )
			{
				if ( isBeach )
				{
					this->map[position.y][position.x] = TileFactory(TT_Beach_ER);
				}
				else
				{
					this->map[position.y][position.x] = TileFactory(TT_Coast_ER);
				}
			}
			else if ( onRight )
			{
				if ( isBeach )
				{
					this->map[position.y][position.x] = TileFactory(TT_Beach_EL);
				}
				else
				{
					this->map[position.y][position.x] = TileFactory(TT_Coast_EL);
				}
			}
			else if ( onUp )
			{
				if ( isBeach )
				{
					this->map[position.y][position.x] = TileFactory(TT_Beach_EB);
				}
				else
				{
					this->map[position.y][position.x] = TileFactory(TT_Coast_EB);
				}
			}
			else if ( onDown )
			{
				if ( isBeach )
				{
					this->map[position.y][position.x] = TileFactory(TT_Beach_ET);
				}
				else
				{
					this->map[position.y][position.x] = TileFactory(TT_Coast_ET);
				}
			}
			break;
		case 2: // Can be a line or a corner
			// Line case
			if ( isVerticalSee && !isHorizontalSee )
			{
				this->map[position.y][position.x] = TileFactory(TT_Coast_V);
			}

			if ( isHorizontalSee && !isVerticalSee )
			{
				this->map[position.y][position.x] = TileFactory(TT_Coast_H);
			}

			// Corners
			if ( onLeft && onUp )
			{
				if ( onUpLeft )
				{
					if ( isBeach )
					{
						this->map[position.y][position.x] = TileFactory(TT_Beach_BR);
						if ( beachOnUp )
						{
							this->map[position.y][position.x] = TileFactory(TT_Beach_BR_T);
						}
						else if ( beachOnLeft )
						{
							this->map[position.y][position.x] = TileFactory(TT_Beach_BR_L);
						}
						if ( beachOnUp && beachOnLeft )
						{
							this->map[position.y][position.x] = TileFactory(TT_Beach_BR_2);
						}
					}
					else
					{
						this->map[position.y][position.x] = TileFactory(TT_Coast_BR);
					}
				}
				else
				{
					this->map[position.y][position.x] = TileFactory(TT_Coast_RBR);
				}
			}

			if ( onRight && onUp )
			{
				if ( onUpRight )
				{
					if ( isBeach )
					{
						this->map[position.y][position.x] = TileFactory(TT_Beach_BL);
						if ( beachOnUp )
						{
							this->map[position.y][position.x] = TileFactory(TT_Beach_BL_T);
						}
						else if ( beachOnRight )
						{
							this->map[position.y][position.x] = TileFactory(TT_Beach_BL_R);
						}
						if ( beachOnUp && beachOnRight )
						{
							this->map[position.y][position.x] = TileFactory(TT_Beach_BL_2);
						}
					}
					else
					{
						this->map[position.y][position.x] = TileFactory(TT_Coast_BL);
					}					
				}
				else
				{
					this->map[position.y][position.x] = TileFactory(TT_Coast_RBL);
				}
			}

			if ( onLeft && onDown )
			{
				if ( onDownLeft )
				{
					if ( isBeach )
					{
						this->map[position.y][position.x] = TileFactory(TT_Beach_TR);
						if ( beachOnDown )
						{
							this->map[position.y][position.x] = TileFactory(TT_Beach_TR_B);
						}
						else if ( beachOnLeft )
						{
							this->map[position.y][position.x] = TileFactory(TT_Beach_TR_L);
						}
						if ( beachOnDown && beachOnLeft )
						{
							this->map[position.y][position.x] = TileFactory(TT_Beach_TR_2);
						}
					}
					else
					{
						this->map[position.y][position.x] = TileFactory(TT_Coast_TR);
					}
				}
				else
				{
					this->map[position.y][position.x] = TileFactory(TT_Coast_RTR);
				}
			}

			if ( onRight && onDown )
			{
				if ( onDownRight )
				{
					if ( isBeach )
					{
						this->map[position.y][position.x] = TileFactory(TT_Beach_TL);
						if ( beachOnDown )
						{
							this->map[position.y][position.x] = TileFactory(TT_Beach_TL_B);
						}
						else if ( beachOnRight )
						{
							this->map[position.y][position.x] = TileFactory(TT_Beach_TL_R);
						}
						if ( beachOnDown && beachOnRight )
						{
							this->map[position.y][position.x] = TileFactory(TT_Beach_TL_2);
						}
					}
					else
					{
						this->map[position.y][position.x] = TileFactory(TT_Coast_TL);
					}
				}
				else
				{
					this->map[position.y][position.x] = TileFactory(TT_Coast_RTL);
				}
			}

			break;

		case 3: // Can be a T, or a corner 
			if ( onLeft && onRight && onUp )
			{
				this->map[position.y][position.x] = TileFactory(TT_Coast_T_B);

				if ( nbSeeDiagonal >= 1 )
				{
					if ( onUpLeft )
					{
						this->map[position.y][position.x] = TileFactory(TT_Coast_T_BR);
					}
					
					if ( onUpRight )
					{
						this->map[position.y][position.x] = TileFactory(TT_Coast_T_BL);
					}	

					if ( onUpLeft && onUpRight )
					{
						if ( isBeach )
						{
							this->map[position.y][position.x] = TileFactory(TT_Beach_B);
							if ( beachOnLeft )
							{
								this->map[position.y][position.x] = TileFactory(TT_Beach_B_L);
							}
							else if ( beachOnRight )
							{
								this->map[position.y][position.x] = TileFactory(TT_Beach_B_R);
							}
							if ( beachOnRight && beachOnLeft )
							{
								this->map[position.y][position.x] = TileFactory(TT_Beach_B_2);
							}
						}
						else
						{
							this->map[position.y][position.x] = TileFactory(TT_Coast_B);
						}

						if ( this->getTile(UVec2(position.x,position.y+1)).tileType == TT_River_V && this->getTile(UVec2(position.x,position.y+2)).tileType == TT_River_V )
						{
							this->map[position.y][position.x] = TileFactory(TT_River_See_B);
						}
					}
				}
			}

			if ( onLeft && onRight && onDown )
			{
				this->map[position.y][position.x] = TileFactory(TT_Coast_T_T);

				if ( nbSeeDiagonal >= 1 )
				{
					if ( onDownLeft )
					{
						this->map[position.y][position.x] = TileFactory(TT_Coast_T_TR);
					}
					
					if ( onDownRight )
					{
						this->map[position.y][position.x] = TileFactory(TT_Coast_T_TL);
					}	

					if ( onDownLeft && onDownRight )
					{
						if ( isBeach )
						{
							this->map[position.y][position.x] = TileFactory(TT_Beach_T);
							if ( beachOnLeft )
							{
								this->map[position.y][position.x] = TileFactory(TT_Beach_T_L);
							}
							else if ( beachOnRight )
							{
								this->map[position.y][position.x] = TileFactory(TT_Beach_T_R);
							}
							if ( beachOnRight && beachOnLeft )
							{
								this->map[position.y][position.x] = TileFactory(TT_Beach_T_2);
							}
						}
						else
						{
							this->map[position.y][position.x] = TileFactory(TT_Coast_T);
						}

						if ( this->getTile(UVec2(position.x,position.y-1)).tileType == TT_River_V && this->getTile(UVec2(position.x,position.y-2)).tileType == TT_River_V )
						{
							this->map[position.y][position.x] = TileFactory(TT_River_See_T);
						}
					}
				}
			}

			if ( onUp && onDown && onLeft )
			{
				this->map[position.y][position.x] = TileFactory(TT_Coast_T_R);

				if ( nbSeeDiagonal >= 1 )
				{
					if ( onUpLeft )
					{
						this->map[position.y][position.x] = TileFactory(TT_Coast_T_RB);
					}
					
					if ( onDownLeft )
					{
						this->map[position.y][position.x] = TileFactory(TT_Coast_T_RT);
					}	

					if ( onUpLeft && onDownLeft )
					{
						if ( isBeach )
						{
							this->map[position.y][position.x] = TileFactory(TT_Beach_R);
							if ( beachOnUp )
							{
								this->map[position.y][position.x] = TileFactory(TT_Beach_R_T);
							}
							else if ( beachOnDown )
							{
								this->map[position.y][position.x] = TileFactory(TT_Beach_R_B);
							}
							if ( beachOnUp && beachOnDown )
							{
								this->map[position.y][position.x] = TileFactory(TT_Beach_R_2);
							}
						}
						else
						{
							this->map[position.y][position.x] = TileFactory(TT_Coast_R);
						}

						if ( this->getTile(UVec2(position.x+1,position.y)).tileType == TT_River_H && this->getTile(UVec2(position.x+2,position.y)).tileType == TT_River_H )
						{
							this->map[position.y][position.x] = TileFactory(TT_River_See_R);
						}
					}
				}
			}

			if ( onUp && onDown && onRight )
			{
				this->map[position.y][position.x] = TileFactory(TT_Coast_T_L);

				if ( nbSeeDiagonal >= 1 )
				{
					if ( onUpRight)
					{
						this->map[position.y][position.x] = TileFactory(TT_Coast_T_LB);
					}
					
					if ( onDownRight )
					{
						this->map[position.y][position.x] = TileFactory(TT_Coast_T_LT);
					}	

					if ( onDownRight && onUpRight )
					{
						if ( isBeach )
						{
							this->map[position.y][position.x] = TileFactory(TT_Beach_L);
							if ( beachOnUp )
							{
								this->map[position.y][position.x] = TileFactory(TT_Beach_L_T);
							}
							else if ( beachOnDown )
							{
								this->map[position.y][position.x] = TileFactory(TT_Beach_L_B);
							}
							if ( beachOnUp && beachOnDown )
							{
								this->map[position.y][position.x] = TileFactory(TT_Beach_L_2);
							}
						}
						else
						{
							this->map[position.y][position.x] = TileFactory(TT_Coast_L);
						}

						if ( this->getTile(UVec2(position.x-1,position.y)).tileType == TT_River_H && this->getTile(UVec2(position.x-2,position.y)).tileType == TT_River_H )
						{
							this->map[position.y][position.x] = TileFactory(TT_River_See_L);
						}
					}
				}
			}
			break;
			

		case 4:
			switch(nbSeeDiagonal)
			{
				case 0:
					this->map[position.y][position.x] = TileFactory(TT_Coast_X);
					break;
				case 1:
					if ( onUpLeft )
					{
						this->map[position.y][position.x] = TileFactory(TT_Coast_XBR);
					}
					if ( onUpRight )
					{
						this->map[position.y][position.x] = TileFactory(TT_Coast_XBL);
					}
					if ( onDownLeft )
					{
						this->map[position.y][position.x] = TileFactory(TT_Coast_XTR);
					}
					if ( onDownRight )
					{
						this->map[position.y][position.x] = TileFactory(TT_Coast_XTL);
					}
					break;
				case 2:
					if ( onUpLeft && onUpRight )
					{
						this->map[position.y][position.x] = TileFactory(TT_Coast_XB);
					}
					if ( onUpLeft && onDownLeft )
					{
						this->map[position.y][position.x] = TileFactory(TT_Coast_XR);
					}
					if ( onDownLeft && onDownRight )
					{
						this->map[position.y][position.x] = TileFactory(TT_Coast_XT);
					}
					if ( onDownRight && onUpRight )
					{
						this->map[position.y][position.x] = TileFactory(TT_Coast_XL);
					}
					if ( onDownRight && onUpLeft )
					{
						this->map[position.y][position.x] = TileFactory(TT_Coast_XBLTR);
					}
					if ( onDownLeft && onUpRight )
					{
						this->map[position.y][position.x] = TileFactory(TT_Coast_XTLBR);
					}
					break;
				case 3:
					if ( onDownRight && onUpRight && onUpLeft )
					{
						this->map[position.y][position.x] = TileFactory(TT_Sea_BL);
					}
					if ( onUpRight && onUpLeft && onDownLeft )
					{
						this->map[position.y][position.x] = TileFactory(TT_Sea_BR);
					}
					if ( onUpLeft && onDownLeft && onDownRight )
					{
						this->map[position.y][position.x] = TileFactory(TT_Sea_TR);
					}
					if ( onDownLeft && onDownRight && onUpRight )
					{
						this->map[position.y][position.x] = TileFactory(TT_Sea_TL);
					}
					break;
				case 4:
					this->map[position.y][position.x] = TileFactory(TT_Sea);
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
		
	if ( this->getTile(UVec2(position.x-1,position.y)).isRiver || this->getTile(UVec2(position.x-1,position.y)).isBridge )	// Left
	{
		nbRiverAround++;
		isHorizontalRiver = true;
		onLeft = true;
	}
	
	if ( this->getTile(UVec2(position.x+1,position.y)).isRiver || this->getTile(UVec2(position.x+1,position.y)).isBridge ) // Right
	{
		nbRiverAround++;
		isHorizontalRiver = true;
		onRight = true;
	}

	if ( this->getTile(UVec2(position.x,position.y-1)).isRiver || this->getTile(UVec2(position.x,position.y-1)).isBridge ) // Up
	{
		nbRiverAround++;
		isVerticalRiver = true;
		onUp = true;
	}

	if ( this->getTile(UVec2(position.x,position.y+1)).isRiver || this->getTile(UVec2(position.x,position.y+1)).isBridge ) // Down
	{
		nbRiverAround++;
		isVerticalRiver = true;
		onDown = true;
	}

	switch(nbRiverAround)
	{
		case 0:
			this->map[position.y][position.x] = TileFactory(TT_River_H);	// The default one
			break;
		case 1:
			if ( isVerticalRiver )
			{
				this->map[position.y][position.x] = TileFactory(TT_River_V);	// The default one
			}
			else if ( isHorizontalRiver )
			{
				this->map[position.y][position.x] = TileFactory(TT_River_H);
			}

			// Test for the river to see tiles
			if ( onLeft && this->getTile(UVec2(position.x,position.y-1)).isSea && this->getTile(UVec2(position.x,position.y+1)).isSea && this->getTile(UVec2(position.x+1,position.y)).isSea && this->getTile(UVec2(position.x+1,position.y+1)).isSea && this->getTile(UVec2(position.x+1,position.y-1)).isSea )
			{
				this->map[position.y][position.x] = TileFactory(TT_River_See_L);
			}

			if ( onRight && this->getTile(UVec2(position.x,position.y-1)).isSea && this->getTile(UVec2(position.x,position.y+1)).isSea && this->getTile(UVec2(position.x-1,position.y)).isSea && this->getTile(UVec2(position.x-1,position.y+1)).isSea && this->getTile(UVec2(position.x-1,position.y-1)).isSea )
			{
				this->map[position.y][position.x] = TileFactory(TT_River_See_R);
			}

			if ( onDown && this->getTile(UVec2(position.x-1,position.y)).isSea && this->getTile(UVec2(position.x+1,position.y)).isSea && this->getTile(UVec2(position.x,position.y-1)).isSea && this->getTile(UVec2(position.x+1,position.y-1)).isSea && this->getTile(UVec2(position.x-1,position.y-1)).isSea )
			{
				this->map[position.y][position.x] = TileFactory(TT_River_See_B);
			}

			if ( onUp && this->getTile(UVec2(position.x-1,position.y)).isSea && this->getTile(UVec2(position.x+1,position.y)).isSea && this->getTile(UVec2(position.x,position.y+1)).isSea && this->getTile(UVec2(position.x+1,position.y+1)).isSea && this->getTile(UVec2(position.x-1,position.y+1)).isSea )
			{
				this->map[position.y][position.x] = TileFactory(TT_River_See_T);
			}
			break;
		case 2: // Can be a line or a corner
			// Line case
			if ( isVerticalRiver && !isHorizontalRiver )
			{
				this->map[position.y][position.x] = TileFactory(TT_River_V);
			}

			if ( isHorizontalRiver && !isVerticalRiver )
			{
				this->map[position.y][position.x] = TileFactory(TT_River_H);
			}

			if ( onLeft && onUp )
			{
				this->map[position.y][position.x] = TileFactory(TT_River_BR);
			}

			if ( onRight && onUp )
			{
				this->map[position.y][position.x] = TileFactory(TT_River_BL);
			}

			if ( onLeft && onDown )
			{
				this->map[position.y][position.x] = TileFactory(TT_River_TR);
			}

			if ( onRight && onDown )
			{
				this->map[position.y][position.x] = TileFactory(TT_River_TL);
			}
			break;

		case 3: // Will be a T
			if ( onLeft && onRight && onUp )
			{
				this->map[position.y][position.x] = TileFactory(TT_River_T_B);
			}

			if ( onLeft && onRight && onDown )
			{
				this->map[position.y][position.x] = TileFactory(TT_River_T_T);
			}

			if ( onUp && onDown && onLeft )
			{
				this->map[position.y][position.x] = TileFactory(TT_River_T_R);
			}

			if ( onUp && onDown && onRight )
			{
				this->map[position.y][position.x] = TileFactory(TT_River_T_L);
			}
			break;
		case 4:
			this->map[position.y][position.x] = TileFactory(TT_River_X);
			break;
	}
}

bool MapEditor :: setPlain(const UVec2& position)
{
	// The plain will be set on the actual tile, in any case
	map[position.y][position.x] = TileFactory(TT_Plain);

	checkCoherencyAround(position);

	return true;
}

bool MapEditor :: setTree(const UVec2& position)
{
	// The tree will be set on the actual tile, in any case
	map[position.y][position.x] = TileFactory(TT_Tree);

	checkCoherencyAround(position);

	return true;
}

bool MapEditor :: setMountain(const UVec2& position)
{
	// The tree will be set on the actual tile, in any case
	map[position.y][position.x] = TileFactory(TT_Mountain_1);

	checkCoherencyAround(position);

	return true;
}

bool MapEditor :: setRoad(const UVec2& position)
{
	if (this->getTile(position).tileType == TT_River_H || this->getTile(position).tileType == TT_River_V)
	{
		// We use the function setBridge, because, the function has all the logic needed (I don"t want to rewrite it ;))
		return setBridge(position);
	}

	map[position.y][position.x] = TileFactory(TT_Road_H);

	checkCoherencyForRoad(position);
	checkCoherencyAround(position);

	return true;
}

bool MapEditor :: setSee(const UVec2& position)
{
	map[position.y][position.x] = TileFactory(TT_Sea);

	checkCoherencyForSee(position);
	checkCoherencyAround(position);

	return true;
}

bool MapEditor :: setReef(const UVec2& position)
{
	map[position.y][position.x] = TileFactory(TT_Reef);

	//checkCoherencyForSee(position);
	//checkCoherencyAround(position);

	return true;
}

bool MapEditor :: setBeach(const UVec2& position)
{
	map[position.y][position.x] = TileFactory(TT_Beach_B);

	checkCoherencyForSee(position);
	checkCoherencyAround(position);

	return true;
}

bool MapEditor :: setRiver(const UVec2& position)
{
	map[position.y][position.x] = TileFactory(TT_River_H);

	checkCoherencyForRiver(position);
	checkCoherencyAround(position);

	return true;
}

bool MapEditor :: setBridge(const UVec2& position)
{
	switch(this->getTile(position).tileType)
	{
		// Rivers
		case TT_River_V:
			map[position.y][position.x] = TileFactory(TT_Bridge_H);
			break;
		case TT_River_H:
			map[position.y][position.x] = TileFactory(TT_Bridge_V);
			break;
		// Sees
		case TT_Coast_V:
		case TT_Coast_L:
		case TT_Coast_R:
			map[position.y][position.x] = TileFactory(TT_Bridge_H);
			break;
		case TT_Coast_H:
		case TT_Coast_B:
		case TT_Coast_T:
			map[position.y][position.x] = TileFactory(TT_Bridge_V);
			break;
		case TT_Sea:
			if ( this->getTile(UVec2(position.x-1,position.y)).isBridge || this->getTile(UVec2(position.x+1,position.y)).isBridge )
			{
				map[position.y][position.x] = TileFactory(TT_Bridge_H);
			}
			else if ( this->getTile(UVec2(position.x,position.y-1)).isBridge || this->getTile(UVec2(position.x,position.y+1)).isBridge )
			{
				map[position.y][position.x] = TileFactory(TT_Bridge_V);
			}
			else
			{
				assert(0);	// If we are here, it's because the test function is wrong
			}
			break;
		default:
			assert(0);	// If we are here, it's because the test function is wrong
			break;
	}

	checkCoherencyAround(position);

	return true;
}

bool MapEditor :: setHQ(const UVec2& position, const TileType type)
{
	assert(type == TT_Green_HQ ||
		type == TT_Red_HQ ||
		type == TT_Blue_HQ ||
		type == TT_Yellow_HQ );

	// For each lines
	for ( unsigned int y = 0 ; y < this->height ; y++ )
	{
		// For each columns
		for ( unsigned int x = 0 ; x < this->width ; x++ )
		{
			if ( map[y][x].tileType == type )
			{
				map[y][x] = TileFactory(TT_Plain);
			}
		}
	}

	map[position.y][position.x] = TileFactory(type);

	checkCoherencyAround(position);

	return true;
}

bool MapEditor :: setBuilding(const UVec2& position, const TileType type)
{
	if ( type == TT_Green_HQ ||
		type == TT_Red_HQ ||
		type == TT_Blue_HQ ||
		type == TT_Yellow_HQ )
	{
		return setHQ(position,type);
	}

	map[position.y][position.x] = TileFactory(type);

	checkCoherencyAround(position);

	return true;
}

bool MapEditor :: setTile(const UVec2& position, const TileType tileType)
{
	// Extra protections
	assert(position.x < this->width);
	assert(position.y < this->height);

	LDebug << "Map :: setTile " << position << " Tile: " << tileType;

	if ( this->testTile(position,tileType) == false )
	{
		return false;
	}

	// Check if the tile below is the same // or one equivalent
	Tile tmpT = this->getTile(position);
	if ( tileType == tmpT.tileType )
		return true;
	
	if ( parseIsRoad(tileType) == true )
		if ( tmpT.isRoad == true )
			return true;
	
	if ( parseIsSea(tileType) == true )
		if ( tmpT.isSea == true )
			return true;
	
	if ( parseIsBeach(tileType) ==  true )
		if ( tmpT.isBeach == true )
			return true;
	
	if ( parseIsRiver(tileType) == true )
		if ( tmpT.isRiver == true )
			return true;
	
	if ( parseIsBridge(tileType) == true )
		if ( tmpT.isBridge == true )
			return true;

	switch ( tileType )
	{
	case TT_Plain:
		return setPlain(position);
		break;
	case TT_Tree:
		return setTree(position);
		break;
	case TT_Mountain_1:
	case TT_Mountain_2:
		return setMountain(position);
		break;
	case TT_Road_H:
		return setRoad(position);
		break;
	case TT_Sea:
		return setSee(position);
		break;
	case TT_Reef:
		return setReef(position);
		break;
	case TT_Beach_T:
		return setBeach(position);
		break;
	case TT_River_H:
		return setRiver(position);
		break;
	case TT_Bridge_H:
		return setBridge(position);
		break;
	}

	// For buildings
	if ( parseIsBuilding(tileType) )
	{
		return setBuilding(position,tileType);
	}

	assert(0);	// All cases have to be handled

	return false;
}

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
		if ( this->getTile(position).tileType == TT_Sea )
		{
			return true;
		}
		else
		{
			return false;
		}
	case TT_Beach_T:
		switch ( this->getTile(position).tileType )
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
		switch ( this->getTile(position).tileType )
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
			break;
		default:
			return false;
			break;
		}
	break;
	}

	// For buildings (can be everywhere)
	if ( parseIsBuilding(tileType) )
	{
		return true;
	}

	assert(0);	// All cases have to be handled

	return true;
}

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
	file << m_theme << std::endl;

	// The size 'width height'
	file << this->width << " " << this->height << std::endl;

	// The tiles data

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
			file << map[y][x].tileType;
		}

		file << std::endl;
	}

	file.close();

	return true;
}

#endif