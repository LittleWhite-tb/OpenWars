#ifndef DOXYGEN_IGNORE_TAG
/**
OpenAWars is an open turn by turn strategic game similar to Advance Wars (c)
Copyright (C) 2010-2015  Alexandre LAURENT

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

website: https://github.com/LittleWhite-tb/OpenWars
e-mail: lw.demoscene@gmail.com
**/
#endif

#include "UnitSelectIGS.h"

#include "Game/GameState/GameObjects/Map/Map.h"
#include "Game/GameState/GameObjects/Map/MapDrawer.h"
#include "Game/GameState/GameObjects/Map/MapMarker/MovementMapMarker.h"
#include "Game/GameState/GameObjects/Cursor.h"

UnitSelectIGS :: UnitSelectIGS(Map* pMap, const Camera* pCamera, Cursor* pCursor, GameInfo* pGameInfo)
	:InGameState(pMap,pCamera,pCursor,pGameInfo)
{
	pMovementMarker = new MovementMapMarker(pMap);
}

UnitSelectIGS :: ~UnitSelectIGS()
{
	delete pMovementMarker;
}

void UnitSelectIGS :: init()
{
	pMovementMarker->setMarksForUnitAt(pCursor->getPosition());
	originalUnitPosition = pCursor->getPosition();
}

bool UnitSelectIGS :: draw(NE::Renderer* pRenderer, unsigned int time)
{
	bool bResult = true;

	bResult &= pMovementMarker->draw(*pRenderer,*pCamera,time);
	bResult &= MapDrawer::drawUnits(*pRenderer,pMap,*pCamera,time);
	bResult &= pCursor->draw(*pRenderer,*pCamera,time);

	return bResult;
}

IGState UnitSelectIGS :: update(NE::InputManager* pInputManager, unsigned int time)
{
    (void)time;

	pCursor->move(pInputManager->getDirectionsPressed(0));

	// Moving unit
	if ( pInputManager->getButtonState(0,NE::InputManager::INPUT_X) == NE::InputManager::BS_JUSTPRESSED &&
		 pMovementMarker->isMarked(pCursor->getPosition()) == true ) // We move only if we are going on a valid tile
	{
		if ( pMap->move(originalUnitPosition,pCursor->getPosition()) == false )
		{
			return IGS_UnitSelected;
		}
		return IGS_Idle; // TODO -> New state
	}

	// Cancelling
	if ( pInputManager->getButtonState(0,NE::InputManager::INPUT_Y) == NE::InputManager::BS_JUSTPRESSED )
	{
		pCursor->move(originalUnitPosition);
		return IGS_Idle;
	}

	return IGS_UnitSelected;
}
