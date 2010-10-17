#ifndef __MAP_H__
#define __MAP_H__

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

#include <string>
#include <map>

#include "Tile.h"
#include "Unit.h"

#include "../Types/Vec2.h"

class Renderer;
class Camera;
class SpriteManager;
class AnimatedSprite;

class Map
{
protected:

	std::map<TileType, Tile>tilesSet;						/*!< Set of tile to use with this map */
	std::map<UnitType, AnimatedSprite*> unitsASprite;		/*!< The collection to associate type of the unit to a sprite */

	unsigned int width;			/*!< Width (in tile) of the map */
	unsigned int height;		/*!< Height (in tile) of the map */

	TileType** map;					/*!< 2D Array representating the map */
	Unit*** unitMap;				/*!< 2D Array representating the unit on the map */

	bool valid;					/*!< if the map is loaded properly */

	Map(void) {};

	//! Load the tiles that the map will use
	/*!
		Will use a tile set file to know the settings of each tiles
		\param sm the SpriteManager to load the sprites.
		\param theme the theme to use to know which sprites to load
	*/
	void loadTileSet(SpriteManager& sm, const std::string& theme);

	//! Load the units that the map will use
	/*!
		Will use a unit set file to know the settings of each units
		\param sm the SpriteManager to load the sprites.
		\param theme the theme to use to know which sprites to load
	*/
	void loadUnitSet(SpriteManager& sm, const std::string& theme);

	//! Load the tiles that the map will use
	/*!
		Will load all the tiles available for the theme passed by parameter in a std::map in view to associate the TileType to an AnimatedSprite pointer.
		\param sm the SpriteManager to load the sprites.
		\param theme the theme to use to know which sprites to load
	*/
	void loadGraphics(SpriteManager& sm, const std::string& theme);

	//! Map file parser
	/*!
      Will parse the information contained in the map. When possible, will check if the information are correct
	  \param sm the sprite manager to load the sprites used by the map
	  \param fileName the name of the file to load
	  \return true if all goes right
    */
	bool parser(SpriteManager& sm, const std::string& fileName);

public:
	//! Basic constructor
	/*!
      Will call the parser
	  If you need to check if the map is correct (and you should), please use isValidMap()
	  \param sm the sprite manager to load the sprites used by the map
	  \param fileName the name of the file to load
    */
	Map(SpriteManager& sm, const std::string& fileName);

	//! Basic destructor
	/*!
      Frees the map
    */
	virtual ~Map(void);

	//! Draw the map
	/*!
	  \param r the renderer to use to draw the map
	  \param c The Camera (used to draw the correct part of the Map)
	  \param time the actual time (for animation)
	  \return true if all goes right
    */
	bool draw(const Renderer& r, const Camera& c, const unsigned int time);

	//! Return if the map is valid
	/*!
		\return true if the map is valid
	*/
	bool isValidMap(void)const { return valid; }

	//! Return the width of the map
	/*!
		\return width of the map
	*/
	unsigned int getWidth(void)const { return width; }

	//! Return the height of the map
	/*!
		\return height of the map
	*/
	unsigned int getHeight(void)const { return height; }

	//! Return the type corresponding to the position
	/*!
		The function will check if the position is outside the map. If it is, the Tile returned has for type TT_Invalid
		\param position the position of the Tile to get
		\return the TileType corresponding to the input position ... TT_Invalid if the position is not valid
	*/
	TileType getTileType(const UVec2& position)const;

	//! Return the tile corresponding to the position
	/*!
		The function will check if the position is outside the map. If it is, the Tile returned has for type TT_Invalid
		\param position the position of the Tile to get
		\return the Tile corresponding to the input position
	*/
	Tile getTile(const UVec2& position)const;

	//! Return the tile corresponding to the TileType
	/*!
		\param tt the TileType
		\return the Tile corresponding to the input TileType
	*/
	Tile getTile(const TileType& tt)const;

	//! Return the Unit corresponding to the position
	/*!
		The function will check if the position is outside the map. If it is, NULL is returned
		\param position the position of the Tile to get
		\return the Unit corresponding to the input position or NULL
	*/
	Unit* getUnit(const UVec2& position)const;

	//! Return the sprite corresponding to the type
	/*!
		If the type is not found in the map library, return NULL
		\param type the type associated to the sprite to return
		\return the AnimatedSprite pointer associated to the type
	*/
	AnimatedSprite* getAssociatedSprite(const TileType type);

	//! Return the sprite corresponding to the type
	/*!
		If the type is not found in the map library, return NULL
		\param type the type associated to the sprite to return
		\return the AnimatedSprite pointer associated to the type
	*/
	AnimatedSprite* getAssociatedSprite(const UnitType type);
};

/*! \class Map Map.h "Game/Map.h"
 *  \brief Map management class
 *
 * Manage the Map for the game.
 * Can do the following:
 *		- Load from file (directly in the constructor, the parsing is done manualy)
 *		- Draw the map
 *		- Get a Tile
 */

#endif