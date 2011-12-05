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

#include "MovementMapMarker.h"

#include "Engine/Theme.h"
#include "Engine/Params.h"
#include "Game/GameState/GameObjects/Tile.h"
#include "Game/GameState/GameObjects/Unit.h"
#include "Game/GameState/GameObjects/Map/Map.h"

MovementMapMarker :: MovementMapMarker(const Map* pMap)
    :MapMarker(pMap,pMap->getTheme()->getUIItem("MoveMark")->getSprite())
{
}

void MovementMapMarker :: setMarksRecursively(const UVec2& position, const UnitTemplate* pUnitTemplate, int movement, bool firstCall)
{
    int movementCost = pMap->getTile(position)->getParams()->getAs<int>("movementCost",1);
    if ( pUnitTemplate->getParams()->getAs<bool>("isVehicule",false) )
    {
        movementCost = pMap->getTile(position)->getParams()->getAs<unsigned int>("vehiculeMovementCost",1);
    }

    if ( pMap->isValidPosition(position) == false )
    {
        return;
    }
    if ( movement+1 < movementCost )
    {
        return;
    }
    if ( marks[position.y][position.x] != -1 && marks[position.y][position.x] > movement ) // This position have been already proceed
    {
        return;
    }
    if ( pMap->testUnit(position,pUnitTemplate) == false )
    {
        return;
    }

    marks[position.y][position.x] = movement;

    // Checks if the unit can move here // or if there is already a unit here
    // In this case, we don't have to continue the process, since we can't move here
    if ( !firstCall && (pMap->getUnit(position)->state != US_NO_UNIT && pMap->getUnit(position)->faction != pUnitTemplate->getFaction()) )
    {
        return;
    }

    // Check if we can move the unit here, and if the we no unit at this place
    {
        UVec2 positionLeft(position.x-1,position.y);
        setMarksRecursively(positionLeft,pUnitTemplate,movement-movementCost);
    }

    {
        UVec2 positionRight(position.x+1,position.y);
        setMarksRecursively(positionRight,pUnitTemplate,movement-movementCost);
    }

    {
        UVec2 positionUp(position.x,position.y-1);
        setMarksRecursively(positionUp,pUnitTemplate,movement-movementCost);
    }

    {
        UVec2 positionDown(position.x,position.y+1);
        setMarksRecursively(positionDown,pUnitTemplate,movement-movementCost);
    }
}

void MovementMapMarker :: setMarks(const UVec2& position, const Unit* pUnit)
{
    unsigned int movement = pUnit->getPossibleMovementLength();
    if (movement == 0)
    {
        return;
    }

    this->setMarksRecursively(position,pUnit->getTemplate(),movement, true);
}
