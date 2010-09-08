#ifndef __GLOBALS_H__
#define __GLOBALS_H__

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

// Folders path
#define MAP_PATH	"./data/maps/"				/*!< Path to the default maps folder */
#define GFX_TILES_PATH	"./data/gfx/tiles/"		/*!< Path to the default tiles graphics files folder */
#define GFX_UNITS_PATH	"./data/gfx/units/"		/*!< Path to the default units graphics files folder */
#define SFX_PATH	"./data/sfx/"				/*!< Path to the default sounds folder */

// Animations speed
#define NORMAL_SPEED	200						/*!< Default speed for normal animation */
#define SEE_SPEED		300						/*!< Default speed for the see animations */
#define BUILDING_SPEED	150						/*!< Default speed for animation of buildings */

// Sprite default size (will be used to determine the scaling factor)
#define TILE_DEFAULT_WIDTH	32					/*!< Default width of the tiles */
#define TILE_DEFAULT_HEIGHT	32					/*!< Default height of the tiles */
#define MAP_MIN_WIDTH			15				/*!< Minimum number of tiles on the map for x axis */
#define MAP_MIN_HEIGHT			10				/*!< Minimum number of tiles on the map for y axis */

#endif