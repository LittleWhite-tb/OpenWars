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

#include "../Engine/Renderer.h"
#include "../Engine/ResourcesManager/SpriteManager.h"
#include "../Engine/AnimatedSprite.h"

#include "Camera.h"

#include "../Types/Vec2.h"

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
	for ( unsigned int y = 0 ; y < this->height ; y++ )
	{
		delete[] map[y];
	}

	delete[] map;

	LDebug << "Map deleted";
}

void Map :: loadGraphics(SpriteManager& sm, const std::string& theme)
{
	LDebug << "Map :: loadGraphics ( " << theme.c_str() << ")";

	tilesASprite[TT_Plain] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/plain.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Tree] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/tree.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Mountain_1] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/mountain1.png",32,32,NORMAL_SPEED,true);
	// The Mountain2 has a irregular size!
	tilesASprite[TT_Mountain_2] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/mountain2.png",32,42,NORMAL_SPEED,true);
	tilesASprite[TT_Beach_TL] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/beach_tl.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Beach_TR] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/beach_tr.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Beach_BL] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/beach_bl.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Beach_BR] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/beach_br.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Beach_EL] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/beach_el.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Beach_ER] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/beach_er.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Beach_ET] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/beach_et.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Beach_EB] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/beach_eb.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Beach_T] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/beach_t.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Beach_B] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/beach_b.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Beach_L] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/beach_l.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Beach_R] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/beach_r.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Bridge_H] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/bridge_h.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Bridge_V] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/bridge_v.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_River_H] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/river_h.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_River_V] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/river_v.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_River_T_L] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/river_t_l.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_River_T_R] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/river_t_r.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_River_T_T] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/river_t_t.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_River_T_B] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/river_t_b.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_River_TL] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/river_tl.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_River_TR] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/river_tr.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_River_BL] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/river_bl.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_River_BR] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/river_br.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_River_See_T] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/river2see_t.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_River_See_B] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/river2see_b.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_River_See_L] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/river2see_l.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_River_See_R] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/river2see_r.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_River_X] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/river_x.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Road_H] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/road_h.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Road_V] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/road_v.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Road_TL] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/road_tl.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Road_TR] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/road_tr.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Road_BL] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/road_bl.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Road_BR] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/road_br.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Road_T_L] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/road_t_l.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Road_T_B] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/road_t_b.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Road_T_R] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/road_t_r.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Road_T_T] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/road_t_t.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Road_X] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/road_x.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Red_HQ] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/r_hq.png",32,62,NORMAL_SPEED,true);
	tilesASprite[TT_Red_Factory] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/r_factory.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Red_Port] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/r_port.png",32,44,NORMAL_SPEED,true);
	tilesASprite[TT_Red_Airport] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/r_airport.png",32,36,NORMAL_SPEED,true);
	tilesASprite[TT_Red_City] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/r_city.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Blue_HQ] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/b_hq.png",32,64,NORMAL_SPEED,true);
	tilesASprite[TT_Blue_Factory] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/b_factory.png",32,40,NORMAL_SPEED,true);
	tilesASprite[TT_Blue_Port] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/b_port.png",32,42,NORMAL_SPEED,true);
	tilesASprite[TT_Blue_Airport] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/b_airport.png",32,36,NORMAL_SPEED,true);
	tilesASprite[TT_Blue_City] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/b_city.png",32,40,NORMAL_SPEED,true);
	tilesASprite[TT_Green_HQ] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/g_hq.png",32,52,NORMAL_SPEED,true);
	tilesASprite[TT_Green_Factory] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/g_factory.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Green_Port] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/g_port.png",32,42,NORMAL_SPEED,true);
	tilesASprite[TT_Green_Airport] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/g_airport.png",32,36,NORMAL_SPEED,true);
	tilesASprite[TT_Green_City] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/g_city.png",32,40,NORMAL_SPEED,true);
	tilesASprite[TT_Yellow_HQ] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/y_hq.png",32,60,NORMAL_SPEED,true);
	tilesASprite[TT_Yellow_Factory] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/y_factory.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Yellow_Port] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/y_port.png",32,44,NORMAL_SPEED,true);
	tilesASprite[TT_Yellow_Airport] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/y_airport.png",32,36,NORMAL_SPEED,true);
	tilesASprite[TT_Yellow_City] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/y_city.png",32,40,NORMAL_SPEED,true);
	tilesASprite[TT_Neutral_Factory] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/n_factory.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Neutral_Port] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/n_port.png",32,42,NORMAL_SPEED,true);
	tilesASprite[TT_Neutral_Airport] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/n_airport.png",32,36,NORMAL_SPEED,true);
	tilesASprite[TT_Neutral_City] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/n_city.png",32,40,NORMAL_SPEED,true);
	tilesASprite[TT_See] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/see.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_See_TL] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/see_tl.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_See_TR] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/see_tr.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_See_BL] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/see_bl.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_See_BR] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/see_br.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Reef] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/reef.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Coast] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/coast.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Coast_ET] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/coast_et.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Coast_EB] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/coast_eb.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Coast_EL] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/coast_el.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Coast_ER] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/coast_er.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Coast_TL] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/coast_tl.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Coast_TR] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/coast_tr.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Coast_BL] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/coast_bl.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Coast_BR] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/coast_br.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Coast_RTL] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/coast_rtl.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Coast_RTR] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/coast_rtr.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Coast_RBL] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/coast_rbl.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Coast_RBR] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/coast_rbr.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Coast_L] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/coast_l.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Coast_R] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/coast_r.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Coast_B] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/coast_b.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Coast_T] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/coast_t.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Coast_H] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/coast_h.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Coast_V] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/coast_v.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Coast_T_L] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/coast_t_l.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Coast_T_B] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/coast_t_b.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Coast_T_R] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/coast_t_r.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Coast_T_T] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/coast_t_t.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Coast_T_TL] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/coast_t_tl.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Coast_T_TR] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/coast_t_tr.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Coast_T_BL] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/coast_t_bl.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Coast_T_BR] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/coast_t_br.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Coast_T_LT] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/coast_t_lt.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Coast_T_RT] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/coast_t_rt.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Coast_T_LB] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/coast_t_lb.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Coast_T_RB] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/coast_t_rb.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Coast_X] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/coast_x.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Coast_XL] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/coast_xl.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Coast_XR] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/coast_xr.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Coast_XT] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/coast_xt.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Coast_XB] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/coast_xb.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Coast_XTL] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/coast_xtl.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Coast_XTR] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/coast_xtr.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Coast_XBL] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/coast_xbl.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Coast_XBR] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/coast_xbr.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Coast_XTLBR] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/coast_xtlbr.png",32,32,NORMAL_SPEED,true);
	tilesASprite[TT_Coast_XBLTR] = new AnimatedSprite(sm,GFX_TILES_PATH + theme + "/coast_xbltr.png",32,32,NORMAL_SPEED,true);
}

