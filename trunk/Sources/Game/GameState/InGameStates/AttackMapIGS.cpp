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

#include "AttackMapIGS.h"

#include "Game/GameState/GameObjects/Map/Map.h"
#include "Game/GameState/GameObjects/Map/MapDrawer.h"
#include "Game/GameState/GameObjects/Map/MapMarker/GlobalAttackMapMarker.h"
#include "Game/GameState/GameObjects/Cursor.h"

AttackMapIGS :: AttackMapIGS(Map* pMap, const Camera* pCamera, Cursor* pCursor, GameInfo* pGameInfo)
:InGameState(pMap,pCamera,pCursor,pGameInfo)
{
	pMapMarker = new GlobalAttackMapMarker(pMap,pMap->getTheme());
}

AttackMapIGS :: ~AttackMapIGS()
{
	delete pMapMarker;
}

void AttackMapIGS :: init()
{
	pMapMarker->setMarksForUnitAt(pCursor->getPosition());
}

bool AttackMapIGS :: draw(NE::Renderer* pRenderer, unsigned int time)
{
	bool bResult = true;

	bResult &= pMapMarker->draw(*pRenderer,*pCamera,time);
	bResult &= MapDrawer::drawUnits(*pRenderer,pMap,*pCamera,time);

	return bResult;
}

IGState AttackMapIGS :: update(NE::InputManager::ArrowsDirection direction, NE::InputManager::Buttons buttons, unsigned int time)
{
	(void) direction;
	(void) time;

	if ( (buttons & NE::InputManager::INPUT_B) == NE::InputManager::INPUT_B )
	{
		return IGS_AttackMap;
	}
	else
	{
		return IGS_Idle;
	}
}