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
	// Delete the Tiles used my the map
	for ( std::map<TileType, Tile>::iterator itTile = tilesSet.begin() ; itTile != tilesSet.end() ; ++itTile)
	{
		delete itTile->second.pASprite;
	}
	tilesSet.clear();

	// Delete the unit map
	for ( unsigned int y = 0 ; y < this->height ; y++ )
	{
		for ( unsigned int x = 0 ; x < this->width ; x++ )
		{
			delete unitMap[y][x];
		}

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

}

void Map :: loadGraphics(SpriteManager& sm, const std::string& theme)
{
	LDebug << "Map :: loadGraphics ( " << theme.c_str() << ")";

	loadTileSet(sm,theme);
	// Units

	unitsASprite[UT_R_INFANTRY] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/r_infantry.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_R_BAZOOKA] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/r_bazooka.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_R_RECON] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/r_recon.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_R_TANK] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/r_tank.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_R_TANKM] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/r_tankm.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_R_NEOTANK] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/r_neo.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_R_APC] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/r_apc.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_R_ARTILLERY] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/r_artillery.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_R_ROCKETS] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/r_rockets.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_R_ANTIAIR] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/r_aair.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_R_MISSILES] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/r_missiles.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_R_LANDER] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/r_lander.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_R_SUB] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/r_sub.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_R_BOMBERSHIP] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/r_bship.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_R_CRUISER] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/r_cruiser.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_R_TCOPTER] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/r_tcopter.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_R_COPTER] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/r_copter.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_R_FIGHTER] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/r_fighter.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_R_BOMBER] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/r_bomber.png"),32,32,NORMAL_SPEED,true);

	unitsASprite[UT_B_INFANTRY] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/b_infantry.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_B_BAZOOKA] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/b_bazooka.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_B_RECON] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/b_recon.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_B_TANK] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/b_tank.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_B_TANKM] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/b_tankm.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_B_NEOTANK] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/b_neo.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_B_APC] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/b_apc.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_B_ARTILLERY] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/b_artillery.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_B_ROCKETS] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/b_rockets.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_B_ANTIAIR] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/b_aair.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_B_MISSILES] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/b_missiles.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_B_LANDER] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/b_lander.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_B_SUB] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/b_sub.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_B_BOMBERSHIP] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/b_bship.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_B_CRUISER] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/b_cruiser.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_B_TCOPTER] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/b_tcopter.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_B_COPTER] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/b_copter.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_B_FIGHTER] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/b_fighter.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_B_BOMBER] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/b_bomber.png"),32,32,NORMAL_SPEED,true);

	unitsASprite[UT_G_INFANTRY] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/g_infantry.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_G_BAZOOKA] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/g_bazooka.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_G_RECON] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/g_recon.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_G_TANK] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/g_tank.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_G_TANKM] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/g_tankm.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_G_NEOTANK] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/g_neo.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_G_APC] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/g_apc.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_G_ARTILLERY] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/g_artillery.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_G_ROCKETS] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/g_rockets.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_G_ANTIAIR] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/g_aair.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_G_MISSILES] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/g_missiles.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_G_LANDER] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/g_lander.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_G_SUB] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/g_sub.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_G_BOMBERSHIP] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/g_bship.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_G_CRUISER] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/g_cruiser.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_G_TCOPTER] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/g_tcopter.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_G_COPTER] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/g_copter.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_G_FIGHTER] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/g_fighter.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_G_BOMBER] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/g_bomber.png"),32,32,NORMAL_SPEED,true);

	unitsASprite[UT_Y_INFANTRY] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/y_infantry.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_Y_BAZOOKA] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/y_bazooka.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_Y_RECON] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/y_recon.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_Y_TANK] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/y_tank.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_Y_TANKM] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/y_tankm.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_Y_NEOTANK] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/y_neo.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_Y_APC] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/y_apc.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_Y_ARTILLERY] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/y_artillery.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_Y_ROCKETS] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/y_rockets.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_Y_ANTIAIR] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/y_aair.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_Y_MISSILES] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/y_missiles.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_Y_LANDER] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/y_lander.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_Y_SUB] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/y_sub.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_Y_BOMBERSHIP] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/y_bship.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_Y_CRUISER] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/y_cruiser.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_Y_TCOPTER] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/y_tcopter.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_Y_COPTER] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/y_copter.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_Y_FIGHTER] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/y_fighter.png"),32,32,NORMAL_SPEED,true);
	unitsASprite[UT_Y_BOMBER] = new AnimatedSprite(sm,GFX_UNITS_PATH + theme + std::string("/y_bomber.png"),32,32,NORMAL_SPEED,true);
}

