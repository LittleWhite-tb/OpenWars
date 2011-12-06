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

#include "AttackMapMarker.h"

#include "Engine/Theme.h"
#include "Engine/Params.h"
#include "Game/GameState/GameObjects/Unit.h"
#include "Game/GameState/GameObjects/Map/Map.h"

AttackMapMarker :: AttackMapMarker(const Map* pMap)
	:MapMarker(pMap,pMap->getTheme()->getUIItem("AttackMark")->getSprite())
{
}

void AttackMapMarker :: setMarksOnUnits(const UVec2& position, const Unit* pUnit, unsigned int minRange, unsigned int maxRange)
{
	for ( unsigned int y = 0 ; y < marks.size() ; y++ )
	{
		for ( unsigned int x = 0 ; x < marks[y].size() ; x++ )
		{
			unsigned int dist = distance(position,UVec2(x,y));
			if ( dist >= minRange && dist <= maxRange ) 
			{
				// Ok, this case is attackable, but, is there an attackable unit on it?
				const Unit* pAttackableUnit = pMap->getUnit(position);
				if ( pAttackableUnit == NULL ) // No unit
				{
					continue;
				}
				if ( pAttackableUnit->faction == pUnit->faction ) // Same faction (we will not attack friends)
				{
					continue;
				}

				marks[y][x] = 1;
			}
		}
	}
}

void AttackMapMarker :: setMarks(const UVec2& position, const Unit* pUnit)
{
	unsigned int minAttack = pUnit->getTemplate()->getParams()->getAs<unsigned int>("range_min",0);
	unsigned int maxAttack = pUnit->getTemplate()->getParams()->getAs<unsigned int>("range_max",0);
	if ( minAttack == 0 && maxAttack == 0 ) // This unit does not attack
	{
		return;
	}

	this->setMarksOnUnits(position,pUnit,minAttack,maxAttack);
}