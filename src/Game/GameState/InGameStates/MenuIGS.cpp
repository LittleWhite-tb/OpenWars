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

#include "MenuIGS.h"

#include "NEngine/NEngine.h"
#include "NEngine/Exceptions/ConstructionFailedException.h"

#include "Engine/Params.h"

#include "Game/GameState/GameObjects/Map/Map.h"
#include "Game/GameState/GameObjects/Map/MapDrawer.h"
#include "Game/GameState/GameObjects/Cursor.h"
#include "Game/GameState/GameObjects/GameInfo.h"

#include "UI/MenuBox.h"

MenuIGS :: MenuIGS(Map* pMap, const Camera* pCamera, Cursor* pCursor, GameInfo* pGameInfo, NE::SpriteFactory* const pSF, const USize2& winSize)
    :InGameState(pMap,pCamera,pCursor,pGameInfo)
{
    pUIMenu = new MenuBox(pSF,pMap->getTheme(),winSize);
    if ( pUIMenu == NULL )
    {
        NEError << "Fail to allocate MenuBox\n";
        throw std::bad_alloc();
    }

    pUIMenu->add("EndTurnAction",pMap->getTheme()->getUIItem("endTurnIcon")->getSprite(),"End turn");
    pUIMenu->add("QuitAction",NULL,"Quit");
}

MenuIGS :: ~MenuIGS()
{
    delete pUIMenu;
}

bool MenuIGS :: draw(NE::Renderer* pRenderer, unsigned int time)
{
    bool bResult = true;

    bResult &= MapDrawer::drawUnits(*pRenderer,pMap,*pCamera,time);
    bResult &= pUIMenu->draw(*pRenderer,pCursor->getPosition(),time);

    return bResult;
}

IGState MenuIGS :: update(NE::InputManager* pInputManager, unsigned int time)
{
    (void)time;

    pUIMenu->update(pInputManager->getDirectionsPressed(0));
    if ( pInputManager->getButtonState(0,NE::InputManager::INPUT_X) == NE::InputManager::BS_JUSTPRESSED )
    {
        // Check what is in
        std::string menuSelection = pUIMenu->getSelectedActionName();
        if ( menuSelection == "EndTurnAction" )
        {
            this->pMap->enableUnits();
            this->pGameInfo->nextFaction(pMap);
            return IGS_Idle;
        }
        else if ( menuSelection == "QuitAction" )
        {
            return IGS_Quit;
        }
        else
        {
            NEWarning << "Not implemented action '" << menuSelection << "' in GS_MENU state\n";
        }
    }
    else if ( pInputManager->getButtonState(0,NE::InputManager::INPUT_Y) == NE::InputManager::BS_JUSTPRESSED )
    {
        return IGS_Idle;
    }

    return IGS_Menu;
}
