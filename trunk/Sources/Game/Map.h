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

class Window;
class Renderer;

class Map
{
private:

	unsigned int width;			/*!< Width (in tile) of the map */
	unsigned int height;		/*!< Height (in tile) of the map */

	Tile*** map;				/*!< 2D Array representating the map */

	bool valid;					/*!< if the map is loaded properly */

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
	~Map(void);

	//! Draw the map
	/*!
      \param win the window where to draw
	  \param r the renderer to use to draw the map
	  \param time the actual time (for animation)
	  \return true if all goes right
    */
	bool draw(Window& win, Renderer& r, const unsigned int time);

	//! Return if the map is valid
	/*!
		\return true if the map is valid
	*/
	bool isValidMap(void) { return valid; }
};

/*! \class Map Map.h "Game/Map.h"
 *  \brief Map management class
 *
 * Manage the Map for the game.
 * Can do the following:
 *		- Load from file (directly in the constructor, the parsing is done manualy)
 *		- Draw the map
 */

#endif