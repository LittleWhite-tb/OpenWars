#ifdef EDITOR
#ifndef __TILEBARUNITS_H__
#define __TILEBARUNITS_H__

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

#include "TileBar.h"

#include "../Game/Unit.h"

namespace NE { class SpriteFactory; }

class Theme;
class AnimatedSprite;

class UnitView : public View
{
protected:
	const UnitTemplate* pUnit;							/*!< */

public:

	UnitView(const UnitTemplate* const pUnit, const int positionX):View(pUnit->getSprite(),positionX),pUnit(pUnit) {}

	const UnitTemplate* getUnit()const { return pUnit; }
};

class TileBarUnits : public TileBar
{
private:

	std::vector<std::vector<UnitView> > unitsList;		/*!< The units to be displayed in the TileBar */

public:
	TileBarUnits(NE::SpriteFactory* const pSF, const Theme* pTheme, std::vector<UnitView*>& listTiles, const USize2& windowSize);

	const UnitTemplate* getSelected(void)const;
};

/*! \class UnitView TileBarUnits.h "Game/TileBarUnits.h"
 *  \brief UnitView struct
 *
 * Used to give a structure usable in the TileBar to contain Unit
 */

/*! \fn UnitView::UnitView(const UnitTemplate* const pUnit, const int positionX)
 * Will fill the structure with the params
 * \param pUnit pointer to the unit to display
 * \param positionX the position in the TileBar
 */

/*! \fn const UnitTemplate* UnitView::getUnit()const
 * \brief Return the unit kept
 * \return the UnitType
 */

/*! \class TileBarUnits TileBarUnits.h "UI/TileBarUnits.h"
 *  \brief Display a bar with a list of Units
 *
 *	Specialisation for the TileBar to display units
 *
 */

/*! \fn TileBarUnits::TileBarUnits(NE::SpriteLoader* const pSL, NE::SpriteFactory* const pSF, std::vector<UnitView*>& listTiles, const USize2& windowSize)
 * \brief Create a TileBar with units
 * \param pSL the SpriteLoader to load the sprites used by the map
 * \param pSF the SpriteFactory to create Sprite on the fly
 * \param listTiles The list of units to display in the TileBar
 * \param windowSize the size of the window (used as reference to place the TileBar)
 */

/*! \fn const UnitTemplate* TileBarUnits::getSelected(void)const
 * \brief Get the unit selected
 * \return the pointer to the unit selected in the Bar
 */

#endif
#endif
