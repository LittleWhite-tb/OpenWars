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

#include "GameEngine.h"

#include <cassert>

#include "NEngine/NEngine.h"
#include "NEngine/Window.h"
#include "NEngine/Renderer.h"
#include "NEngine/SpriteLoader.h"
#include "NEngine/Time.h"

#include "Engine/ThemeLoader.h"
#include "Engine/Theme.h"

#include "Game/GameState/Game.h"
#include "Game/GameState/Editor.h"

#include "XML/XMLListReader.h"

#include "GameOption.h"

#include "ow_globals.h"

GameEngine :: GameEngine(NE::NEngine* pNE, const GameOption* pGameOptions)
    :pNE(pNE),pGameOptions(pGameOptions),fpsNumber(0),fpsCounter(0),fpsLastUpdateTime(0),lastUpdateTime(0),bIsRunning(true)
{
    assert(pNE);
    assert(pGameOptions);

    NEDebug << "GameEngine started\n";
}

GameEngine :: ~GameEngine()
{
    delete pGame;

    NEDebug << "GameEngine stopped\n";
}

bool GameEngine :: init(void)
{
    pNE->getSpriteLoader()->setTransparencyColour(Colour(255,0,255));

    if ( pGameOptions->editorMode )
    {
        pGame = new Editor();
    }
    else
    {
        pGame = new Game();
    }

    if ( pGame == NULL )
    {
        NEError << "Fail to allocate memory for game state\n";
        return false;
    }

    return true;
}

bool GameEngine :: load(void)
{
    bool bResult = true;

    try
    {
        ThemeLoader::loadThemeList(pNE->getSpriteLoader(),THEME_PATH + "themeList.xml",&themeLibrary);

        bResult &= pGame->load(pNE,&themeLibrary,pGameOptions);
    }
    catch (LibraryException& le)
    {
        NEError << le.what() << "\n";
        return false;
    }
    catch (EngineException& ee)
    {
        NEError << ee.what() << "\n";
        return false;
    }

    return bResult;
}

bool GameEngine :: render()
{
    pGame->draw(pNE->getRenderer(),pNE->getTime()->getTime());

    if ( pNE->getRenderer()->updateWindow() == false )
    {
        NEError << "Fail to draw on the screen\n";
    }

    return true;
}

bool GameEngine :: update()
{
    pNE->getInputManager()->update();
    return pGame->update(pNE->getInputManager(),pNE->getTime()->getTime());
}

void GameEngine :: run(void)
{
    bool bResult = true;

    while ( bIsRunning && pNE->getInputManager()->needEscape() == false && pNE->getWindow()->needWindowClosure() == false && bResult == true )
    {
        bResult &= this->render();
        // This solve a problem in Windows, because the events have to be updated in the same thread than the video.
        unsigned int actualTime = pNE->getTime()->getTime();
        if ( actualTime - lastUpdateTime > 75 )
        {
            bResult &= this->update();
            lastUpdateTime = pNE->getTime()->getTime();
        }

        // FPS management
        fpsCounter++;
        if ( actualTime - fpsLastUpdateTime > 1000 ) // After one second
        {
            fpsNumber= fpsCounter;
            fpsCounter = 0;
            fpsLastUpdateTime = pNE->getTime()->getTime();

            NELog(0) << "FPS: " << fpsNumber << "\n";
        }
    }
}
