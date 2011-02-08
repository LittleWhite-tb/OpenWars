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

#include "Map.h"

#include <string>

#include <string>
#include <sstream>
#include <fstream>
#include <cassert>

#include "Tile.h"
#include "Unit.h"

#include "../NEngine/SpriteLoader.h"
#include "../Engine/AnimatedSprite.h"

#include "Camera.h"

#include "../Types/Vec2.h"

#include "../Utils/LineParser.h"
#include "../Utils/Logger.h"

#include "../NEngine/Exceptions/ConstructionFailedException.h"
#include "../Utils/Exceptions/FileNotOpenedException.h"

#include "../globals.h"

Map :: Map(NE::SpriteLoader* const pSL, const std::string& fileName)
	:width(0),height(0),map(NULL),valid(false)
{
	valid = this->parser(pSL,fileName);

	LDebug << "Map '" << fileName.c_str() << "' created";
}

Map :: ~Map(void)
{
	// Delete the Tile sprites used by the map
	for ( std::map<TileType, Tile>::iterator itTile = tilesSet.begin() ; itTile != tilesSet.end() ; ++itTile)
	{
		delete itTile->second.pASprite;
	}
	tilesSet.clear();

	// Delete the Unit sprite used by the map
	for ( std::map<UnitType, UnitTemplate>::iterator itUnit = unitsSet.begin() ; itUnit != unitsSet.end() ; ++itUnit)
	{
		delete itUnit->second.pASprite;
	}
	unitsSet.clear();

	// Delete the unit map
	for ( unsigned int y = 0 ; y < this->height ; y++ )
	{
		delete[] unitViewMap[y];
	}

	delete[] unitViewMap;

	// Delete the map
	for ( unsigned int y = 0 ; y < this->height ; y++ )
	{
		delete[] map[y];
	}

	delete[] map;

	LDebug << "Map deleted";
}

bool Map :: loadTileSet(NE::SpriteLoader* const pSL)
{
	LDebug << "Map :: loadTileSet ( " << m_themeName.c_str() << ")";

	// Need reading of the file
	std::string tileSetPath = TILESET_PATH + m_themeName + std::string(".oawts");

	try
	{
		LineParser lp(tileSetPath);

		for ( unsigned int i = TT_Plain ; i < TT_Invalid ; i++ )
		{
			unsigned int idTile = static_cast<unsigned int>(lp.getInt());
			lp.readNextLine();
			if ( i != idTile )
			{
				LWarning << "The tileset does not have sprite is good orger -> Received: " << idTile << " ; Expected: " << i;
			}
			std::string name = lp.getLine();
			lp.readNextLine();
			std::string spriteName = lp.getLine();
			lp.readNextLine();
			USize2 spriteSize = lp.getUSize2();
			lp.readNextLine();
			int spriteDuration = lp.getInt();
			lp.readNextLine();
			unsigned char defence = static_cast<unsigned char>(lp.getInt());
			lp.readNextLine();
			bool isRoad = lp.getBool();
			lp.readNextLine();
			bool isBridge = lp.getBool();
			lp.readNextLine();
			bool isRiver = lp.getBool();
			lp.readNextLine();
			bool isSea = lp.getBool();
			lp.readNextLine();
			bool isBeach = lp.getBool();
			lp.readNextLine();
			bool isBuilding = lp.getBool();
			lp.readNextLine();
			bool isHQ = lp.getBool();
			lp.readNextLine();
			bool needBackground = lp.getBool();
			lp.readNextLine();
			unsigned char cityLife = static_cast<unsigned char>(lp.getInt());
			lp.readNextLine();

			try
			{

				tilesSet[static_cast<TileType>(idTile)] = Tile(new AnimatedSprite(pSL->loadSpriteFromFile(GFX_TILES_PATH + m_themeName + std::string("/") + spriteName), spriteSize, spriteDuration),
					name,
					defence,
					isRoad,
					isBridge,
					isRiver,
					isSea,
					isBeach,
					isBuilding,isHQ,
					needBackground,
					cityLife);
			}
			catch (ConstructionFailedException& cfe)
			{
				LError << cfe.what();
				return false;
			}
		}
	}
	catch (FileNotOpenedException fnoe)
	{
		LError << fnoe.what();
		return false;
	}

	return true;
}

