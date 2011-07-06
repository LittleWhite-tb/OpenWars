#ifndef __GLOBALS_H__
#define __GLOBALS_H__

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

// Folders path
#define THEME_PATH		"./data/themes/"			/*!< Path to defaut theme folder */
#define TILESET_PATH	"./data/tilesets/"		/*!< Path to the default tile set folder */
#define UNITSET_PATH	"./data/unitsets/"		/*!< Path to the default unit set folder */
#define MAP_PATH	"./data/maps/"				/*!< Path to the default maps folder */
#define GFX_PATH	"./data/gfx/"				/*!< Path to the default tiles graphics files folder */
#define GFX_TILES_PATH	"./data/gfx/tiles/"		/*!< Path to the default tiles graphics files folder */
#define GFX_UNITS_PATH	"./data/gfx/units/"		/*!< Path to the default units graphics files folder */
#define SFX_PATH	"./data/sfx/"				/*!< Path to the default sounds folder */

// Animations speed
#define NORMAL_SPEED	200						/*!< Default speed for normal animation */
#define SEE_SPEED		300						/*!< Default speed for the see animations */
#define BUILDING_SPEED	150						/*!< Default speed for animation of buildings */
#define CURSOR_SPEED	400						/*!< Default speed for animation of the cursor */

// Sprite default size (will be used to determine the scaling factor)
#define TILE_DEFAULT_WIDTH	32					/*!< Default width of the tiles */
#define TILE_DEFAULT_HEIGHT	32					/*!< Default height of the tiles */
#define MAP_MIN_WIDTH			15				/*!< Minimum number of tiles on the map for x axis */
#define MAP_MIN_HEIGHT			10				/*!< Minimum number of tiles on the map for y axis */

// For the Camera
#define BOUND_CAMERA_DISPLACEMENT	2			/*!< The distance with the bound where the camera starts to move */

#ifdef EDITOR
	// For the TileBar
	#define TILE_BAR_HEIGHT			64			/*!< The height of the tile bar */
	#define TILE_BAR_XMARGIN		10			/*!< Margin around the tiles on the x axis */
	#define TILE_BAR_YMARGIN		8			/*!< Margin around the tiles on the y axis */
	#define TILE_NB_DRAWN			9			/*!< Number of tiles drawn in the bar */
#endif

#endif