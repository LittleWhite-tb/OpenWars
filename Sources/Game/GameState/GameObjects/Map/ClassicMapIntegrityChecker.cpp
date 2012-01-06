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

#include "ClassicMapIntegrityChecker.h"

#include <cassert>

#include "NEngine/NEngine.h"

#include "Engine/Params.h"

#include "Game/GameState/GameObjects/Map/Map.h"
#include "Game/GameState/GameObjects/Tile.h"
#include "Game/GameState/GameObjects/UnitTemplate.h"

const Tile* seaChecker(const Map* pMap, const UVec2& position, bool isBeach)
{
	assert(pMap);
	if ( pMap->isValidPosition(position) /*&& pMap->getTile(position)->getParams()->getAs<bool>("isSea",false)*/ )
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
		bool beachOnLeft = false;
		bool beachOnRight = false;
		bool beachOnDown = false;
		bool beachOnUp = false;
		unsigned char nbSeeDiagonal = 0;

		const Tile* pTileL = pMap->getTile(UVec2(position.x-1,position.y)); // Left
		const Tile* pTileT = pMap->getTile(UVec2(position.x,position.y-1)); // Top
		const Tile* pTileLT = pMap->getTile(UVec2(position.x-1,position.y-1)); // Left Top
		const Tile* pTileR = pMap->getTile(UVec2(position.x+1,position.y)); // Right
		const Tile* pTileRT = pMap->getTile(UVec2(position.x+1,position.y-1)); // Top Right
		const Tile* pTileB = pMap->getTile(UVec2(position.x,position.y+1)); // Bottom
		const Tile* pTileLB = pMap->getTile(UVec2(position.x-1,position.y+1)); // Bottom Left
		const Tile* pTileRB = pMap->getTile(UVec2(position.x+1,position.y+1)); // Bottom Right
			
		// Check the 8 tiles around and set the flags
		if (pTileL )
		{
			if ( pTileL->getParams()->getAs<bool>("isSea",false) || 
				 pTileL->getParams()->getAs<bool>("isBridge",false) )	// Left
			{
				nbSeeAround++;
				isHorizontalSee = true;
				onLeft = true;

				if ( pTileL->getParams()->getAs<bool>("isBeach",false) )
				{
					beachOnLeft = true;
				}
			}
		}
		
		if ( pTileR )
		{
			if ( pTileR->getParams()->getAs<bool>("isSea",false) || 
				 pTileR->getParams()->getAs<bool>("isBridge",false) ) // Right
			{
				nbSeeAround++;
				isHorizontalSee = true;
				onRight = true;

				if ( pTileR->getParams()->getAs<bool>("isBeach",false) )
				{
					beachOnRight = true;
				}
			}
		}

		if ( pTileT )
		{
			if ( pTileT->getParams()->getAs<bool>("isSea",false) || 
				 pTileT->getParams()->getAs<bool>("isBridge",false) ) // Up
			{
				nbSeeAround++;
				isVerticalSee = true;
				onUp = true;

				if ( pTileT->getParams()->getAs<bool>("isBeach",false) )
				{
					beachOnUp = true;
				}
			}
		}

		if ( pTileB )
		{
			if ( pTileB->getParams()->getAs<bool>("isSea",false) || 
				 pTileB->getParams()->getAs<bool>("isBridge",false) ) // Down
			{
				nbSeeAround++;
				isVerticalSee = true;
				onDown = true;

				if ( pTileB->getParams()->getAs<bool>("isBeach",false) )
				{
					beachOnDown = true;
				}
			}
		}

		if ( pTileLT )
		{
			if ( pTileLT->getParams()->getAs<bool>("isSea",false) || 
				 pTileLT->getParams()->getAs<bool>("isBridge",false) ) // Up Left
			{
				// nbSeeAround++;
				nbSeeDiagonal++;
				onUpLeft = true;
			}
		}

		if ( pTileRT )
		{
			if ( pTileRT->getParams()->getAs<bool>("isSea",false) || 
				 pTileRT->getParams()->getAs<bool>("isBridge",false) ) // Up Right
			{
				// nbSeeAround++;
				nbSeeDiagonal++;
				onUpRight = true;
			}
		}

		if ( pTileLB )
		{
			if ( pTileLB->getParams()->getAs<bool>("isSea",false) || 
				 pTileLB->getParams()->getAs<bool>("isBridge",false) ) // Down Left
			{
				// nbSeeAround++;
				nbSeeDiagonal++;
				onDownLeft = true;
			}
		}

		if ( pTileRB )
		{
			if ( pTileRB->getParams()->getAs<bool>("isSea",false) || 
				 pTileRB->getParams()->getAs<bool>("isBridge",false) ) // Down Right
			{
				// nbSeeAround++;
				nbSeeDiagonal++;
				onDownRight = true;
			}
		}

		// Now that we have all informations needed, we update the map
		switch(nbSeeAround)
		{
			case 0:
				// Diagonals are not important here
				return pMap->getTheme()->getTile("Coast");	// The default one
				break;
			case 1:
				// Diagonals are not important here
				if ( onLeft )
				{
					if ( isBeach )
					{
						return pMap->getTheme()->getTile("Beach_ER");
					}
					else
					{
						return pMap->getTheme()->getTile("Coast_ER");
					}
				}
				else if ( onRight )
				{
					if ( isBeach )
					{
						return pMap->getTheme()->getTile("Beach_EL");
					}
					else
					{
						return pMap->getTheme()->getTile("Coast_EL");
					}
				}
				else if ( onUp )
				{
					if ( isBeach )
					{
						return pMap->getTheme()->getTile("Beach_EB");
					}
					else
					{
						return pMap->getTheme()->getTile("Coast_EB");
					}
				}
				else if ( onDown )
				{
					if ( isBeach )
					{
						return pMap->getTheme()->getTile("Beach_ET");
					}
					else
					{
						return pMap->getTheme()->getTile("Coast_ET");
					}
				}
				break;
			case 2: // Can be a line or a corner
				// Line case
				if ( isVerticalSee && !isHorizontalSee )
				{
					return pMap->getTheme()->getTile("Coast_V");
				}

				if ( isHorizontalSee && !isVerticalSee )
				{
					return pMap->getTheme()->getTile("Coast_H");
				}

				// Corners
				if ( onLeft && onUp )
				{
					if ( onUpLeft )
					{
						if ( isBeach )
						{
							if ( beachOnUp && beachOnLeft )
							{
								return pMap->getTheme()->getTile("Beach_BR_2");
							}
							else if ( beachOnUp )
							{
								return pMap->getTheme()->getTile("Beach_BR_T");
							}
							else if ( beachOnLeft )
							{
								return pMap->getTheme()->getTile("Beach_BR_L");
							}
							
							return pMap->getTheme()->getTile("Beach_BR");
						}
						else
						{
							return pMap->getTheme()->getTile("Coast_BR");
						}
					}
					else
					{
						return pMap->getTheme()->getTile("Coast_RBR");
					}
				}

				if ( onRight && onUp )
				{
					if ( onUpRight )
					{
						if ( isBeach )
						{
							if ( beachOnUp && beachOnRight )
							{
								return pMap->getTheme()->getTile("Beach_BL_2");
							}
							else if ( beachOnUp )
							{
								return pMap->getTheme()->getTile("Beach_BL_T");
							}
							else if ( beachOnRight )
							{
								return pMap->getTheme()->getTile("Beach_BL_R");
							}
							
							return pMap->getTheme()->getTile("Beach_BL");
						}
						else
						{
							return pMap->getTheme()->getTile("Coast_BL");
						}					
					}
					else
					{
						return pMap->getTheme()->getTile("Coast_RBL");
					}
				}

				if ( onLeft && onDown )
				{
					if ( onDownLeft )
					{
						if ( isBeach )
						{
							if ( beachOnDown && beachOnLeft )
							{
								return pMap->getTheme()->getTile("Beach_TR_2");
							}
							else if ( beachOnDown )
							{
								return pMap->getTheme()->getTile("Beach_TR_B");
							}
							else if ( beachOnLeft )
							{
								return pMap->getTheme()->getTile("Beach_TR_L");
							}
							
							return pMap->getTheme()->getTile("Beach_TR");
						}
						else
						{
							return pMap->getTheme()->getTile("Coast_TR");
						}
					}
					else
					{
						return pMap->getTheme()->getTile("Coast_RTR");
					}
				}

				if ( onRight && onDown )
				{
					if ( onDownRight )
					{
						if ( isBeach )
						{
							if ( beachOnDown && beachOnRight )
							{
								return pMap->getTheme()->getTile("Beach_TL_2");
							}
							else if ( beachOnDown )
							{
								return pMap->getTheme()->getTile("Beach_TL_B");
							}
							else if ( beachOnRight )
							{
								return pMap->getTheme()->getTile("Beach_TL_R");
							}
							
							return pMap->getTheme()->getTile("Beach_TL");
						}
						else
						{
							return pMap->getTheme()->getTile("Coast_TL");
						}
					}
					else
					{
						return pMap->getTheme()->getTile("Coast_RTL");
					}
				}

				break;

			case 3: // Can be a T, or a corner 
				if ( onLeft && onRight && onUp )
				{
					if ( nbSeeDiagonal >= 1 )
					{
						if ( onUpLeft && onUpRight )
						{
							if ( isBeach )
							{
								if ( beachOnRight && beachOnLeft )
								{
									return pMap->getTheme()->getTile("Beach_B_2");
								}
								else if ( beachOnLeft )
								{
									return pMap->getTheme()->getTile("Beach_B_L");
								}
								else if ( beachOnRight )
								{
									return pMap->getTheme()->getTile("Beach_B_R");
								}
								
								return pMap->getTheme()->getTile("Beach_B");
							}

							if ( pTileB == pMap->getTheme()->getTile("River_V") )
							{
								if ( pMap->getTile(UVec2(position.x,position.y+2)) == pMap->getTheme()->getTile("River_V") )
								{
									return pMap->getTheme()->getTile("River_See_B");
								}
							}

							return pMap->getTheme()->getTile("Coast_B");
						}

						if ( onUpLeft )
						{
							return pMap->getTheme()->getTile("Coast_T_BR");
						}
						
						if ( onUpRight )
						{
							return pMap->getTheme()->getTile("Coast_T_BL");
						}
					}
					return pMap->getTheme()->getTile("Coast_T_B");
				}

				if ( onLeft && onRight && onDown )
				{
					if ( nbSeeDiagonal >= 1 )
					{
						if ( onDownLeft && onDownRight )
						{
							if ( isBeach )
							{
								if ( beachOnRight && beachOnLeft )
								{
									return pMap->getTheme()->getTile("Beach_T_2");
								}
								else if ( beachOnLeft )
								{
									return pMap->getTheme()->getTile("Beach_T_L");
								}
								else if ( beachOnRight )
								{
									return pMap->getTheme()->getTile("Beach_T_R");
								}
								
								return pMap->getTheme()->getTile("Beach_T");
							}

							if ( pTileT == pMap->getTheme()->getTile("River_V") && pMap->getTile(UVec2(position.x,position.y-2)) == pMap->getTheme()->getTile("River_V") )
							{
								return pMap->getTheme()->getTile("River_See_T");
							}

							return pMap->getTheme()->getTile("Coast_T");
						}

						if ( onDownLeft )
						{
							return pMap->getTheme()->getTile("Coast_T_TR");
						}
						
						if ( onDownRight )
						{
							return pMap->getTheme()->getTile("Coast_T_TL");
						}	
					}

					return pMap->getTheme()->getTile("Coast_T_T");
				}

				if ( onUp && onDown && onLeft )
				{
					if ( nbSeeDiagonal >= 1 )
					{
						if ( onUpLeft && onDownLeft )
						{
							if ( isBeach )
							{
								if ( beachOnUp && beachOnDown )
								{
									return pMap->getTheme()->getTile("Beach_R_2");
								}
								else if ( beachOnUp )
								{
									return pMap->getTheme()->getTile("Beach_R_T");
								}
								else if ( beachOnDown )
								{
									return pMap->getTheme()->getTile("Beach_R_B");
								}
								
								return pMap->getTheme()->getTile("Beach_R");
							}

							if ( pTileR == pMap->getTheme()->getTile("River_H") && pMap->getTile(UVec2(position.x+2,position.y)) == pMap->getTheme()->getTile("River_H") )
							{
								return pMap->getTheme()->getTile("River_See_R");
							}

							return pMap->getTheme()->getTile("Coast_R");
						}
						if ( onUpLeft )
						{
							return pMap->getTheme()->getTile("Coast_T_RB");
						}
						
						if ( onDownLeft )
						{
							return pMap->getTheme()->getTile("Coast_T_RT");
						}	
					}
					return pMap->getTheme()->getTile("Coast_T_R");
				}

				if ( onUp && onDown && onRight )
				{
					if ( nbSeeDiagonal >= 1 )
					{
						if ( onDownRight && onUpRight )
						{
							if ( isBeach )
							{
								if ( beachOnUp && beachOnDown )
								{
									return pMap->getTheme()->getTile("Beach_L_2");
								}
								else if ( beachOnUp )
								{
									return pMap->getTheme()->getTile("Beach_L_T");
								}
								else if ( beachOnDown )
								{
									return pMap->getTheme()->getTile("Beach_L_B");
								}
								
								return pMap->getTheme()->getTile("Beach_L");
							}

							if ( pTileL == pMap->getTheme()->getTile("River_H") && pMap->getTile(UVec2(position.x-2,position.y)) == pMap->getTheme()->getTile("River_H") )
							{
								return pMap->getTheme()->getTile("River_See_L");
							}

							return pMap->getTheme()->getTile("Coast_L");
						}
						if ( onUpRight)
						{
							return pMap->getTheme()->getTile("Coast_T_LB");
						}
						
						if ( onDownRight )
						{
							return pMap->getTheme()->getTile("Coast_T_LT");
						}
					}
					return pMap->getTheme()->getTile("Coast_T_L");
				}
				break;
				

			case 4:
				switch(nbSeeDiagonal)
				{
					case 0:
						return pMap->getTheme()->getTile("Coast_X");
						break;
					case 1:
						if ( onUpLeft )
						{
							return pMap->getTheme()->getTile("Coast_XBR");
						}
						if ( onUpRight )
						{
							return pMap->getTheme()->getTile("Coast_XBL");
						}
						if ( onDownLeft )
						{
							return pMap->getTheme()->getTile("Coast_XTR");
						}
						if ( onDownRight )
						{
							return pMap->getTheme()->getTile("Coast_XTL");
						}
						break;
					case 2:
						if ( onUpLeft && onUpRight )
						{
							return pMap->getTheme()->getTile("Coast_XB");
						}
						if ( onUpLeft && onDownLeft )
						{
							return pMap->getTheme()->getTile("Coast_XR");
						}
						if ( onDownLeft && onDownRight )
						{
							return pMap->getTheme()->getTile("Coast_XT");
						}
						if ( onDownRight && onUpRight )
						{
							return pMap->getTheme()->getTile("Coast_XL");
						}
						if ( onDownRight && onUpLeft )
						{
							return pMap->getTheme()->getTile("Coast_XBLTR");
						}
						if ( onDownLeft && onUpRight )
						{
							return pMap->getTheme()->getTile("Coast_XTLBR");
						}
						break;
					case 3:
						if ( onDownRight && onUpRight && onUpLeft )
						{
							return pMap->getTheme()->getTile("Sea_BL");
						}
						if ( onUpRight && onUpLeft && onDownLeft )
						{
							return pMap->getTheme()->getTile("Sea_BR");
						}
						if ( onUpLeft && onDownLeft && onDownRight )
						{
							return pMap->getTheme()->getTile("Sea_TR");
						}
						if ( onDownLeft && onDownRight && onUpRight )
						{
							return pMap->getTheme()->getTile("Sea_TL");
						}
						break;
					case 4:
						return pMap->getTheme()->getTile("Sea");
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

	return NULL;
}

const Tile* seaChecker(const Map* pMap, const UVec2& position)
{
	return seaChecker(pMap,position,false);
}

const Tile* beachChecker(const Map* pMap, const UVec2& position)
{
	return seaChecker(pMap,position,true);
}

const Tile* bridgeChecker(const Map* pMap, const UVec2& position)
{
	assert(pMap);
	if ( pMap->isValidPosition(position) && pMap->getTile(position)->getParams()->getAs<bool>("isBridge",false) == false )
	{
		std::string tileName = pMap->getTile(position)->getInternalName();
		if ( tileName == "River_V" )
		{
			return pMap->getTheme()->getTile("Bridge_H");
		}
		else if ( tileName == "River_H" )
		{
			return pMap->getTheme()->getTile("Bridge_V");
		}
		else if ( tileName == "Coast_V" || tileName == "Coast_L" || tileName == "Coast_R" )
		{
			return pMap->getTheme()->getTile("Bridge_H");
		}
		else if ( tileName == "Coast_H" || tileName == "Coast_B" || tileName == "Coast_T" )
		{
			return pMap->getTheme()->getTile("Bridge_V");
		}
		else if ( tileName == "Sea" )
		{
			const Tile* pTileL = pMap->getTile(UVec2(position.x-1,position.y)); // Left
			const Tile* pTileT = pMap->getTile(UVec2(position.x,position.y-1)); // Top
			const Tile* pTileR = pMap->getTile(UVec2(position.x+1,position.y)); // Right
			const Tile* pTileB = pMap->getTile(UVec2(position.x,position.y+1)); // Bottom

				if ( (pTileL && pTileL->getParams()->getAs<bool>("isBridge",false)) || 
					 (pTileR && pTileR->getParams()->getAs<bool>("isBridge",false)) )
				{
					return pMap->getTheme()->getTile("Bridge_H");
				}
				else if ( (pTileB && pTileB->getParams()->getAs<bool>("isBridge",false)) || 
					      (pTileT && pTileT->getParams()->getAs<bool>("isBridge",false)) )
				{
					return pMap->getTheme()->getTile("Bridge_V");
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

	}
	return NULL;
}

const Tile* riverChecker(const Map* pMap, const UVec2& position)
{
	assert(pMap);
	if ( pMap->isValidPosition(position) /*&& pMap->getTile(position)->getParams()->getAs<bool>("isRiver",false)*/ )
	{
		unsigned char nbRiverAround = 0;
		bool isVerticalRiver = false;
		bool isHorizontalRiver = false;
		bool onLeft = false;
		bool onRight = false;
		bool onUp = false;
		bool onDown = false;

		const Tile* pTileL = pMap->getTile(UVec2(position.x-1,position.y)); // Left
		const Tile* pTileT = pMap->getTile(UVec2(position.x,position.y-1)); // Top
		const Tile* pTileLT = pMap->getTile(UVec2(position.x-1,position.y-1)); // Left Top
		const Tile* pTileR = pMap->getTile(UVec2(position.x+1,position.y)); // Right
		const Tile* pTileRT = pMap->getTile(UVec2(position.x+1,position.y-1)); // Top Right
		const Tile* pTileB = pMap->getTile(UVec2(position.x,position.y+1)); // Bottom
		const Tile* pTileLB = pMap->getTile(UVec2(position.x-1,position.y+1)); // Bottom Left
		const Tile* pTileRB = pMap->getTile(UVec2(position.x+1,position.y+1)); // Bottom Right
			
		if ( (pTileL && pTileL->getParams()->getAs<bool>("isRiver",false)) || 
			 (pTileL && pTileL->getParams()->getAs<bool>("isBridge",false)) )	// Left
		{
			nbRiverAround++;
			isHorizontalRiver = true;
			onLeft = true;
		}
		
		if ( (pTileR && pTileR->getParams()->getAs<bool>("isRiver",false)) || 
			 (pTileR && pTileR->getParams()->getAs<bool>("isBridge",false)) ) // Right
		{
			nbRiverAround++;
			isHorizontalRiver = true;
			onRight = true;
		}

		if ( (pTileT && pTileT->getParams()->getAs<bool>("isRiver",false)) || 
			 (pTileT && pTileT->getParams()->getAs<bool>("isBridge",false)) ) // Up
		{
			nbRiverAround++;
			isVerticalRiver = true;
			onUp = true;
		}

		if ( (pTileB && pTileB->getParams()->getAs<bool>("isRiver",false)) || 
			 (pTileB && pTileB->getParams()->getAs<bool>("isBridge",false)) ) // Down
		{
			nbRiverAround++;
			isVerticalRiver = true;
			onDown = true;
		}

		switch(nbRiverAround)
		{
			case 0:
				return pMap->getTheme()->getTile("River_H");	// The default one
				break;
			case 1:
				// Test for the river to see tiles
				if ( onLeft && 
					 pTileT && pTileT->getParams()->getAs<bool>("isSea",false) && 
					 pTileB && pTileB->getParams()->getAs<bool>("isSea",false) && 
					 pTileR && pTileR->getParams()->getAs<bool>("isSea",false) && 
					 pTileRB && pTileRB->getParams()->getAs<bool>("isSea",false) && 
					 pTileRT && pTileRT->getParams()->getAs<bool>("isSea",false) )
				{
					return pMap->getTheme()->getTile("River_See_L");
				}

				if ( onRight && 
					pTileT && pTileT->getParams()->getAs<bool>("isSea",false) && 
					pTileB && pTileB->getParams()->getAs<bool>("isSea",false) &&
					pTileL && pTileL->getParams()->getAs<bool>("isSea",false) && 
					pTileLB && pTileLB->getParams()->getAs<bool>("isSea",false) && 
					pTileLT && pTileLT->getParams()->getAs<bool>("isSea",false) )
				{
					return pMap->getTheme()->getTile("River_See_R");
				}

				if ( onDown && 
					 pTileL && pTileL->getParams()->getAs<bool>("isSea",false) && 
					 pTileR && pTileR->getParams()->getAs<bool>("isSea",false) && 
					 pTileT && pTileT->getParams()->getAs<bool>("isSea",false) && 
					 pTileRT && pTileRT->getParams()->getAs<bool>("isSea",false) && 
					 pTileLT && pTileLT->getParams()->getAs<bool>("isSea",false) )
				{
					return pMap->getTheme()->getTile("River_See_B");
				}

				if ( onUp && 
					 pTileL && pTileL->getParams()->getAs<bool>("isSea",false) && 
					 pTileR && pTileR->getParams()->getAs<bool>("isSea",false) && 
					 pTileB && pTileB->getParams()->getAs<bool>("isSea",false) && 
					 pTileRB && pTileRB->getParams()->getAs<bool>("isSea",false) && 
					 pTileLB && pTileLB->getParams()->getAs<bool>("isSea",false) )
				{
					return pMap->getTheme()->getTile("River_See_T");
				}

				if ( isVerticalRiver )
				{
					return pMap->getTheme()->getTile("River_V");	// The default one
				}
				else if ( isHorizontalRiver )
				{
					return pMap->getTheme()->getTile("River_H");
				}

				break;
			case 2: // Can be a line or a corner
				// Line case
				if ( isVerticalRiver && !isHorizontalRiver )
				{
					return pMap->getTheme()->getTile("River_V");
				}

				if ( isHorizontalRiver && !isVerticalRiver )
				{
					return pMap->getTheme()->getTile("River_H");
				}

				if ( onLeft && onUp )
				{
					return pMap->getTheme()->getTile("River_BR");
				}

				if ( onRight && onUp )
				{
					return pMap->getTheme()->getTile("River_BL");
				}

				if ( onLeft && onDown )
				{
					return pMap->getTheme()->getTile("River_TR");
				}

				if ( onRight && onDown )
				{
					return pMap->getTheme()->getTile("River_TL");
				}
				break;

			case 3: // Will be a T
				if ( onLeft && onRight && onUp )
				{
					return pMap->getTheme()->getTile("River_T_B");
				}

				if ( onLeft && onRight && onDown )
				{
					return pMap->getTheme()->getTile("River_T_T");
				}

				if ( onUp && onDown && onLeft )
				{
					return pMap->getTheme()->getTile("River_T_R");
				}

				if ( onUp && onDown && onRight )
				{
					return pMap->getTheme()->getTile("River_T_L");
				}
				break;
			case 4:
				return pMap->getTheme()->getTile("River_X");
				break;
		}
	}

	return NULL;
}

const Tile* roadChecker(const Map* pMap, const UVec2& position)
{
	assert(pMap);
	if ( pMap->isValidPosition(position) /*&& pMap->getTile(position)->getParams()->getAs<bool>("isRoad",false)*/ )
	{
		unsigned char nbRoadAround = 0;
		bool isVerticalRoad = false;
		bool isHorizontalRoad = false;
		bool onLeft = false;
		bool onRight = false;
		bool onUp = false;
		bool onDown = false;

		const Tile* pTileL = pMap->getTile(UVec2(position.x-1,position.y)); // Left
		const Tile* pTileT = pMap->getTile(UVec2(position.x,position.y-1)); // Top
		const Tile* pTileR = pMap->getTile(UVec2(position.x+1,position.y)); // Right
		const Tile* pTileB = pMap->getTile(UVec2(position.x,position.y+1)); // Bottom
		
		if ( pTileL )
		{
			if ( pTileL->getParams()->getAs<bool>("isRoad",false) || 
				 pTileL->getParams()->getAs<bool>("isBridge",false) || 
				 pTileL->getParams()->getAs<bool>("isHQ",false) )	// Left
			{
				nbRoadAround++;
				isHorizontalRoad = true;
				onLeft = true;
			}
		}
		
		if ( pTileR )
		{
			if ( pTileR->getParams()->getAs<bool>("isRoad",false) || 
				 pTileR->getParams()->getAs<bool>("isBridge",false) || 
				 pTileR->getParams()->getAs<bool>("isHQ",false) ) // Right
			{
				nbRoadAround++;
				isHorizontalRoad = true;
				onRight = true;
			}
		}

		if ( pTileT )
		{
			if ( pTileT->getParams()->getAs<bool>("isRoad",false) || 
				 pTileT->getParams()->getAs<bool>("isBridge",false) || 
				 pTileT->getParams()->getAs<bool>("isHQ",false) ) // Up
			{
				nbRoadAround++;
				isVerticalRoad = true;
				onUp = true;
			}
		}

		if ( pTileB )
		{
			if ( pTileB->getParams()->getAs<bool>("isRoad",false) || 
				 pTileB->getParams()->getAs<bool>("isBridge",false) || 
				 pTileB->getParams()->getAs<bool>("isHQ",false) ) // Down
			{
				nbRoadAround++;
				isVerticalRoad = true;
				onDown = true;
			}
		}

		switch(nbRoadAround)
		{
			case 0:
				return pMap->getTheme()->getTile("Road_H");	// The default one
				break;
			case 1:
				if ( isVerticalRoad )
				{
					return pMap->getTheme()->getTile("Road_V");	// The default one
				}
				else if ( isHorizontalRoad )
				{
					return pMap->getTheme()->getTile("Road_H");
				}
				break;
			case 2: // Can be a line or a corner
				// Line case
				if ( isVerticalRoad && !isHorizontalRoad )
				{
					return pMap->getTheme()->getTile("Road_V");
				}

				if ( isHorizontalRoad && !isVerticalRoad )
				{
					return pMap->getTheme()->getTile("Road_H");
				}

				if ( onLeft && onUp )
				{
					return pMap->getTheme()->getTile("Road_TL");
				}

				if ( onRight && onUp )
				{
					return pMap->getTheme()->getTile("Road_TR");
				}

				if ( onLeft && onDown )
				{
					return pMap->getTheme()->getTile("Road_BL");
				}

				if ( onRight && onDown )
				{
					return pMap->getTheme()->getTile("Road_BR");
				}
				break;

			case 3: // Will be a T
				if ( onLeft && onRight && onUp )
				{
					return pMap->getTheme()->getTile("Road_T_T");
				}

				if ( onLeft && onRight && onDown )
				{
					return pMap->getTheme()->getTile("Road_T_B");
				}

				if ( onUp && onDown && onLeft )
				{
					return pMap->getTheme()->getTile("Road_T_L");
				}

				if ( onUp && onDown && onRight )
				{
					return pMap->getTheme()->getTile("Road_T_R");
				}
				break;
			case 4:
				return pMap->getTheme()->getTile("Road_X");
				break;
		}
	}
	return NULL;
}

ClassicMapIntegrityChecker :: ClassicMapIntegrityChecker(const Map* pMap):MapIntegrityChecker(pMap) 
{
	coherencyCheckers["SeaChecker"] = &seaChecker;
	coherencyCheckers["BeachChecker"] = &beachChecker;
	coherencyCheckers["BridgeChecker"] = &bridgeChecker;
	coherencyCheckers["RiverChecker"] = &riverChecker;
	coherencyCheckers["RoadChecker"] = &roadChecker;
}

void ClassicMapIntegrityChecker :: addChecker(const std::string& name)
{
	// Do nothing (all was done in the constructor)
	(void)name;
}

bool ClassicMapIntegrityChecker :: testTile(const UVec2& position, const Tile* pTile)const
{
	// Extra protections
	assert(pTile);
	if ( pMap->isValidPosition(position) )
	{
		if ( pTile->getParams()->getAs<bool>("isReef",false) )
		{
			if ( pMap->getTile(position)->getParams()->getAs("isSee",false) )
			{
				return true;
			}
			return false;
		}
		else if ( pTile->getParams()->getAs<bool>("isBeach",false) )
		{
			std::string internalTileName = pMap->getTile(position)->getInternalName();
			if ( internalTileName == "Coast_B" ||
				 internalTileName == "Coast_T" || 
				 internalTileName == "Coast_R" || 
				 internalTileName == "Coast_L" || 
				 internalTileName == "Coast_ER" || 
				 internalTileName == "Coast_EL" || 
				 internalTileName == "Coast_EB" || 
				 internalTileName == "Coast_ET" || 
				 internalTileName == "Coast_BL" || 
				 internalTileName == "Coast_BR" || 
				 internalTileName == "Coast_TR" ||
				 internalTileName == "Coast_TL" )
			{
				return true;
			}

			return false;
		}
		else if ( pTile->getParams()->getAs<bool>("isRiver",false) )
		{
			if ( pMap->getTile(position)->getParams()->getAs("isSee",false) )
			{
				return false;
			}

			const Tile* pTileL = pMap->getTile(UVec2(position.x-1,position.y)); // Left
			const Tile* pTileT = pMap->getTile(UVec2(position.x,position.y-1)); // Top
			const Tile* pTileLT = pMap->getTile(UVec2(position.x-1,position.y-1)); // Left Top
			const Tile* pTileR = pMap->getTile(UVec2(position.x+1,position.y)); // Right
			const Tile* pTileRT = pMap->getTile(UVec2(position.x+1,position.y-1)); // Top Right
			const Tile* pTileB = pMap->getTile(UVec2(position.x,position.y+1)); // Bottom
			const Tile* pTileLB = pMap->getTile(UVec2(position.x-1,position.y+1)); // Bottom Left
			const Tile* pTileRB = pMap->getTile(UVec2(position.x+1,position.y+1)); // Bottom Right
			// Check Top Left corner
			if ( pTileL && pTileL->getParams()->getAs<bool>("isRiver",false) && // Left
				 pTileT && pTileT->getParams()->getAs<bool>("isRiver",false) && // Top
				 pTileLT && pTileLT->getParams()->getAs<bool>("isRiver",false) ) // TopLeft
				 return false;

			// Check Top Right corner
			if ( pTileR && pTileR->getParams()->getAs<bool>("isRiver",false) && // Right
				 pTileT && pTileT->getParams()->getAs<bool>("isRiver",false) && // Top
				 pTileRT && pTileRT->getParams()->getAs<bool>("isRiver",false) ) // TopRight
				 return false;

			// Check Bottom Left corner
			if ( pTileL && pTileL->getParams()->getAs<bool>("isRiver",false) && // Left
				 pTileB && pTileB->getParams()->getAs<bool>("isRiver",false) && // Bottom
				 pTileLB && pTileLB->getParams()->getAs<bool>("isRiver",false) ) // BottomLeft
				 return false;

			// Check Bottom Right corner
			if ( pTileR && pTileR->getParams()->getAs<bool>("isRiver",false) && // Right
				 pTileB && pTileB->getParams()->getAs<bool>("isRiver",false) && // Bottom
				 pTileRB && pTileRB->getParams()->getAs<bool>("isRiver",false) ) // BottomRight
				 return false;

			return true;
		}
		else if ( pTile->getParams()->getAs<bool>("isBridge",false) )
		{
			std::string internalTileName = pMap->getTile(position)->getInternalName();
			if ( internalTileName == "River_H" ||
				 internalTileName == "River_V" ||
				 internalTileName == "Coast_H" ||
				 internalTileName == "Coast_V" ||
				 internalTileName == "Coast_T" ||
				 internalTileName == "Coast_R" ||
				 internalTileName == "Coast_B" ||
				 internalTileName == "Coast_L" )
			{
				return true;
			}
			else if ( internalTileName == "Sea" )
			{
				// Test is a bridge is around this position (so, the user wants to continue the bridge)
				const Tile* pTileL = pMap->getTile(UVec2(position.x-1,position.y)); // Left
				const Tile* pTileT = pMap->getTile(UVec2(position.x,position.y-1)); // Top
				const Tile* pTileR = pMap->getTile(UVec2(position.x+1,position.y)); // Right
				const Tile* pTileB = pMap->getTile(UVec2(position.x,position.y+1)); // Bottom

				if ( (pTileL && pTileL->getParams()->getAs<bool>("isBridge",false)) || 
					 (pTileR && pTileR->getParams()->getAs<bool>("isBridge",false)) || 
					 (pTileT && pTileT->getParams()->getAs<bool>("isBridge",false)) || 
					 (pTileB && pTileB->getParams()->getAs<bool>("isBridge",false)) )
				{
					return true;
				}
			}

			return false;
		}

		// For buildings (can be everywhere)
		if ( pTile->getParams()->getAs<bool>("isBuilding",false) )
		{
			return true;
		}

		return true;
	}

	return false;
}

bool ClassicMapIntegrityChecker :: testUnit(const UVec2& position, const UnitTemplate* pUnitTemplate)const
{
	assert(pUnitTemplate);

	const Tile* pTile = pMap->getTile(position);
	if ( pTile == NULL )
	{
		return false;
	}

	if ( !pUnitTemplate->getParams()->exists("unit-classId") )
	{
        NEWarning << "An unit template does not have a classId\n";
		return false;
	}

	int unitClassId = pUnitTemplate->getParams()->getAs<int>("unit-classId",-100);
	if ( unitClassId == -100 )
	{
        NEWarning << "An unit template does not have a valide classId (value of -100)\n";
		return false;
	}

	switch ( unitClassId )
	{
		case 0: // These units can't go on sea
			{
				if ( pTile->getParams()->getAs<bool>("isSea",false) == false )
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			break;
		case 1:
			{
				if ( pTile->getParams()->getAs<bool>("isSea",false) ||
					 pTile->getParams()->getAs<bool>("isRiver",false) ||
					 pTile->getParams()->getAs<bool>("isMountain",false) )
				{
					return false;
				}
				else
				{
					return true;
				}
			}
			break;
		case 2:
			{
				if ( pTile->getParams()->getAs<bool>("isSea",false) ||
					 pTile->getParams()->getAs<bool>("isBeach",false) )
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			break;
		case 3:
		case 4:
		case 5:
			{
				if ( pTile->getParams()->getAs<bool>("isSea",false ) )
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			break;
		case 6:	// Flying units can go everywhere
		case 7:
			return true;
			break;
		default:
            NEWarning << "Unknown unity class '" << unitClassId << "'\n";
			return false;
			break;
	}
}