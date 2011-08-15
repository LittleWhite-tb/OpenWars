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

#include "GlobalAttackMapMarker.h"

#include "Engine/Theme.h"
#include "Engine/Params.h"
#include "Game/GameState/GameObjects/Unit.h"
#include "Game/GameState/GameObjects/Map/Map.h"

#include "Utils/Logger.h"

GlobalAttackMapMarker :: GlobalAttackMapMarker(const Map* pMap, const Theme* pTheme)
	:MapMarker(pMap,pTheme->getUIItem("AttackMark")->getSprite())
{
	assert(pTheme);
}

void GlobalAttackMapMarker :: setMarksRecursively(const UVec2& position, const UnitTemplate* pUnitTemplate, int movement, bool firstCall)
{
	if ( pMap->isValidPosition(position) == false )
	{
		return;
	}
	if ( movement < 0 )
	{
		return;
	}
	if ( marks[position.y][position.x] != -1 && marks[position.y][position.x] > movement ) // This position have been already proceed
	{
		return;
	}

	marks[position.y][position.x] = movement;

	// Checks if the unit can move here // or if there is already a unit here
	// In this case, we don't have to continue the process, since we can't move here
	if ( !firstCall && (pMap->testUnit(position,pUnitTemplate) == false || pMap->getUnit(position)->state != US_NO_UNIT) )
	{
		return;
	}

	// Check if we can move the unit here, and if the we no unit at this place
	{
		UVec2 positionLeft(position.x-1,position.y);
		setMarksRecursively(positionLeft,pUnitTemplate,movement-1);
	}

	{
		UVec2 positionRight(position.x+1,position.y);
		setMarksRecursively(positionRight,pUnitTemplate,movement-1);
	}

	{
		UVec2 positionUp(position.x,position.y-1);
		setMarksRecursively(positionUp,pUnitTemplate,movement-1);
	}

	{
		UVec2 positionDown(position.x,position.y+1);
		setMarksRecursively(positionDown,pUnitTemplate,movement-1);
	}
}

void GlobalAttackMapMarker :: setMarksForUnitAt(const UVec2& position)
{
	this->clear();

	if ( pMap->isValidPosition(position) == false )
	{
		LWarning << "Passing invalid position to GlobalAttackMapMarker :: setMarks";
		return;
	}

	const Unit* pUnit = pMap->getUnit(position);

	if ( pUnit == NULL )
	{
		LWarning << "No unit at: " << position << " for GlobalAttackMapMarker :: setMarks";
		return;
	}

	unsigned int minAttack = pUnit->getTemplate()->getParams()->getAs<unsigned int>("range_min",0);
	unsigned int maxAttack = pUnit->getTemplate()->getParams()->getAs<unsigned int>("range_max",0);
	if ( minAttack == 0 && maxAttack == 0 ) // This unit does not attack
	{
		return;
	}

	if ( minAttack == 1 && maxAttack == 1 ) // This unit can move and attack (not range attack)
	{
		maxAttack += pUnit->getPossibleMovementLength();
		// marks[position.y][position.x]= ;
		this->setMarksRecursively(position,pUnit->getTemplate(),maxAttack, true);
		// We unmark the actual position
		marks[position.y][position.x]= -1;
	}
	else // Range attack
	{
		this->setMarksInRange(position,minAttack,maxAttack);
	}
}