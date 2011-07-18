#ifndef __UNIT_H__
#define __UNIT_H__

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

#include <string>

#include "UnitTemplate.h"

namespace NE { class SpriteLoader; }

enum UnitState
{
	US_NO_UNIT,
	US_ACTIVE,
	US_MOVED,
	US_DONE,
};

/**
	Unit is a class used to handle the unit instances on the map.
*/
class Unit
{
private:
	const UnitTemplate* pUnitTemplate;	/*!< */

public:
	unsigned short faction;			/*!< */

    unsigned int fuel;              /*!< The remaining fuel */
    unsigned int ammo;              /*!< The remaining ammo */

    unsigned int life;              /*!< The life */

    UnitState state;                /*!< If the unit is enabled (can be moved) */

	Unit():state(US_NO_UNIT) {};
	Unit(const UnitTemplate* pUnitTemplate);

	const std::string& getName()const { return pUnitTemplate->getName(); }
	unsigned int getID()const { return pUnitTemplate->getID(); }
	AnimatedSprite* getSprite()const { return pUnitTemplate->getSprite(); }
	const UnitTemplate* const getTemplate()const { return pUnitTemplate; }
};

/*! \enum UnitState
 * Identifiers to know which state the unit is
 */

/*! \class Unit Unit.h "Game/Unit.h"
 *  \brief unit on the map controlled by the player
 */

/*!	\fn Unit :: Unit()
 */

/*!	\fn Unit :: Unit(const UnitTemplate* pUnitTemplate)
 *	\param pUnitTemplate pointer to the unit template to use to get initial information
 */

/*!	\fn const std::string& Unit :: getName()const
 *	\return
 */

/*!	\fn unsigned int Unit :: getID()const
 *	\return
 */

/*!	\fn AnimatedSprite* const Unit :: getSprite()const
 *	\return
 */

/*!	\fn const UnitTemplate* const Unit :: getTemplate()const
 *	\return
 */

#endif