bool Map :: parser(SpriteManager& sm, const std::string& fileName)
{
	std::ifstream file;
	std::string line;
	std::string theme = "";
	unsigned int lineCounter = 0;
	unsigned int mapLineCounter = 0;
	unsigned int unitMapLineCounter = 0;
	bool error = false;

	LDebug << "Map :: parser '" << fileName.c_str() << "'";

	file.open(fileName.c_str(),std::ios::in);
    if ( file.is_open() == false )
    {
		LWarning << "Failed to open: '" << fileName.c_str() << "'";
		return false;
	}

	while ( !file.eof() && !error )
    {
        std::getline(file,line);
		if ( line[0] != '#' && line.size() != 0 ) // If the line is not empty, or is not a comment
        {
            std::stringstream ss(line);

			if ( lineCounter == 0 )
			{
				ss >> theme;

				LDebug << "Theme: " << theme.c_str();

				loadGraphics(sm,theme); // TODO : Error checking has to be added ... more ... this line has to move in the constructor
			}
			else if ( lineCounter == 1 )
			{
				ss >> this->width >> this->height;

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
					unitMap = new Unit**[this->height];
					if ( unitMap == NULL )
					{
						LError << "Error to allocate memory for the unitMap! (at height)";
						error = true;
					}
					else
					{
						for ( unsigned int y = 0 ; y < this->height ; y++ )
						{
							unitMap[y] = new Unit*[this->width];
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
			else if ( lineCounter >= 2 && lineCounter < 2+this->height ) // For all lines representating the map
			{
				mapLineCounter++;

				// We are reading one line, by one
				for ( unsigned int x = 0 ; x < this->width ; x++ )
				{
					int tileType = -1;
					ss >> tileType;
					if ( tileType != -1 )
					{
						if ( tileType < TT_END_LIST )
						{
							map[lineCounter-2][x] = static_cast<TileType>(tileType);
						}
						else
						{
							LWarning << "Data in the map invalid (" << tileType << ")";
							error = true;
						}	
					}
					else
					{
						LError << "Fail to read the tile type @ " << x << ";" << lineCounter-2;
						error = true;
					}
				}
			}
			else if ( lineCounter >= 2+this->height && lineCounter < 2+this->height*2 )	// For the unit map
			{
				unitMapLineCounter++;

				// We are reading one line, by one
				for ( unsigned int x = 0 ; x < this->width ; x++ )
				{
					int unitType = -1;
					ss >> unitType;
					if ( unitType != -1 )
					{
						if ( unitType < UT_END_LIST )
						{
							unitMap[lineCounter-(2+this->height)][x] = UnitFactory(static_cast<UnitType>(unitType));
						}
						else
						{
							LWarning << "Data in the map invalid (" << unitType << ")";
							error = true;
						}	
					}
					else
					{
						LError << "Fail to read the tile type @ " << x << ";" << lineCounter-(2+this->height);
						error = true;
					}
				}
			}
            
            lineCounter++;
        }
    }

	if ( mapLineCounter != this->height )
	{
		LError << "The number of line declared in the size of the map doesn't correspond to the number of lines in the map data (" << mapLineCounter << ")";
		error = true;
	}

	file.close();

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
			if ( unitMap[y][x]->getType() != UT_NO_UNIT )	// If we have a unit
			{
				r.drawTile(*unitsASprite[unitMap[y][x]->getType()],tilePos,time);
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
		return tilesSet.find(map[position.y][position.x])->second;;
	}
	else
	{
		return Tile();
	}
}

Tile Map :: getTile(const TileType& tt)const
{
#ifdef VERBOSE
	LDebug << "Map :: getTile " << position;
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

Unit* Map :: getUnit(const UVec2& position)const
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
		return NULL;
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
	if ( unitsASprite.find(type) == unitsASprite.end() )
	{
		return NULL;
	}

	return unitsASprite[type];
}