bool Map :: loadUnitSet(NE::SpriteLoader* const pSL)
{
	LDebug << "Map :: loadUnitSet ( " << m_themeName.c_str() << ")";

	// Need reading of the file
	std::string unitSetPath = UNITSET_PATH + m_themeName + std::string(".oawus");

	try
	{
		LineParser lp(unitSetPath);

		for ( unsigned int i = UT_R_INFANTRY ; i < UT_END_LIST ; i++ )
		{
			unsigned int idTile = static_cast<unsigned int>(lp.getInt());
			lp.readNextLine();
			if ( i != idTile )
			{
				LWarning << "The tileset does not have sprite is good orger -> Received: " << idTile << " ; Expected: " << i;
			}
			std::string name = lp.getLine();
			lp.readNextLine();
			std::string spriteName = lp.getLine();
			lp.readNextLine();
			USize2 spriteSize = lp.getUSize2();
			lp.readNextLine();
			int spriteDuration = lp.getInt();
			lp.readNextLine();
			unsigned int category = static_cast<unsigned int>(lp.getInt());
			lp.readNextLine();
			unsigned int targetCategory = static_cast<unsigned int>(lp.getInt());
			lp.readNextLine();
			unsigned int movement = static_cast<unsigned int>(lp.getInt());
			lp.readNextLine();
			unsigned int fuel = static_cast<unsigned int>(lp.getInt());
			lp.readNextLine();
			unsigned int fuelConsumption = static_cast<unsigned int>(lp.getInt());
			lp.readNextLine();
			unsigned int ammo = static_cast<unsigned int>(lp.getInt());
			lp.readNextLine();
			unsigned int maxLife = static_cast<unsigned int>(lp.getInt());
			lp.readNextLine();
			unsigned int price = static_cast<unsigned int>(lp.getInt());
			lp.readNextLine();

			try
			{

				unitsSet[static_cast<UnitType>(idTile)] = UnitTemplate(new AnimatedSprite(pSL->loadSpriteFromFile(GFX_UNITS_PATH + m_themeName + std::string("/") + spriteName), spriteSize, spriteDuration),
					name,
					category,
					targetCategory,
					movement,
					fuel,
					fuelConsumption,
					ammo,
					maxLife,price
					);
			}
			catch (ConstructionFailedException& cfe)
			{
				LError << cfe.what();
				return false;
			}
		}
	}
	catch (FileNotOpenedException fnoe)
	{
		LError << fnoe.what();
		return false;
	}

	return true;
}

bool Map :: loadGraphics(NE::SpriteLoader* const pSL)
{
	LDebug << "Map :: loadGraphics";

	if ( loadTileSet(pSL) == false || loadUnitSet(pSL) == false )
	{
		return false;
	}

	return true;
}

