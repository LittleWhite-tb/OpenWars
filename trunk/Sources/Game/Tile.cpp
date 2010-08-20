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

#include "tile.h"

#include <cassert>

#include "../Engine/AnimatedSprite.h"
#include "../Engine/ResourcesManager/SpriteManager.h"

#include "../globals.h"

Tile :: ~Tile(void)
{
	delete pAnimation;
}

AnimatedSprite* getTileSurface(SpriteManager& sm, const std::string& themeName, const TileType tileType)
{
	std::string folderName = std::string(GFX_TILES_PATH) + themeName + std::string("/");
	AnimatedSprite* pAS = NULL;

	switch(tileType)
	{
		case TT_Plain:
			pAS = new AnimatedSprite(sm,folderName + std::string("plain.png"),32,32,NORMAL_SPEED);
			break;
		case TT_Tree:
			pAS = new AnimatedSprite(sm,folderName + std::string("tree.png"),32,32,NORMAL_SPEED);
			break;
		case TT_Mountain_1:
			pAS = new AnimatedSprite(sm,folderName + std::string("mountain1.png"),32,32,NORMAL_SPEED);
			break;
		case TT_Mountain_2:
			pAS = new AnimatedSprite(sm,folderName + std::string("mountain2.png"),32,32,NORMAL_SPEED);
			break;
		case TT_Beach_TL:
			pAS = new AnimatedSprite(sm,folderName + std::string("beach_tl.png"),32,32,NORMAL_SPEED);
			break;
		case TT_Beach_TR:
			pAS = new AnimatedSprite(sm,folderName + std::string("beach_tr.png"),32,32,NORMAL_SPEED);
			break;
		case TT_Beach_BL:
			pAS = new AnimatedSprite(sm,folderName + std::string("beach_bl.png"),32,32,NORMAL_SPEED);
			break;
		case TT_Beach_BR:
			pAS = new AnimatedSprite(sm,folderName + std::string("beach_br.png"),32,32,NORMAL_SPEED);
			break;
		case TT_Beach_H:
			pAS = new AnimatedSprite(sm,folderName + std::string("beach_h.png"),32,32,NORMAL_SPEED);
			break;
		case TT_Beach_V:
			pAS = new AnimatedSprite(sm,folderName + std::string("beach_v.png"),32,32,NORMAL_SPEED);
			break;
		case TT_Beach_T_L:
			pAS = new AnimatedSprite(sm,folderName + std::string("beach_t_l.png"),32,32,NORMAL_SPEED);
			break;
		case TT_Beach_T_R:
			pAS = new AnimatedSprite(sm,folderName + std::string("beach_t_r.png"),32,32,NORMAL_SPEED);
			break;
		case TT_Beach_T_T:
			pAS = new AnimatedSprite(sm,folderName + std::string("beach_t_t.png"),32,32,NORMAL_SPEED);
			break;
		case TT_Beach_T_B:
			pAS = new AnimatedSprite(sm,folderName + std::string("beach_t_b.png"),32,32,NORMAL_SPEED);
			break;
		case TT_Bridge_H:
			pAS = new AnimatedSprite(sm,folderName + std::string("bridge_h.png"),32,32,NORMAL_SPEED);
			break;
		case TT_Bridge_V:
			pAS = new AnimatedSprite(sm,folderName + std::string("bridge_v.png"),32,32,NORMAL_SPEED);
			break;
		case TT_River_H:
			pAS = new AnimatedSprite(sm,folderName + std::string("river_h.png"),32,32,NORMAL_SPEED);
			break;
		case TT_River_V:
			pAS = new AnimatedSprite(sm,folderName + std::string("river_v.png"),32,32,NORMAL_SPEED);
			break;
		case TT_River_T_L:
			pAS = new AnimatedSprite(sm,folderName + std::string("river_t_l.png"),32,32,NORMAL_SPEED);
			break;
		case TT_River_T_R:
			pAS = new AnimatedSprite(sm,folderName + std::string("river_t_r.png"),32,32,NORMAL_SPEED);
			break;
		case TT_River_T_T:
			pAS = new AnimatedSprite(sm,folderName + std::string("river_t_t.png"),32,32,NORMAL_SPEED);
			break;
		case TT_River_T_B:
			pAS = new AnimatedSprite(sm,folderName + std::string("river_t_b.png"),32,32,NORMAL_SPEED);
			break;
		case TT_River_TL:
			pAS = new AnimatedSprite(sm,folderName + std::string("river_tl.png"),32,32,NORMAL_SPEED);
			break;
		case TT_River_TR:
			pAS = new AnimatedSprite(sm,folderName + std::string("river_tr.png"),32,32,NORMAL_SPEED);
			break;
		case TT_River_BL:
			pAS = new AnimatedSprite(sm,folderName + std::string("river_bl.png"),32,32,NORMAL_SPEED);
			break;
		case TT_River_BR:
			pAS = new AnimatedSprite(sm,folderName + std::string("river_br.png"),32,32,NORMAL_SPEED);
			break;
		case TT_Road_H:
			pAS = new AnimatedSprite(sm,folderName + std::string("road_h.png"),32,32,NORMAL_SPEED);
			break;
		case TT_Road_V:
			pAS = new AnimatedSprite(sm,folderName + std::string("road_v.png"),32,32,NORMAL_SPEED);
			break;
		case TT_Road_T_L:
			pAS = new AnimatedSprite(sm,folderName + std::string("road_t_l.png"),32,32,NORMAL_SPEED);
			break;
		case TT_Road_T_B:
			pAS = new AnimatedSprite(sm,folderName + std::string("road_t_b.png"),32,32,NORMAL_SPEED);
			break;
		case TT_Road_T_R:
			pAS = new AnimatedSprite(sm,folderName + std::string("road_t_r.png"),32,32,NORMAL_SPEED);
			break;
		case TT_Road_T_T:
			pAS = new AnimatedSprite(sm,folderName + std::string("road_t_t.png"),32,32,NORMAL_SPEED);
			break;
		case TT_Road_X:
			pAS = new AnimatedSprite(sm,folderName + std::string("road_x.png"),32,32,NORMAL_SPEED);
			break;
		case TT_Red_HQ:
			pAS = new AnimatedSprite(sm,folderName + std::string("red_hq.png"),32,32,NORMAL_SPEED);
			break;
		case TT_Red_Factory:
			pAS = new AnimatedSprite(sm,folderName + std::string("red_factory.png"),32,32,NORMAL_SPEED);
			break;
		case TT_Red_Port:
			pAS = new AnimatedSprite(sm,folderName + std::string("red_port.png"),32,32,NORMAL_SPEED);
			break;
		case TT_Red_Airport:
			pAS = new AnimatedSprite(sm,folderName + std::string("red_airport.png"),32,32,NORMAL_SPEED);
			break;
		case TT_Red_City:
			pAS = new AnimatedSprite(sm,folderName + std::string("red_city.png"),32,32,NORMAL_SPEED);
			break;
		case TT_Blue_HQ:
			pAS = new AnimatedSprite(sm,folderName + std::string("blue_hq.png"),32,32,NORMAL_SPEED);
			break;
		case TT_Blue_Factory:
			pAS = new AnimatedSprite(sm,folderName + std::string("blue_factory.png"),32,32,NORMAL_SPEED);
			break;
		case TT_Blue_Port:
			pAS = new AnimatedSprite(sm,folderName + std::string("blue_port.png"),32,32,NORMAL_SPEED);
			break;
		case TT_Blue_Airport:
			pAS = new AnimatedSprite(sm,folderName + std::string("blue_airport.png"),32,32,NORMAL_SPEED);
			break;
		case TT_Blue_City:
			pAS = new AnimatedSprite(sm,folderName + std::string("blue_city.png"),32,32,NORMAL_SPEED);
			break;
		case TT_Green_HQ:
			pAS = new AnimatedSprite(sm,folderName + std::string("green_hq.png"),32,32,NORMAL_SPEED);
			break;
		case TT_Green_Factory:
			pAS = new AnimatedSprite(sm,folderName + std::string("green_factory.png"),32,32,NORMAL_SPEED);
			break;
		case TT_Green_Port:
			pAS = new AnimatedSprite(sm,folderName + std::string("green_port.png"),32,32,NORMAL_SPEED);
			break;
		case TT_Green_Airport:
			pAS = new AnimatedSprite(sm,folderName + std::string("green_airport.png"),32,32,NORMAL_SPEED);
			break;
		case TT_Green_City:
			pAS = new AnimatedSprite(sm,folderName + std::string("green_city.png"),32,32,NORMAL_SPEED);
			break;
		case TT_Yellow_HQ:
			pAS = new AnimatedSprite(sm,folderName + std::string("yellow_hq.png"),32,32,NORMAL_SPEED);
			break;
		case TT_Yellow_Factory:
			pAS = new AnimatedSprite(sm,folderName + std::string("yellow_factory.png"),32,32,NORMAL_SPEED);
			break;
		case TT_Yellow_Port:
			pAS = new AnimatedSprite(sm,folderName + std::string("yellow_port.png"),32,32,NORMAL_SPEED);
			break;
		case TT_Yellow_Airport:
			pAS = new AnimatedSprite(sm,folderName + std::string("yellow_airport.png"),32,32,NORMAL_SPEED);
			break;
		case TT_Yellow_City:
			pAS = new AnimatedSprite(sm,folderName + std::string("yellow_city.png"),32,32,NORMAL_SPEED);
			break;
		case TT_Neutral_Factory:
			pAS = new AnimatedSprite(sm,folderName + std::string("neutral_factory.png"),32,32,NORMAL_SPEED);
			break;
		case TT_Neutral_Port:
			pAS = new AnimatedSprite(sm,folderName + std::string("neutral_port.png"),32,32,NORMAL_SPEED);
			break;
		case TT_Neutral_Airport:
			pAS = new AnimatedSprite(sm,folderName + std::string("neutral_airport.png"),32,32,NORMAL_SPEED);
			break;
		case TT_Neutral_City:
			pAS = new AnimatedSprite(sm,folderName + std::string("neutral_city.png"),32,32,NORMAL_SPEED);
			break;
		case TT_River_See:
			pAS = new AnimatedSprite(sm,folderName + std::string("river_see.png"),32,32,NORMAL_SPEED);
			break;
		case TT_See:
			pAS = new AnimatedSprite(sm,folderName + std::string("see.png"),32,32,NORMAL_SPEED);
			break;
		case TT_Reef:
			pAS = new AnimatedSprite(sm,folderName + std::string("reef.png"),32,32,NORMAL_SPEED);
			break;
		case TT_Coast_TL:
			pAS = new AnimatedSprite(sm,folderName + std::string("coast_tl.png"),32,32,NORMAL_SPEED);
			break;
		case TT_Coast_TR:
			pAS = new AnimatedSprite(sm,folderName + std::string("coast_tr.png"),32,32,NORMAL_SPEED);
			break;
		case TT_Coast_BL:
			pAS = new AnimatedSprite(sm,folderName + std::string("coast_bl.png"),32,32,NORMAL_SPEED);
			break;
		case TT_Coast_BR:
			pAS = new AnimatedSprite(sm,folderName + std::string("coast_br.png"),32,32,NORMAL_SPEED);
			break;
		case TT_Coast_L:
			pAS = new AnimatedSprite(sm,folderName + std::string("coast_l.png"),32,32,NORMAL_SPEED);
			break;
		case TT_Coast_R:
			pAS = new AnimatedSprite(sm,folderName + std::string("coast_r.png"),32,32,NORMAL_SPEED);
			break;
		case TT_Coast_B:
			pAS = new AnimatedSprite(sm,folderName + std::string("coast_b.png"),32,32,NORMAL_SPEED);
			break;
		case TT_Coast_T:
			pAS = new AnimatedSprite(sm,folderName + std::string("coast_t.png"),32,32,NORMAL_SPEED);
			break;
		case TT_Coast_H:
			pAS = new AnimatedSprite(sm,folderName + std::string("coast_h.png"),32,32,NORMAL_SPEED);
			break;
		case TT_Coast_V:
			pAS = new AnimatedSprite(sm,folderName + std::string("coast_v.png"),32,32,NORMAL_SPEED);
			break;
		case TT_Coast_T_L:
			pAS = new AnimatedSprite(sm,folderName + std::string("coast_t_l.png"),32,32,NORMAL_SPEED);
			break;
		case TT_Coast_T_B:
			pAS = new AnimatedSprite(sm,folderName + std::string("coast_t_b.png"),32,32,NORMAL_SPEED);
			break;
		case TT_Coast_T_R:
			pAS = new AnimatedSprite(sm,folderName + std::string("coast_t_r.png"),32,32,NORMAL_SPEED);
			break;
		case TT_Coast_T_T:
			pAS = new AnimatedSprite(sm,folderName + std::string("coast_t_t.png"),32,32,NORMAL_SPEED);
			break;
		case TT_Coast_X:
			pAS = new AnimatedSprite(sm,folderName + std::string("coast_x.png"),32,32,NORMAL_SPEED);
			break;
	}

	return pAS;
}

