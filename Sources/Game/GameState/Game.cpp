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

#include "Game.h"

#include "NEngine/NEngine.h"
#include "NEngine/Window.h"

#include "Game/GameState/GameObjects/Map/Map.h"
#include "Game/GameState/GameObjects/Map/MapLoader.h"
#include "Game/GameState/GameObjects/Map/MapDrawer.h"
#include "Game/GameState/GameObjects/Cursor.h"
#include "Game/GameState/GameObjects/Camera.h"

#include "Game/GameState/InGameStates/IdleIGS.h"
#include "Game/GameState/InGameStates/ConstructionIGS.h"
#include "Game/GameState/InGameStates/MenuIGS.h"
#include "Game/GameState/InGameStates/UnitSelectIGS.h"
#include "Game/GameState/InGameStates/AttackMapIGS.h"

#include "NEngine/Exceptions/ConstructionFailedException.h"
#include "globals.h"

Game :: Game()
:pMap(NULL),pCamera(NULL),pCursor(NULL),gameInfo(GameInfo(2,10000)),igState(IGS_Idle)
{
    NE::NEngine::logger()->log(NE::LL_Debug,"GameEngine constructed");
}

Game :: ~Game(void)
{
	for ( std::map<IGState, InGameState*>::iterator itIGS = states.begin() ; itIGS != states.end() ; ++itIGS )
	{
		delete itIGS->second;
	}
	states.clear();

    delete pCursor;
	delete pCamera;
	delete pMap;

    NE::NEngine::logger()->log(NE::LL_Debug,"GameEngine deleted");
}

bool Game :: load(NE::NEngine* pNE)
{
	pCamera = new Camera();
    pCursor = new Cursor(pMap,UVec2(5,5));

	if ( pCamera == NULL || pCursor == NULL )
	{
		return false;
	}

    try
    {
        states[IGS_Idle] = new IdleIGS(pMap,pCamera,pCursor,&gameInfo,pNE->getWindow()->getWindowSize());
		states[IGS_Construction] = new ConstructionIGS(pMap,pCamera,pCursor,&gameInfo);
		states[IGS_Menu] = new MenuIGS(pMap,pCamera,pCursor,&gameInfo,pNE->getSpriteFactory(),pNE->getWindow()->getWindowSize());
		states[IGS_UnitSelected] = new UnitSelectIGS(pMap,pCamera,pCursor,&gameInfo);
		states[IGS_AttackMap] = new AttackMapIGS(pMap,pCamera,pCursor,&gameInfo);
    }
    catch (ConstructionFailedException& cfe)
    {
        NE::NEngine::logger()->log(NE::LL_Error,"%s",cfe.what());
        return false;
    }

    return true;
}

bool Game :: loadMap(const Library<Theme>* const pThemes,const std::string& name)
{
	delete pMap;

	pMap = MapLoader::loadMapFromFile(pThemes,name);
	if ( pMap == NULL )
	{
        NE::NEngine::logger()->log(NE::LL_Error,"Fail to load map '%s'",name);
		return false;
	}

	return true;
}

bool Game :: draw(NE::Renderer* pRenderer, unsigned int time)
{
	bool bResult = true;
	// Drawing part
	bResult &= MapDrawer::drawTerrain(*pRenderer,pMap,*pCamera,time);

	bResult &= states[igState]->draw(pRenderer,time);

	return bResult;
}

bool Game :: update(NE::InputManager::ArrowsDirection direction, NE::InputManager::Buttons buttons, unsigned int time)
{
	(void) time;

    pCamera->update(*pCursor,*pMap);

	IGState oldIGState = igState;
	igState = states[igState]->update(direction,buttons,time);
	if ( igState == IGS_Quit )
	{
		return false;
	}
	if ( oldIGState != igState ) // New state, make transition by initialising the new state
	{
		states[igState]->init();
	}
	
     
    return true;
}

