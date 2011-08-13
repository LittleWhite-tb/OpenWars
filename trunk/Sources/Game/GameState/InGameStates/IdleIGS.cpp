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

#include "IdleIGS.h"

#include "Engine/Params.h"

#include "Game/GameState/GameObjects/Map/Map.h"
#include "Game/GameState/GameObjects/Cursor.h"
#include "Game/GameState/GameObjects/Tile.h"
#include "Game/GameState/GameObjects/Unit.h"

#include "UI/OfficerBox.h"

IdleIGS :: IdleIGS(Map* pMap, const Camera* pCamera, Cursor* pCursor, GameInfo* pGameInfo, const USize2& winSize)
	:InGameState(pMap,pCamera,pCursor, pGameInfo) 
{
	pOfficerBox = new OfficerBox(pMap->getTheme(),winSize);
}

IdleIGS :: ~IdleIGS()
{
	delete pOfficerBox;
}

bool IdleIGS::draw(NE::Renderer* pRenderer, unsigned int time)
{
	bool bResult = true;

	bResult &= pCursor->draw(*pRenderer,*pCamera,time);
	bResult &= pOfficerBox->draw(*pRenderer,*pGameInfo,time);

	return bResult;
}

IGState IdleIGS::update(NE::InputManager::ArrowsDirection direction, NE::InputManager::Buttons buttons, unsigned int time)
{
	(void) time;

	pCursor->move(direction);

	if ( (buttons & NE::InputManager::INPUT_X) == NE::InputManager::INPUT_X )
    {
		// Get the information under the cursor
		const Tile* pTile = pMap->getTile(pCursor->getPosition());
		const Unit* pUnit = pMap->getUnit(pCursor->getPosition());

		// if ( pUnit->faction == actualFaction ) // TODO
		if ( pUnit->state == US_NO_UNIT )
		{
			if ( pTile->getParams()->exists("producerName") )	// We are on a building able to produce units
			{
				return IGS_Construction;
			}
			else
			{
				return IGS_Menu;
			}
		}
		if ( pUnit->state == US_ACTIVE )
		{
			return IGS_UnitSelected;
		}
		else if ( pUnit->state == US_DONE )
		{
			return IGS_Menu;
		}
	}

	pOfficerBox->update(pCursor->getPosition());

	return IGS_Idle;
}