unsigned char parseDefence(const TileType tileType)
{
	switch(tileType)
	{
		case TT_Beach_TL:
		case TT_Beach_TR:
		case TT_Beach_BL:
		case TT_Beach_BR:
		case TT_Beach_H:
		case TT_Beach_V:
		case TT_Beach_T_L:
		case TT_Beach_T_R:
		case TT_Beach_T_T:
		case TT_Beach_T_B:
		case TT_Bridge_H:
		case TT_Bridge_V:
		case TT_Coast_TL:
		case TT_Coast_TR:
		case TT_Coast_BL:
		case TT_Coast_BR:
		case TT_Coast_L:
		case TT_Coast_R:
		case TT_Coast_B:
		case TT_Coast_T:
		case TT_Coast_H:
		case TT_Coast_V:
		case TT_Coast_T_L:
		case TT_Coast_T_B:
		case TT_Coast_T_R:
		case TT_Coast_T_T:
		case TT_Coast_X:
		case TT_See:
		case TT_Road_H:
		case TT_Road_V:
		case TT_Road_T_L:
		case TT_Road_T_B:
		case TT_Road_T_R:
		case TT_Road_T_T:
		case TT_Road_X:
		case TT_River_H:
		case TT_River_V:
		case TT_River_T_L:
		case TT_River_T_R:
		case TT_River_T_T:
		case TT_River_T_B:
		case TT_River_TL:
		case TT_River_TR:
		case TT_River_BL:
		case TT_River_BR:
		case TT_River_See:
			return 0;
			break;
		case TT_Plain:
		case TT_Reef:
			return 1;
			break;
		case TT_Tree:
			return 2;
			break;
		case TT_Red_Factory:
		case TT_Red_Port:
		case TT_Red_Airport:
		case TT_Red_City:
		case TT_Blue_Factory:
		case TT_Blue_Port:
		case TT_Blue_Airport:
		case TT_Blue_City:
		case TT_Green_Factory:
		case TT_Green_Port:
		case TT_Green_Airport:
		case TT_Green_City:
		case TT_Yellow_Factory:
		case TT_Yellow_Port:
		case TT_Yellow_Airport:
		case TT_Yellow_City:
		case TT_Neutral_Factory:
		case TT_Neutral_Port:
		case TT_Neutral_Airport:
		case TT_Neutral_City:
			return 3;
			break;
		case TT_Mountain_1:
		case TT_Mountain_2:
		case TT_Red_HQ:
		case TT_Blue_HQ:
		case TT_Green_HQ:
		case TT_Yellow_HQ:
			return 4;
			break;
	}

	assert(0);
	return 0;
}

