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

#include "Tile.h"
#include "Unit.h"

#include "../Engine/Renderer.h"
#include "../Engine/ResourcesManager/SpriteManager.h"
#include "../Engine/AnimatedSprite.h"

#include "Camera.h"

#include "../Types/Vec2.h"

#include "../Utils/LineParser.h"
#include "../Utils/Logger.h"
#include "../Utils/Scaler.h"
#include "../globals.h"

Map :: Map(SpriteManager& sm, const std::string& fileName)
	:width(0),height(0),map(NULL),valid(false)
{
	valid = this->parser(sm,fileName);

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
	for ( std::map<UnitType, Unit>::iterator itUnit = unitsSet.begin() ; itUnit != unitsSet.end() ; ++itUnit)
	{
		delete itUnit->second.pASprite;
	}
	unitsSet.clear();

	// Delete the unit map
	for ( unsigned int y = 0 ; y < this->height ; y++ )
	{
		delete[] unitMap[y];
	}

	delete[] unitMap;

	// Delete the map
	for ( unsigned int y = 0 ; y < this->height ; y++ )
	{
		delete[] map[y];
	}

	delete[] map;

	LDebug << "Map deleted";
}

void Map :: loadTileSet(SpriteManager& sm, const std::string& theme)
{
	LDebug << "Map :: loadTileSet ( " << theme.c_str() << ")";

	// Need reading of the file
	std::string tileSetPath = TILESET_PATH + theme + std::string(".oawts");

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
		IVec2 spriteSize = lp.getIVec2();
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

		tilesSet[static_cast<TileType>(idTile)] = Tile(new AnimatedSprite(sm,GFX_TILES_PATH + theme + std::string("/") + spriteName, spriteSize.x , spriteSize.y, spriteDuration, true),
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
}

void Map :: loadUnitSet(SpriteManager& sm, const std::string& theme)
{
	LDebug << "Map :: loadUnitSet ( " << theme.c_str() << ")";

	// Need reading of the file
	std::string unitSetPath = UNITSET_PATH + theme + std::string(".oawus");

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
		IVec2 spriteSize = lp.getIVec2();
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

		unitsSet[static_cast<UnitType>(idTile)] = Unit(new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/") + spriteName, spriteSize.x , spriteSize.y, spriteDuration, true),
			name,
			category,
			targetCategory,
			movement,
			fuel,
			fuelConsumption,
			ammo,
			maxLife);
	}
}

void Map :: loadGraphics(SpriteManager& sm, const std::string& theme)
{
	LDebug << "Map :: loadGraphics ( " << theme.c_str() << ")";

	loadTileSet(sm,theme);
	loadUnitSet(sm,theme);
}

bool Map :: parser(SpriteManager& sm, const std::string& fileName)
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
			theme = lp.getLine();

			LDebug << "Theme: " << theme.c_str();

				loadGraphics(sm,theme); // TODO : Error checking has to be added ... more ... this line has to move in the constructor
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
				unitMap = new UnitType*[this->height];
				if ( unitMap == NULL )
				{
					LError << "Error to allocate memory for the unitMap! (at height)";
					error = true;
				}
				else
				{
					for ( unsigned int y = 0 ; y < this->height ; y++ )
					{
						unitMap[y] = new UnitType[this->width];
						if ( unitMap[y] == NULL )
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
						unitMap[lp.getLineNumber()-(3+this->height)][x] = static_cast<UnitType>(unitType);
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

bool Map :: draw(const Renderer& r, const Camera& c, const unsigned int time)
{
	UVec2 cameraPosition = c.getPosition();
	UVec2 mapOffset = Scaler::getOffset();
	IVec2 tilePos(0,mapOffset.y);

	LDebug << "Map :: draw";

	// The camera is an offset of the Map drawing
	// For each lines
	for ( unsigned int y = cameraPosition.y ; y < MAP_MIN_HEIGHT+cameraPosition.y ; y++ )
	{
		tilePos.x = mapOffset.x;
		// For each columns
		for ( unsigned int x = cameraPosition.x ; x < MAP_MIN_WIDTH+cameraPosition.x ; x++ )
		{
			// Calculation of the offset for sprite with higher size than normal Tile (e.g.: Mountains)
			unsigned int yOffset = tilesSet[map[y][x]].pASprite->getHeight() - (static_cast<unsigned int>(Scaler::getYScaleFactor() * TILE_DEFAULT_HEIGHT));

			// Draw the background sprite ( Plain )
			if ( tilesSet[map[y][x]].needBackground )
			{
				r.drawTile(*tilesSet[TT_Plain].pASprite,tilePos);
			}

			// Apply offset
			tilePos.y -= yOffset;

			r.drawTile(*tilesSet[map[y][x]].pASprite,tilePos,time);
			if ( unitMap[y][x] != UT_NO_UNIT )	// If we have a unit
			{
				r.drawTile(*unitsSet[unitMap[y][x]].pASprite,tilePos,time);
			}
			tilePos.x += tilesSet[map[y][x]].pASprite->getWidth();

			// Remove offset ( to not affect other sprite )
			tilePos.y += yOffset;
		}

		// To put 0 here, can be a bit dangerous
		tilePos.y += (static_cast<unsigned int>(Scaler::getYScaleFactor() * TILE_DEFAULT_HEIGHT));
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
		return unitMap[position.y][position.x];
	}
	else
	{
		return UT_NO_UNIT;
	}
}

Unit Map :: getUnit(const UVec2& position)const
{
#ifdef VERBOSE
	LDebug << "Map :: getUnit " << position;
#endif

	if ( position.x < this->width && position.y < this->height )
	{
		return unitsSet.find(unitMap[position.y][position.x])->second;
	}
	else
	{
		return Unit();
	}
}

Unit Map :: getUnit(const UnitType ut)const
{
#ifdef VERBOSE
	LDebug << "Map :: getUnit " << ut;
#endif
	std::map<UnitType, Unit>::const_iterator it = unitsSet.find(ut);

 	if ( it != unitsSet.end() )
	{
		// The [] operator is not const...
		return it->second;;
	}
	else
	{
		return Unit();
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