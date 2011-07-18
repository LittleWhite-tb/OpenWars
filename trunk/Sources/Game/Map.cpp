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

#include "Utils/LineParser.h"
#include "Utils/Logger.h"

#include "NEngine/Exceptions/ConstructionFailedException.h"
#include "Utils/Exceptions/FileNotOpenedException.h"

#include "globals.h"

Map :: Map(const Library<Theme>* const pThemes)
	:pThemes(pThemes),themeName("classic"),width(0),height(0),valid(false)
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

	return true;
}

bool Map :: load(const std::string& fileName)
{
	unsigned int mapLineCounter = 0;
	unsigned int unitMapLineCounter = 0;
	bool error = false;

	LineParser lp(fileName);

	LDebug << "Map :: load '" << fileName.c_str() << "'";

	do
	{
		if ( lp.getLineNumber() == 1 )
		{
			themeName = lp.getLine();
			
			if ( !pThemes->exists(themeName) )
			{
				LError << "Map is asking for a theme not found";
				error = true;
			}

			LDebug << "Theme: " << themeName.c_str();
		}
		else if ( lp.getLineNumber() == 2 )
		{
			IVec2 size = lp.getIVec2();

			this->width = size.x;
			this->height = size.y;

			if ( this->width != 0 || this->height != 0 )	// If it looks correct (we can add a maximum size... to be safer)
			{
				this->allocateMemory(USize2(width,height));
			}
			else
			{
				LError << "Size of the map not valid (" << this->width << ";" << this->height << ")";
				error = true;
			}
		}
		else if ( lp.getLineNumber() >= 3 && lp.getLineNumber() < 3 + this->height ) // For all lines representating the map
		{
			std::stringstream ss(lp.getLine());
			int tileID = -1;

			mapLineCounter++;

			// We are reading one line, by one
			for ( unsigned int x = 0 ; x < this->width ; x++ )
			{
				ss >> tileID;
				if ( tileID != -1 )
				{
					if ( pThemes->get(themeName)->containsTile(tileID) )
					{
						tileMap[lp.getLineNumber()-3][x] = pThemes->get(themeName)->getTile(tileID);
					}
					else
					{
						LWarning << "Tile data in the map invalid (" << tileID << ") at position " << x << ";" << lp.getLineNumber()-3;
						error = true;
					}	
				}
				else
				{
					LError << "Fail to read the tile type @ " << x << ";" << lp.getLineNumber()-3;
					error = true;
				}
			}
		}
		else if ( lp.getLineNumber() >= 3+this->height && lp.getLineNumber() < 3+this->height*2 )	// For the unit map
		{
			std::stringstream ss(lp.getLine());
			int unitID = -42;

			unitMapLineCounter++;

			// We are reading one line, by one
			for ( unsigned int x = 0 ; x < this->width ; x++ )
			{
				ss >> unitID;
				if ( unitID != -42 )
				{
					if ( unitID == -1 )
					{
						unitMap[lp.getLineNumber()-(3+this->height)][x] = Unit();
					}
					else if ( pThemes->get(themeName)->containsUnit(unitID) )
					{
						unitMap[lp.getLineNumber()-(3+this->height)][x] = Unit(pThemes->get(themeName)->getUnit(unitID));
					}
					else
					{
						LWarning << "Data in the map invalid (" << unitID << ")";
						error = true;
					}	
				}
				else
				{
					LError << "Fail to read the tile type @ " << x << ";" << lp.getLineNumber()-(3+this->height);
					error = true;
				}
			}
		}
	}while(lp.readNextLine());

	return !error;
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
				bResult &= pThemes->get(themeName)->getTile("Plain")->getSprite()->draw(r,tilePos,0);
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