bool parseIsSee(const TileType tileType)
{
	switch(tileType)
	{
		case TT_Plain:
		case TT_Tree:
		case TT_Mountain_1:
		case TT_Mountain_2:
		case TT_Beach_TL:
		case TT_Beach_TR:
		case TT_Beach_BL:
		case TT_Beach_BR:
		case TT_Beach_H:
		case TT_Beach_V:
		case TT_Beach_T_L:
		case TT_Beach_T_R:
		case TT_Beach_T_T:
		case TT_Beach_T_B:
		case TT_Bridge_H:
		case TT_Bridge_V:
		case TT_River_H:
		case TT_River_V:
		case TT_River_T_L:
		case TT_River_T_R:
		case TT_River_T_T:
		case TT_River_T_B:
		case TT_River_TL:
		case TT_River_TR:
		case TT_River_BL:
		case TT_River_BR:
		case TT_Road_H:
		case TT_Road_V:
		case TT_Road_T_L:
		case TT_Road_T_B:
		case TT_Road_T_R:
		case TT_Road_T_T:
		case TT_Road_X:
		case TT_Red_HQ:
		case TT_Red_Factory:
		case TT_Red_Port:
		case TT_Red_Airport:
		case TT_Red_City:
		case TT_Blue_HQ:
		case TT_Blue_Factory:
		case TT_Blue_Port:
		case TT_Blue_Airport:
		case TT_Blue_City:
		case TT_Green_HQ:
		case TT_Green_Factory:
		case TT_Green_Port:
		case TT_Green_Airport:
		case TT_Green_City:
		case TT_Yellow_HQ:
		case TT_Yellow_Factory:
		case TT_Yellow_Port:
		case TT_Yellow_Airport:
		case TT_Yellow_City:
		case TT_Neutral_Factory:
		case TT_Neutral_Port:
		case TT_Neutral_Airport:
		case TT_Neutral_City:
			return false;
			break;
		case TT_River_See:
		case TT_See:
		case TT_Reef:
		case TT_Coast_TL:
		case TT_Coast_TR:
		case TT_Coast_BL:
		case TT_Coast_BR:
		case TT_Coast_L:
		case TT_Coast_R:
		case TT_Coast_B:
		case TT_Coast_T:
		case TT_Coast_H:
		case TT_Coast_V:
		case TT_Coast_T_L:
		case TT_Coast_T_B:
		case TT_Coast_T_R:
		case TT_Coast_T_T:
		case TT_Coast_X:
			return true;
	}

	assert(0);
	return false;
}

