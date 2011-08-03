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

#include "GameEngine.h"

#include "NEngine/NEngine.h"
#include "NEngine/Renderer.h"
#include "NEngine/Time.h"

#include "Engine/Theme.h"

#include "Game/GameState/Game.h"
#include "Game/GameState/Editor.h"

#include "XML/XMLListReader.h"

#include "Utils/Logger.h"
#include "Utils/Exceptions/XMLException.h"

#include "globals.h"

GameEngine :: GameEngine(NE::NEngine* pNE)
	:pNE(pNE),fpsNumber(0),fpsCounter(0),fpsLastUpdateTime(0),lastUpdateTime(0),bIsRunning(true)
{
	LDebug << "GameEngine started";
}
	
GameEngine :: ~GameEngine()
{
	LDebug << "GameEngine stopped";
}

bool GameEngine :: init(void)
{
#ifdef EDITOR
	pGame = new Editor();
#else
	pGame = new Game();
#endif

	if ( pGame == NULL )
	{
		LError << "Fail to allocate memory for game state";
		return false;
	}

	return true;
}

void GameEngine :: loadTheme(const std::string& themeName)
{
    Theme* pTheme = new Theme(themeName);
    if ( pTheme == NULL )
    {
        LError << "Fail to allocate Theme";
        throw std::bad_alloc();
    }

    if ( pTheme->load(pNE->getSpriteLoader()) == false )
    {
        throw EngineException("Failed to load the theme (" + themeName+ ")");
    }
    else
    {
        themeLibrary.add(pTheme->getName(),pTheme);
    }
}

void GameEngine :: loadThemeList(const std::string& listPath)
{
    try
    {
        std::list<std::string> paths;
        XMLListReader xmlReader = XMLListReader(listPath);

        xmlReader.parse("theme",&paths);

        for ( std::list<std::string>::const_iterator itPath = paths.begin() ; itPath != paths.end() ; ++itPath )
        {
            loadTheme(*itPath);
        }
    }
    catch ( XMLParsingFailedException& xmle )
    {
        (void)xmle;
        throw EngineException("Fail to open list of theme paths '" + listPath + "'");
    }
}

bool GameEngine :: load(void)
{
	bool bResult = true;

	this->loadThemeList(THEME_PATH "themeList.xml");
	
#ifdef EDITOR
	bResult &= pGame->loadMap(USize(15,14));
#else
	bResult &= pGame->loadMap(&themeLibrary,MAP_PATH "maw.map");
#endif

	bResult &= pGame->load(pNE);

	return bResult;
}

bool GameEngine :: render()
{
	pGame->draw(pNE->getRenderer(),pNE->getTime()->getTime());

	if ( pNE->getRenderer()->updateWindow() == false )
    {
        LError << "Fail to draw on the screen";
    }

	return true;
}

bool GameEngine :: update()
{
	pNE->getInputManager()->update();

	NE::InputManager::ArrowsDirection directions =pNE->getInputManager()->getDirectionsPressed();
    NE::InputManager::Buttons buttons = pNE->getInputManager()->getButtonsPressed();	

	pGame->update(directions,buttons);

	return true;
}

void GameEngine :: run(void)
{
	while ( bIsRunning )
    {
        this->render();
        // This solve a problem in Windows, because the events have to be updated in the same thread than the video.
		this->update();

		// FPS management
        fpsCounter++;
		if ( pNE->getTime()->getTime() - fpsLastUpdateTime > 1000 ) // After one second
        {
            fpsNumber= fpsCounter;
            fpsCounter = 0;
            fpsLastUpdateTime = pNE->getTime()->getTime();

            std::cout << "FPS: " << fpsNumber << std::endl;
        }

        lastUpdateTime = pNE->getTime()->getTime();
    }
}