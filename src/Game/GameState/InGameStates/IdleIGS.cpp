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

#include "IdleIGS.h"

#include "Engine/Params.h"

#include "Game/GameState/GameObjects/Map/Map.h"
#include "Game/GameState/GameObjects/Map/MapDrawer.h"
#include "Game/GameState/GameObjects/Cursor.h"
#include "Game/GameState/GameObjects/Tile.h"
#include "Game/GameState/GameObjects/Unit.h"
#include "Game/GameState/GameObjects/GameInfo.h"

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

    bResult &= MapDrawer::drawUnits(*pRenderer,pMap,*pCamera,time);
    bResult &= pCursor->draw(*pRenderer,*pCamera,time);
    bResult &= pOfficerBox->draw(*pRenderer,*pGameInfo,time);

    return bResult;
}

IGState IdleIGS::update(NE::InputManager* pInputManager, unsigned int time)
{
    (void) time;

    pCursor->move(pInputManager->getDirectionsPressed(0));

    if ( pInputManager->getButtonState(0,NE::InputManager::INPUT_X) == NE::InputManager::BS_JUSTPRESSED )
    {
        // Get the information under the cursor
        const Tile* pTile = pMap->getTile(pCursor->getPosition());
        const Unit* pUnit = pMap->getUnit(pCursor->getPosition());

        // if ( pUnit->faction == actualFaction ) // TODO
        if ( pUnit->state == US_NO_UNIT )
        {
            if ( pTile->getParams()->exists("producerName") )   // We are on a building able to produce units
            {
                if ( pTile->getParams()->getAs<unsigned int>("faction") == pGameInfo->getCurrentFaction() )
                {
                    return IGS_Construction;
                }
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
        else
        {
            return IGS_Menu;
        }
    }
    if ( pInputManager->getButtonState(0,NE::InputManager::INPUT_B) == NE::InputManager::BS_JUSTPRESSED )
    {
        if ( pMap->getUnit(pCursor->getPosition())->state != US_NO_UNIT )
        {
            return IGS_AttackMap;
        }
    }

    pOfficerBox->update(pCursor->getPosition());

    return IGS_Idle;
}
