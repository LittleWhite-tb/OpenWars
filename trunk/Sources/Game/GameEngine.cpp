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

#include "../UI/ConstructBox.h"

#include "../Engine/VTime.h"

#include "../Engine/Controls/Keyboard.h"

#include "../Utils/Logger.h"
#include "../globals.h"

GameEngine :: GameEngine(void)
:Engine(),pMap(NULL),pC(NULL),pCam(NULL),gState(GS_VISU)
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

	// Prepare the data to put in the Construction Box for the Factory
	std::vector<ConstructUnitView> factoryUnits;
	{
		Unit u = pMap->getUnit(UT_R_INFANTRY);
		factoryUnits.push_back(ConstructUnitView(UT_R_INFANTRY,u.pASprite,u.name,u.price));
		u = pMap->getUnit(UT_R_BAZOOKA);
		factoryUnits.push_back(ConstructUnitView(UT_R_BAZOOKA,u.pASprite,u.name,u.price));
		u = pMap->getUnit(UT_R_RECON);
		factoryUnits.push_back(ConstructUnitView(UT_R_RECON,u.pASprite,u.name,u.price));
		u = pMap->getUnit(UT_R_TANK);
		factoryUnits.push_back(ConstructUnitView(UT_R_TANK,u.pASprite,u.name,u.price));
		u = pMap->getUnit(UT_R_TANKM);
		factoryUnits.push_back(ConstructUnitView(UT_R_TANKM,u.pASprite,u.name,u.price));
		u = pMap->getUnit(UT_R_NEOTANK);
		factoryUnits.push_back(ConstructUnitView(UT_R_NEOTANK,u.pASprite,u.name,u.price));
		u = pMap->getUnit(UT_R_APC);
		factoryUnits.push_back(ConstructUnitView(UT_Y_APC,u.pASprite,u.name,u.price));
		u = pMap->getUnit(UT_R_ARTILLERY);
		factoryUnits.push_back(ConstructUnitView(UT_R_ARTILLERY,u.pASprite,u.name,u.price));
		u = pMap->getUnit(UT_R_ROCKETS);
		factoryUnits.push_back(ConstructUnitView(UT_R_ROCKETS,u.pASprite,u.name,u.price));
		u = pMap->getUnit(UT_R_ANTIAIR);
		factoryUnits.push_back(ConstructUnitView(UT_R_ANTIAIR,u.pASprite,u.name,u.price));
		u = pMap->getUnit(UT_R_MISSILES);
		factoryUnits.push_back(ConstructUnitView(UT_R_MISSILES,u.pASprite,u.name,u.price));
	}
	pCBFactory = new ConstructBox(*pSM,*pFM,*pWin,GFX_PATH "constBackground.png",GFX_PATH "constCursor.png",GFX_PATH "upArrow.png",GFX_PATH "downArrow.png", "./data/fonts/times.ttf",factoryUnits);

	// Prepare the data to put in the Construction Box for the Port
	std::vector<ConstructUnitView> portUnits;
	{
		Unit u = pMap->getUnit(UT_R_BOMBERSHIP);
		portUnits.push_back(ConstructUnitView(UT_R_BOMBERSHIP,u.pASprite,u.name,u.price));
		u = pMap->getUnit(UT_R_CRUISER);
		portUnits.push_back(ConstructUnitView(UT_R_CRUISER,u.pASprite,u.name,u.price));
		u = pMap->getUnit(UT_R_LANDER);
		portUnits.push_back(ConstructUnitView(UT_R_LANDER,u.pASprite,u.name,u.price));
		u = pMap->getUnit(UT_R_SUB);
		portUnits.push_back(ConstructUnitView(UT_R_SUB,u.pASprite,u.name,u.price));		
	}
	pCBPort = new ConstructBox(*pSM,*pFM,*pWin,GFX_PATH "constBackground.png",GFX_PATH "constCursor.png",GFX_PATH "upArrow.png",GFX_PATH "downArrow.png", "./data/fonts/times.ttf",portUnits);

	// Prepare the data to put in the Construction Box for the Port
	std::vector<ConstructUnitView> airportUnits;
	{
		Unit u = pMap->getUnit(UT_R_FIGHTER);
		airportUnits.push_back(ConstructUnitView(UT_R_FIGHTER,u.pASprite,u.name,u.price));
		u = pMap->getUnit(UT_R_BOMBER);
		airportUnits.push_back(ConstructUnitView(UT_R_BOMBER,u.pASprite,u.name,u.price));
		u = pMap->getUnit(UT_R_COPTER);
		airportUnits.push_back(ConstructUnitView(UT_R_COPTER,u.pASprite,u.name,u.price));
		u = pMap->getUnit(UT_R_TCOPTER);
		airportUnits.push_back(ConstructUnitView(UT_R_TCOPTER,u.pASprite,u.name,u.price));		
	}
	pCBAirport = new ConstructBox(*pSM,*pFM,*pWin,GFX_PATH "constBackground.png",GFX_PATH "constCursor.png",GFX_PATH "upArrow.png",GFX_PATH "downArrow.png", "./data/fonts/times.ttf",airportUnits);

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
		
		switch ( gState )
		{
			case GS_VISU:
				{
					pC->draw(*pRenderer,*pCam,pVT->getTime());
				}
				break;
			case GS_FACTORY:
				{
					pCBFactory->draw(*pRenderer);
				}
				break;
			case GS_PORT:
				{
					pCBPort->draw(*pRenderer);
				}
				break;
			case GS_AIRPORT:
				{
					pCBAirport->draw(*pRenderer);
				}
				break;
		}

		SDL_UpdateRect(pWin->getWindowSurface(),0,0,0,0);

		// Update part
		if ( pVT->canUpdate() )
		{
			pCam->update(*pC,*pMap);
			pKB->update();

			switch ( gState )
			{
				case GS_VISU:
					{
						pC->move(pKB->getDirectionPressed());
						if ( pKB->isKey(SDLK_SPACE) )
						{
							if ( pC->getTileTypeUnderCursor() == TT_Red_Factory )
							{
								this->gState = GS_FACTORY;
							}
							else if ( pC->getTileTypeUnderCursor() == TT_Red_Airport )
							{
								this->gState = GS_AIRPORT;
							}
							else if ( pC->getTileTypeUnderCursor() == TT_Red_Port )
							{
								this->gState = GS_PORT;
							}
						}
					}
					break;
				case GS_FACTORY:
					{
						pCBFactory->update(pKB->getDirectionPressed());
						if ( pKB->isKey(SDLK_SPACE) )
						{
							pMap->setTile(pC->getPosition(),pCBFactory->getUnitSelected());
							this->gState = GS_VISU;
						}
					}
					break;
				case GS_PORT:
					{
						pCBPort->update(pKB->getDirectionPressed());
						if ( pKB->isKey(SDLK_SPACE) )
						{
							pMap->setTile(pC->getPosition(),pCBPort->getUnitSelected());
							this->gState = GS_VISU;
						}
					}
					break;
				case GS_AIRPORT:
					{
						pCBAirport->update(pKB->getDirectionPressed());
						if ( pKB->isKey(SDLK_SPACE) )
						{
							pMap->setTile(pC->getPosition(),pCBAirport->getUnitSelected());
							this->gState = GS_VISU;
						}
					}
					break;
			}
		}

		pVT->waitNextFrame();
	}

	return true;
}

