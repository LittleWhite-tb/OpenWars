#ifdef EDITOR
#ifndef __TILEBARUNITS_H__
#define __TILEBARUNITS_H__

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

#include "../Game/Unit.h"

class AnimatedSprite;

class UnitView : public View
{
protected:
	UnitType type;							/*!< The type of the Unit */

public:
	//! Constructor for the TileView
	/*!
		Will fill the structure with the params
		\param pASprite the AnimatedSprite to dislay
		\param type the type of the Unit
		\param positionX the position in the TileBar
	*/
	UnitView(AnimatedSprite* pASprite, const UnitType type, const int positionX):View(pASprite,positionX),type(type) {}

	//! Return the UnitType kept
	/*!
		\return the UnitType
	*/
	UnitType getType()const { return type; }
};

class TileBarUnits : public TileBar
{
private:

	std::vector<std::vector<UnitView> > unitsList;		/*<! The units to be displayed in the TileBar */

public:

	//! Basic constructor
	/*!
      Create a TileBar with units
	  \param sm the sprite manager to load the sprites used by the map
	  \param win The window where the bar will be
	  \param listTiles The list of units to display in the TileBar
    */
	TileBarUnits(SpriteManager& sm, const Window& win, std::vector<UnitView*>& listTiles);

	//! Get the UnitType selected
	/*!
	  \return the UnitType selected in the Bar
	*/
	UnitType getSelected(void)const;
};

/*! \struct UnitView TileBarUnits.h "Game/TileBarUnits.h"
 *  \brief UnitView struct
 *
 * Used to give a structure usable in the TileBar to contain Unit
 */

/*! \class TileBarUnits TileBarUnits.h "UI/TileBarUnits.h"
 *  \brief Display a bar with a list of Units
 *
 *	Specialisation for the TileBar to display units
 *
 */

#endif
#endif