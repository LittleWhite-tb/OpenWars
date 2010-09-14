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

#include "Tile.h"
#include "../Types/Vec2.h"

class Renderer;
class Camera;

class Map
{
private:

	unsigned int width;			/*!< Width (in tile) of the map */
	unsigned int height;		/*!< Height (in tile) of the map */

	Tile*** map;				/*!< 2D Array representating the map */

	bool valid;					/*!< if the map is loaded properly */

#ifdef EDITOR
	std::string theme;			/*!< Graphical theme for the map */
#endif

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
#ifdef EDITOR
	//! Basic constructor
	/*!
      Create an empty map, with only T_Plain
	  \param sm the sprite manager to load the sprites used by the map
	  \param size the size of the map wanted
    */
	Map(SpriteManager& sm, const UVec2& size);
#endif

	//! Basic destructor
	/*!
      Frees the map
    */
	~Map(void);

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

	//! Return the tile corresponding to the position
	/*!
		\param position the position of the Tile to get
		\return the Tile corresponding to the input position
	*/
	Tile* getTile(const UVec2& position)const { return map[position.y][position.x]; }

#ifdef EDITOR
	//! Set the Tile at the position
	/*!
		Will delete the Tile previously at this position and create a new one that will take place.
		\param sm the SpriteManager to use when creating the sprite
		\param position the position where to change the tile
		\param tileType the type of the new tile
		\return true if all goes right
	*/
	bool setTile(SpriteManager& sm, const UVec2& position, const TileType tileType);

	//! Save the Map in a file
	/*!
		\param fileName the file name where to save the file
		\return true if all goes right
	*/
	bool save(const std::string& fileName);
#endif
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