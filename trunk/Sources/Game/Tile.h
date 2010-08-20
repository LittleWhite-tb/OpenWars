#ifndef __TILE_H__
#define __TILE_H__

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

struct SDL_Surface;

class AnimatedSprite;
class SpriteManager;

#include <string>

enum TileType
{
	TT_Plain=0,
	TT_Tree,
	// ToDo should have some new trees

	// Mountain
	TT_Mountain_1,
	TT_Mountain_2,

	// Beach
	TT_Beach_TL,	// Top Left
	TT_Beach_TR,	// Top Right
	TT_Beach_BL,	// Bottom Left
	TT_Beach_BR,	// Bottom Right
	TT_Beach_H,		// Horizontal
	TT_Beach_V,		// Vertical
	TT_Beach_T_L,	// T Left
	TT_Beach_T_R,	// T Right
	TT_Beach_T_T,	// T Top
	TT_Beach_T_B,	// T Bottom

	// Bridge
	TT_Bridge_H,	// Horizontal
	TT_Bridge_V,	// Vertical

	// River
	TT_River_H,		// Horizontal
	TT_River_V,		// Vertical
	TT_River_T_L,	// T Left
	TT_River_T_R,	// T Right
	TT_River_T_T,	// T Top
	TT_River_T_B,	// T Bottom
	TT_River_TL,	// Top Left
	TT_River_TR,	// Top Right
	TT_River_BL,	// Bottom Left
	TT_River_BR,	// Bottom Right
	TT_River_See,	// River to See

	TT_See,

	TT_Reef,

	// Coast
	TT_Coast_TL,	// Top Left
	TT_Coast_TR,	// Top Right
	TT_Coast_BL,	// Bottom Left
	TT_Coast_BR,	// Bottom Right
	TT_Coast_L,		// Left
	TT_Coast_R,		// Right
	TT_Coast_B,		// Bottom
	TT_Coast_T,		// Top
	TT_Coast_H,		// Horizontal
	TT_Coast_V,		// Vertical
	TT_Coast_T_L,	// T Left
	TT_Coast_T_B,	// T Bottom
	TT_Coast_T_R,	// T Right
	TT_Coast_T_T,	// T Top
	TT_Coast_X,		// X

	// Road
	TT_Road_H,		// Horizontal
	TT_Road_V,		// Vertical
	TT_Road_T_L,	// T Left
	TT_Road_T_B,	// T Bottom
	TT_Road_T_R,	// T Right
	TT_Road_T_T,	// T Top
	TT_Road_X,		// X

	// Buildings
		// Red
	TT_Red_HQ,
	TT_Red_Factory,
	TT_Red_Port,
	TT_Red_Airport,
	TT_Red_City,

		// Blue
	TT_Blue_HQ,
	TT_Blue_Factory,
	TT_Blue_Port,
	TT_Blue_Airport,
	TT_Blue_City,

		// Green
	TT_Green_HQ,
	TT_Green_Factory,
	TT_Green_Port,
	TT_Green_Airport,
	TT_Green_City,

		// Yellow
	TT_Yellow_HQ,
	TT_Yellow_Factory,
	TT_Yellow_Port,
	TT_Yellow_Airport,
	TT_Yellow_City,

		// Neutral
	TT_Neutral_Factory,
	TT_Neutral_Port,
	TT_Neutral_Airport,
	TT_Neutral_City,

	TT_END_LIST,	// This has to be always at the end ; used as loop stoppper
};

typedef struct Tile
{
	TileType tileType;

	AnimatedSprite* pAnimation;

	unsigned char defence;
	bool isSee;	// Reminder: See, only boat can be on it, can't be walkable
	bool isBuilding;

	unsigned char cityLife; // For capturing

	Tile(void):tileType(TT_Plain),pAnimation(0),defence(0),isSee(false),isBuilding(false),cityLife(0) {}
	Tile(const TileType tileType, AnimatedSprite* const pAnimation, const unsigned char defence, const bool isSee, const bool isBuilding, const unsigned char cityLife)
		:tileType(tileType),pAnimation(pAnimation),defence(defence),isSee(isSee),isBuilding(isBuilding),cityLife(cityLife) {}

	~Tile(void);
}Tile;

Tile* TileFactory(SpriteManager& sm, const std::string& themeName, const TileType tileType);

#endif