bool Map :: parser(NE::SpriteLoader* const pSL, const std::string& fileName)
{
	std::string theme = "";
	unsigned int mapLineCounter = 0;
	unsigned int unitMapLineCounter = 0;
	bool error = false;

	LineParser lp(fileName);

	LDebug << "Map :: parser '" << fileName.c_str() << "'";

	do
	{
		if ( lp.getLineNumber() == 1 )
		{
			m_themeName = lp.getLine();

			LDebug << "Theme: " << m_themeName.c_str();

			if ( loadGraphics(pSL) == false )
			{
				LError << "Error to load the graphics";
				error = true;
			}
		}
		else if ( lp.getLineNumber() == 2 )
		{
			IVec2 size = lp.getIVec2();

			this->width = size.x;
			this->height = size.y;

			if ( this->width != 0 || this->height != 0 )	// If it looks correct (we can add a maximum size... to be safer)
			{
				map = new TileType*[this->height];
				if ( map == NULL )
				{
					LError << "Error to allocate memory for the map! (at height)";
					error = true;
				}
				else
				{
					for ( unsigned int y = 0 ; y < this->height ; y++ )
					{
						map[y] = new TileType[this->width];
						if ( map[y] == NULL )
						{
							LError << "Error to allocate memory for the map! (at width (" << y << "))";
							error = true;
						}
					}
				}

				// Allocation of the unit map
				unitViewMap = new UnitType*[this->height];
				if ( unitViewMap == NULL )
				{
					LError << "Error to allocate memory for the unitMap! (at height)";
					error = true;
				}
				else
				{
					for ( unsigned int y = 0 ; y < this->height ; y++ )
					{
						unitViewMap[y] = new UnitType[this->width];
						if ( unitViewMap[y] == NULL )
						{
							LError << "Error to allocate memory for the unitMap! (at width (" << y << "))";
							error = true;
						}
					}
				}
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
			int tileType = -1;

			mapLineCounter++;

			// We are reading one line, by one
			for ( unsigned int x = 0 ; x < this->width ; x++ )
			{
				ss >> tileType;
				if ( tileType != -1 )
				{
					if ( tileType < TT_END_LIST )
					{
						map[lp.getLineNumber()-3][x] = static_cast<TileType>(tileType);
					}
					else
					{
						LWarning << "Data in the map invalid (" << tileType << ")";
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
			int unitType = -42;

			unitMapLineCounter++;

			// We are reading one line, by one
			for ( unsigned int x = 0 ; x < this->width ; x++ )
			{
				ss >> unitType;
				if ( unitType != -42 )
				{
					if ( unitType < UT_END_LIST )
					{
						unitViewMap[lp.getLineNumber()-(3+this->height)][x] = static_cast<UnitType>(unitType);
					}
					else
					{
						LWarning << "Data in the map invalid (" << unitType << ")";
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
			unsigned int yOffset = tilesSet[map[y][x]].pASprite->getSize().height - TILE_DEFAULT_HEIGHT;

			// Draw the background sprite ( Plain )
			if ( tilesSet[map[y][x]].needBackground )
			{
				bResult &= tilesSet[TT_Plain].pASprite->draw(r,tilePos,0);
			}

			// Apply offset
			tilePos.y -= yOffset;

			bResult &= tilesSet[map[y][x]].pASprite->draw(r,tilePos,time);
			
			// Move on the right
			tilePos.x += tilesSet[map[y][x]].pASprite->getSize().width;

			// Remove offset ( to not affect other sprite )
			tilePos.y += yOffset;
		}

		tilePos.y += TILE_DEFAULT_HEIGHT;
	}

	return true;
}

TileType Map :: getTileType(const UVec2& position)const
{
#ifdef VERBOSE
	LDebug << "Map :: getTileType " << position;
#endif

	if ( position.x < this->width && position.y < this->height )
	{
		// The [] operator is not const...
		return map[position.y][position.x];
	}
	else
	{
		return TT_Invalid;
	}
}

Tile Map :: getTile(const UVec2& position)const
{
#ifdef VERBOSE
	LDebug << "Map :: getTile " << position;
#endif

 	if ( position.x < this->width && position.y < this->height )
	{
		// The [] operator is not const...
		return tilesSet.find(map[position.y][position.x])->second;
	}
	else
	{
		return Tile();
	}
}

Tile Map :: getTile(const TileType& tt)const
{
#ifdef VERBOSE
	LDebug << "Map :: getTile " << tt;
#endif
	std::map<TileType, Tile>::const_iterator it = tilesSet.find(tt);

 	if ( it != tilesSet.end() )
	{
		// The [] operator is not const...
		return it->second;;
	}
	else
	{
		return Tile();
	}
}

UnitType Map :: getUnitType(const UVec2& position)const
{
#ifdef VERBOSE
	LDebug << "Map :: getUnit " << position;
#endif

	if ( position.x < this->width && position.y < this->height )
	{
		return unitViewMap[position.y][position.x];
	}
	else
	{
		return UT_NO_UNIT;
	}
}

UnitTemplate Map :: getUnitTemplate(const UVec2& position)const
{
#ifdef VERBOSE
	LDebug << "Map :: getUnit " << position;
#endif

	if ( position.x < this->width && position.y < this->height )
	{
		return unitsSet.find(unitViewMap[position.y][position.x])->second;
	}
	else
	{
		return UnitTemplate();
	}
}

UnitTemplate Map :: getUnitTemplate(const UnitType ut)const
{
#ifdef VERBOSE
	LDebug << "Map :: getUnit " << ut;
#endif
	std::map<UnitType, UnitTemplate>::const_iterator it = unitsSet.find(ut);

 	if ( it != unitsSet.end() )
	{
		// The [] operator is not const...
		return it->second;;
	}
	else
	{
		return UnitTemplate();
	}
}

AnimatedSprite* Map :: getAssociatedSprite(const TileType type)
{
	if ( tilesSet.find(type) == tilesSet.end() )
	{
		return NULL;
	}

	return tilesSet[type].pASprite;
}

AnimatedSprite* Map :: getAssociatedSprite(const UnitType type)
{
	if ( unitsSet.find(type) == unitsSet.end() )
	{
		return NULL;
	}

	return unitsSet[type].pASprite;
}

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