bool Map :: parser(SpriteManager& sm, const std::string& fileName)
{
	std::ifstream file;
	std::string line;
	std::string theme = "";
	unsigned int lineCounter = 0;
	unsigned int mapLineCounter = 0;
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
					map = new Tile*[this->height];
					if ( map == NULL )
					{
						LError << "Error to allocate memory for the map! (at height)";
						error = true;
					}
					else
					{
						for ( unsigned int y = 0 ; y < this->height ; y++ )
						{
							map[y] = new Tile[this->width];
							if ( map[y] == NULL )
							{
								LError << "Error to allocate memory for the map! (at width (" << y << "))";
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
							map[lineCounter-2][x] = TileFactory(static_cast<TileType>(tileType));
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
	IVec2 tilePos(0,0);

	LDebug << "Map :: draw";

	// The camera is an offset of the Map drawing
	// For each lines
	for ( unsigned int y = cameraPosition.y ; y < MAP_MIN_HEIGHT+cameraPosition.y ; y++ )
	{
		tilePos.x = 0;
		// For each columns
		for ( unsigned int x = cameraPosition.x ; x < MAP_MIN_WIDTH+cameraPosition.x ; x++ )
		{
			// Calculation of the offset for sprite with higher size than normal Tile (e.g.: Mountains)
			unsigned int yOffset = tilesASprite[map[y][x].tileType]->getHeight() - (static_cast<unsigned int>(Scaler::getYScaleFactor() * TILE_DEFAULT_HEIGHT));

			// Draw the background sprite ( Plain )
			if ( map[y][x].needBackground )
			{
				r.drawTile(*tilesASprite[TT_Plain],tilePos);
			}

			// Apply offset
			tilePos.y -= yOffset;

			r.drawTile(*tilesASprite[map[y][x].tileType],tilePos,time);
			tilePos.x += tilesASprite[map[y][x].tileType]->getWidth();

			// Remove offset ( to not affect other sprite )
			tilePos.y += yOffset;
		}

		// To put 0 here, can be a bit dangerous
		tilePos.y += tilesASprite[map[y][0].tileType]->getHeight();
	}

	return true;
}

Tile Map :: getTile(const UVec2& position)const
{
	LDebug << "Map :: getTile " << position;

	if ( position.x < this->width && position.y < this->height )
	{
		return map[position.y][position.x];
	}
	else
	{
		return Tile();
	}
}