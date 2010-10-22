#ifndef DOXYGEN_IGNORE_TAG
/**
OpenAWars is an open turn by turn strategic game aiming to recreate the feeling of advance (famicon) wars (c)
Copyright (C) 2010  Alexandre LAURENT

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

#include "Map.h"
#include "Cursor.h"
#include "Camera.h"

#include "../Engine/VTime.h"

#include "../Engine/Controls/Keyboard.h"

#include "../Utils/Logger.h"

GameEngine :: GameEngine(void)
:Engine(),pMap(NULL),pC(NULL),pCam(NULL)
{
	LDebug << "GameEngine constructed";
}

GameEngine :: ~GameEngine(void)
{
	delete pCam;
	delete pC;
	delete pMap;

	LDebug << "GameEngine deleted";
}

bool GameEngine :: load(void)
{
	pC = new Cursor(*pSM,"./data/gfx/cursor.png",pMap,UVec2(5,5));
	pCam = new Camera();

	return true;
}

bool GameEngine :: init(const Window* pWin, const RenderingAPI rAPI)
{
	bool error = true;

	error = Engine::init(pWin,rAPI);

	LDebug << "GameEngine init'd";

	return error;
}

bool GameEngine :: load(const std::string& mapName)
{
	pMap = new Map(*pSM , mapName);
	if ( !pMap->isValidMap() )
	{
		return false;
	}

	return this->load();
}

bool GameEngine :: run(void)
{
	while ( pKB->isEscapePressed() == 0 && pWin->needClosure() == 0 )
	{
		// Drawing part
		pRenderer->clearScreen();

		pMap->draw(*pRenderer,*pCam,pVT->getTime());
		pC->draw(*pRenderer,*pCam,pVT->getTime());

		SDL_UpdateRect(pWin->getWindowSurface(),0,0,0,0);

		// Update part
		if ( pVT->canUpdate() )
		{
			pCam->update(*pC,*pMap);
			pKB->update();

			pC->move(pKB->getDirectionPressed());
		}

		pVT->waitNextFrame();
	}

	return true;
}