bool parseIsBuilding(const TileType tileType)
{
	switch(tileType)
	{
		case TT_Plain:
		case TT_Tree:
		case TT_Mountain_1:
		case TT_Mountain_2:
		case TT_Beach_TL:
		case TT_Beach_TR:
		case TT_Beach_BL:
		case TT_Beach_BR:
		case TT_Beach_H:
		case TT_Beach_V:
		case TT_Beach_T_L:
		case TT_Beach_T_R:
		case TT_Beach_T_T:
		case TT_Beach_T_B:
		case TT_Bridge_H:
		case TT_Bridge_V:
		case TT_River_H:
		case TT_River_V:
		case TT_River_T_L:
		case TT_River_T_R:
		case TT_River_T_T:
		case TT_River_T_B:
		case TT_River_TL:
		case TT_River_TR:
		case TT_River_BL:
		case TT_River_BR:
		case TT_Road_H:
		case TT_Road_V:
		case TT_Road_T_L:
		case TT_Road_T_B:
		case TT_Road_T_R:
		case TT_Road_T_T:
		case TT_Road_X:
		case TT_River_See:
		case TT_See:
		case TT_Reef:
		case TT_Coast_TL:
		case TT_Coast_TR:
		case TT_Coast_BL:
		case TT_Coast_BR:
		case TT_Coast_L:
		case TT_Coast_R:
		case TT_Coast_B:
		case TT_Coast_T:
		case TT_Coast_H:
		case TT_Coast_V:
		case TT_Coast_T_L:
		case TT_Coast_T_B:
		case TT_Coast_T_R:
		case TT_Coast_T_T:
		case TT_Coast_X:
			return false;
			break;
		case TT_Red_HQ:
		case TT_Red_Factory:
		case TT_Red_Port:
		case TT_Red_Airport:
		case TT_Red_City:
		case TT_Blue_HQ:
		case TT_Blue_Factory:
		case TT_Blue_Port:
		case TT_Blue_Airport:
		case TT_Blue_City:
		case TT_Green_HQ:
		case TT_Green_Factory:
		case TT_Green_Port:
		case TT_Green_Airport:
		case TT_Green_City:
		case TT_Yellow_HQ:
		case TT_Yellow_Factory:
		case TT_Yellow_Port:
		case TT_Yellow_Airport:
		case TT_Yellow_City:
		case TT_Neutral_Factory:
		case TT_Neutral_Port:
		case TT_Neutral_Airport:
		case TT_Neutral_City:
			return true;
			break;
	}

	assert(0);
	return false;
}

Tile* TileFactory(SpriteManager& sm, const std::string& themeName, const TileType tileType)
{
	Tile* pT = new Tile(tileType,getTileSurface(sm,themeName,tileType),parseDefence(tileType),parseIsSee(tileType),parseIsBuilding(tileType),20);

	return pT;
}