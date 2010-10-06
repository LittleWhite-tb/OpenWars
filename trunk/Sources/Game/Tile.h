#ifndef __TILE_H__
#define __TILE_H__

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

struct SDL_Surface;

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
	TT_Beach_TL_R,	// Top Left with Right
	TT_Beach_TL_B,	// Top Left with Bottom
	TT_Beach_TL_2,	// Top Left
	TT_Beach_TR,	// Top Right
	TT_Beach_TR_B,	// Top Right with Bottom 
	TT_Beach_TR_L,	// Top Right with Left
	TT_Beach_TR_2,	// Top Right
	TT_Beach_BL,	// Bottom Left
	TT_Beach_BL_T,	// Bottom Left with Top
	TT_Beach_BL_R,	// Bottom Left with Right
	TT_Beach_BL_2,	// Bottom Left
	TT_Beach_BR,	// Bottom Right
	TT_Beach_BR_L,	// Bottom Right with Left
	TT_Beach_BR_T,	// Bottom Right with Top
	TT_Beach_BR_2,	// Bottom Right
	TT_Beach_EL,	// T Left
	TT_Beach_ER,	// T Right
	TT_Beach_ET,	// T Top
	TT_Beach_EB,	// T Bottom
	TT_Beach_L,	// Left
	TT_Beach_L_T,	// Left with Top
	TT_Beach_L_B,	// Left with Bottom
	TT_Beach_L_2,	// Left
	TT_Beach_R,	// Right
	TT_Beach_R_T,	// Right with Top
	TT_Beach_R_B,	// Right with Bottom
	TT_Beach_R_2,	// Right
	TT_Beach_T,	// Top
	TT_Beach_T_L,	// Top with Left
	TT_Beach_T_R,	// Top with Right
	TT_Beach_T_2,	// Top
	TT_Beach_B,	// Bottom
	TT_Beach_B_R,	// Bottom with Right
	TT_Beach_B_L,	// Bottom with Left
	TT_Beach_B_2,	// Bottom

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
	TT_River_See_T,	// River to See Top
	TT_River_See_B,	// River to See Bottom
	TT_River_See_L,	// River to See left
	TT_River_See_R,	// River to See Right
	TT_River_X,		

	TT_Sea,
	TT_Sea_TL,		// For see with some coast on it (but just a few)
	TT_Sea_TR,
	TT_Sea_BL,
	TT_Sea_BR,

	TT_Reef,

	// Coast
	TT_Coast,		// Alone ... Without nothing around
	TT_Coast_ET,	// Ending Top
	TT_Coast_EB,	// Ending Bottom
	TT_Coast_EL,	// Ending Left
	TT_Coast_ER,	// Ending Right
	TT_Coast_TL,	// Top Left
	TT_Coast_TR,	// Top Right
	TT_Coast_BL,	// Bottom Left
	TT_Coast_BR,	// Bottom Right
	TT_Coast_RBL,	// River like Bottom Left corner
	TT_Coast_RBR,	// River like Bottom Right corner
	TT_Coast_RTR,	// River like Top Right corner
	TT_Coast_RTL,	// River like Top Left corner
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
	TT_Coast_T_TL,	// T Top Left
	TT_Coast_T_TR,	// T Top Right
	TT_Coast_T_BL,	// T Bottom Left
	TT_Coast_T_BR,	// T Bottom Right
	TT_Coast_T_LT,	// T Left Top
	TT_Coast_T_RT,	// T Right Top
	TT_Coast_T_LB,	// T Left Bottom
	TT_Coast_T_RB,	// T Right Bottom
	TT_Coast_X,		// X
	TT_Coast_XL,		// X Left
	TT_Coast_XR,		// X Right
	TT_Coast_XB,		// X Bottom
	TT_Coast_XT,		// X Top
	TT_Coast_XTL,		// X Top Left
	TT_Coast_XTR,		// X Top Right
	TT_Coast_XBL,		// X Bottom Left
	TT_Coast_XBR,		// X Bottom Right
	TT_Coast_XTLBR,		// X with diagonal coast ( on Top Left & Bottom Right )
	TT_Coast_XBLTR,		// X with diagonal coast ( on Top Right & Bottom Left )

	// Road
	TT_Road_H,		// Horizontal
	TT_Road_V,		// Vertical
	TT_Road_TL,		// Corner Top Left
	TT_Road_TR,		// Corner Top Right
	TT_Road_BL,		// Corner Bottom Left
	TT_Road_BR,		// Corner Bottom Right
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

	TT_Invalid,		// To make an invalid tile
	TT_END_LIST,	// This has to be always at the end ; used as loop stoppper
};

typedef struct Tile
{
	TileType tileType;				/*!< The actual tile type */

	unsigned char defence;			/*!< The defence of the tile */
	bool isRoad;					/*!< If the tile is a road tile */
	bool isBridge;					/*!< If the tile is a bridge tile */
	bool isRiver;					/*!< If the tile is a river tile */
	bool isSea;						/*!< If it is see */ // Reminder: See, only boat can be on it, can't be walkable
	bool isBeach;					/*!< If it is beach */
	bool isBuilding;				/*!< If it is a building */
	bool needBackground;			/*!< If the Tile need to have a plain has background drawn before */

	unsigned char cityLife;			/*!< The actual remaining life of the builing */ // For capturing

	//! Default constructor
	/*!
		Sea is true by default
	*/
	Tile(void):tileType(TT_Invalid),defence(0),isRoad(false),isBridge(false),isRiver(false),isSea(true),isBeach(false),isBuilding(false),needBackground(false),cityLife(0) {}

	//! Basic constructor
	/*!
		\param tileType the type of the tile
	*/
	Tile(const TileType tileType);

}Tile;


//! Check if the type correspond to a building
/*!
 * \param tileType the type
 * \return true if the type corresponds to a building
*/
bool parseIsBuilding(const TileType tileType);

//! Check if the type correspond to a road
/*!
 * \param tileType the type
 * \return true if the type corresponds to a road
*/
bool parseIsRoad(const TileType tileType);

//! Check if the type correspond to a sea
/*!
 * \param tileType the type
 * \return true if the type corresponds to a sea
*/
bool parseIsSea(const TileType tileType);

//! Check if the type correspond to a river
/*!
 * \param tileType the type
 * \return true if the type corresponds to a river
*/
bool parseIsRiver(const TileType tileType);

//! Check if the type correspond to a beach
/*!
 * \param tileType the type
 * \return true if the type corresponds to a beach
*/
bool parseIsBeach(const TileType tileType);

//! Check if the type correspond to a bridge
/*!
 * \param tileType the type
 * \return true if the type corresponds to a bridge
*/
bool parseIsBridge(const TileType tileType);

//! Check if the type correspond to a HQ
/*!
 * \param tileType the type
 * \return true if the type corresponds to a HQ
*/
bool parseIsHQ(const TileType tileType);

//! Get the name of the tile
/*!
 *
 * \param tileType the type
 * \return the name of the tile to display
*/
const std::string parseName(const TileType tileType);

/*! \struct Tile Tile.h "Game/Tile.h"
 *  \brief Tile struct
 *
 * Keeps the following:
 *		- The enum to characterise the tile (id)
 *		- The defence of the tile (gameplay)
 *		- If the tile is a see tile (gameplay)
 *		- If the tile is a building (gameplay)
 *		- The life of the building (gameplay)
 */

/*! \enum TileType
 * Identifiers to know which Tile it is
 */

#endif