#ifndef __MAPGAME_H__
#define __MAPGAME_H__

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

#include "Map.h"

#include "Unit.h"

class Renderer;
class SpriteManager;
class Camera;

class MapGame : public Map
{
private:
	Unit*** unitMap;			/*!< Map of units logical information */
public:

	//! Basic constructor
	/**
		Load the map
	*/
	MapGame(SpriteManager& sm, const std::string& fileName);

	//! Basic destructor
	/**
	*/
	~MapGame();

	//! Draw the map
	/*!
	  \param r the renderer to use to draw the map
	  \param c The Camera (used to draw the correct part of the Map)
	  \param time the actual time (for animation)
	  \return true if all goes right
    */
	bool draw(const Renderer& r, const Camera& c, const unsigned int time);

	//! Enable all units in the map
	/**
	*/
	void enableUnits(void);

	//! Set the Unit at the position
	/*!
		Will overwrite the Unit previously contained on the map by the new one.
		The new Unit is selected following the internal logic of the editor.
		\param position the position where to change the tile
		\param unitType the type of the new unit
		\return true if all goes right
	*/
	bool setTile(const UVec2& position, const UnitType unitType);
};

/*! \class MapGame MapGame.h "Game/MapGame.h"
 *  \brief Map implementation for the game
 *
 * This implementation adds a new map containing the information of all units (fuel, life...)
 * The class is reimplementing the draw function (to draw enabled/disabled unit) and 
 * the setTile function (to get logical unit in the unitMap)
 */

#endif