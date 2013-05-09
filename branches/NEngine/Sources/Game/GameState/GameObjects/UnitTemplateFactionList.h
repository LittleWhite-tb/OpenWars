#ifndef __UNITTEMPLATEFACTIONLIST_H__
#define __UNITTEMPLATEFACTIONLIST_H__

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

#include <vector>

class UnitTemplate;

class UnitTemplateFactionList
{
private:

	std::vector<UnitTemplate*> unitTemplates;	/*!< */

public:

	~UnitTemplateFactionList();

	void add(UnitTemplate* pUnitTemplate);
	UnitTemplate* get(unsigned int faction)const;
	unsigned int getNumberFaction()const { return unitTemplates.size(); }
};

/*! \class UnitTemplateFactionList UnitTemplateFactionList.h "Game/GameState/GameObjects/UnitTemplateFactionList.h"
 *  \brief List of Unit for each faction
 */

/*! \fn UnitTemplateFactionList :: ~UnitTemplateFactionList()
 */

/*! \fn void UnitTemplateFactionList :: add(UnitTemplate* pUnitTemplate)
 *	\brief adds a new unit in the list. 
 *	\param pUnitTemplate the pointer to the unit to add
 *	The faction corresponding to this unit is determined using the UnitTemplate
 */

/*!	\fn UnitTemplate* UnitTemplateFactionList :: get(unsigned int faction)const;
 *	\brief Gets the unit refering to this faction
 *	\param faction
 *	\return pointer to the corresponding UnitTemplate
 */

/*!	\fn unsigned int UnitTemplateFactionList :: getNumberFaction()const
 *	\brief Returns the number of faction registered in the list
 *	\return
 */

#endif