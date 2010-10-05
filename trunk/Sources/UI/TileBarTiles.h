#ifdef EDITOR
#ifndef __TILEBARTILES_H__
#define __TILEBARTILES_H__

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

#include "TileBar.h"

#include "../Game/Tile.h"

class SpriteManager;
class Window;
class AnimatedSprite;

class TileView : public View
{	
private:
	TileType type;							/*!< The type of the Tile */					

public:
	//! Constructor for the TileView
	/*!
		Will fill the class with the params
		\param pASprite the AnimatedSprite to dislay
		\param type the type of the Tile
		\param positionX the position in the TileBar
	*/
	TileView(AnimatedSprite* pASprite, const TileType type, const int positionX):View(pASprite,positionX),type(type) {}

	//! Return the TileType kept
	/*!
		\return the TileType
	*/
	TileType getType()const { return type; }
};

class TileBarTiles : public TileBar
{
private:

public:

	//! Basic constructor
	/*!
      Create a TileBar with tiles
	  \param sm the sprite manager to load the sprites used by the map
	  \param win The window where the bar will be
	  \param listTiles The list of tiles to display in the TileBar
    */
	TileBarTiles(SpriteManager& sm, const Window& win, std::vector<TileView*>& listTiles);

	//! Get the TileType selected
	/*!
	  \return the TileType selected in the Bar
	*/
	TileType getSelected(void)const;
};

/*! \struct TileView TileBarTiles.h "Game/TileBarTiles.h"
 *  \brief TileView struct
 *
 * Used to give a structure usable in the TileBar to contain Tile
 */

/*! \class TileBarTiles TileBarTiles.h "UI/TileBarTiles.h"
 *  \brief Display a bar with a list of Tiles
 *
 *	Specialisation for the TileBar to display tiles
 *
 */

#endif
#endif