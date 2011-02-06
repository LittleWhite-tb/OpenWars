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

#include "../NEngine/NEngine.h"
#include "../NEngine/Window.h"
#include "../NEngine/Renderer.h"
#include "../NEngine/SpriteLoader.h"
#include "../NEngine/InputManager.h"

#include "MapGame.h"
#include "Cursor.h"
#include "Camera.h"

#include "../UI/ConstructBox.h"
#include "../UI/MenuBox.h"

#include "../Engine/VTime.h"

#include "../Types/Colour.h"

#include "../Utils/Logger.h"
#include "../Utils/Exceptions/ConstructionFailedException.h"
#include "../globals.h"

GameEngine :: GameEngine(NE::NEngine* const pNE)
:Engine(pNE),pMap(NULL),pC(NULL),pCam(NULL),pCBFactory(NULL),pCBPort(NULL),pCBAirport(NULL),pMBMenu(NULL),gState(GS_VISU),selectedUnitPosition(0,0),m_userQuit(false)
{
	LDebug << "GameEngine constructed";
}

GameEngine :: ~GameEngine(void)
{
    for ( std::vector<MenuView*>::iterator itMenuView = menuEntries.begin() ; itMenuView != menuEntries.end() ; ++itMenuView )
    {
        delete *itMenuView;
    }
    
    for ( std::vector<MenuView*>::iterator itMenuView = unitMenuEntries.begin() ; itMenuView != unitMenuEntries.end() ; ++itMenuView )
    {
        delete *itMenuView;
    }
    
	delete pMBMenu;

	delete pCBAirport;
	delete pCBPort;
	delete pCBFactory;

	delete pCam;
	delete pC;
	delete pMap;

	LDebug << "GameEngine deleted";
}

bool GameEngine :: load(void)
{
	pC = new Cursor(pNE->getSpriteLoader(),"./data/gfx/cursor.png",pMap,UVec2(5,5));
	pCam = new Camera();

	// Prepare the data to put in the Construction Box for the Factory
	std::vector<ConstructUnitView> factoryUnits;
	{
		UnitTemplate u = pMap->getUnitTemplate(UT_R_INFANTRY);
		factoryUnits.push_back(ConstructUnitView(UT_R_INFANTRY,u.pASprite,u.name,u.price));
		u = pMap->getUnitTemplate(UT_R_BAZOOKA);
		factoryUnits.push_back(ConstructUnitView(UT_R_BAZOOKA,u.pASprite,u.name,u.price));
		u = pMap->getUnitTemplate(UT_R_RECON);
		factoryUnits.push_back(ConstructUnitView(UT_R_RECON,u.pASprite,u.name,u.price));
		u = pMap->getUnitTemplate(UT_R_TANK);
		factoryUnits.push_back(ConstructUnitView(UT_R_TANK,u.pASprite,u.name,u.price));
		u = pMap->getUnitTemplate(UT_R_TANKM);
		factoryUnits.push_back(ConstructUnitView(UT_R_TANKM,u.pASprite,u.name,u.price));
		u = pMap->getUnitTemplate(UT_R_NEOTANK);
		factoryUnits.push_back(ConstructUnitView(UT_R_NEOTANK,u.pASprite,u.name,u.price));
		u = pMap->getUnitTemplate(UT_R_APC);
		factoryUnits.push_back(ConstructUnitView(UT_R_APC,u.pASprite,u.name,u.price));
		u = pMap->getUnitTemplate(UT_R_ARTILLERY);
		factoryUnits.push_back(ConstructUnitView(UT_R_ARTILLERY,u.pASprite,u.name,u.price));
		u = pMap->getUnitTemplate(UT_R_ROCKETS);
		factoryUnits.push_back(ConstructUnitView(UT_R_ROCKETS,u.pASprite,u.name,u.price));
		u = pMap->getUnitTemplate(UT_R_ANTIAIR);
		factoryUnits.push_back(ConstructUnitView(UT_R_ANTIAIR,u.pASprite,u.name,u.price));
		u = pMap->getUnitTemplate(UT_R_MISSILES);
		factoryUnits.push_back(ConstructUnitView(UT_R_MISSILES,u.pASprite,u.name,u.price));
	}

	// Prepare the data to put in the Construction Box for the Port
	std::vector<ConstructUnitView> portUnits;
	{
		UnitTemplate u = pMap->getUnitTemplate(UT_R_BOMBERSHIP);
		portUnits.push_back(ConstructUnitView(UT_R_BOMBERSHIP,u.pASprite,u.name,u.price));
		u = pMap->getUnitTemplate(UT_R_CRUISER);
		portUnits.push_back(ConstructUnitView(UT_R_CRUISER,u.pASprite,u.name,u.price));
		u = pMap->getUnitTemplate(UT_R_LANDER);
		portUnits.push_back(ConstructUnitView(UT_R_LANDER,u.pASprite,u.name,u.price));
		u = pMap->getUnitTemplate(UT_R_SUB);
		portUnits.push_back(ConstructUnitView(UT_R_SUB,u.pASprite,u.name,u.price));		
	}

	// Prepare the data to put in the Construction Box for the Port
	std::vector<ConstructUnitView> airportUnits;
	{
		UnitTemplate u = pMap->getUnitTemplate(UT_R_FIGHTER);
		airportUnits.push_back(ConstructUnitView(UT_R_FIGHTER,u.pASprite,u.name,u.price));
		u = pMap->getUnitTemplate(UT_R_BOMBER);
		airportUnits.push_back(ConstructUnitView(UT_R_BOMBER,u.pASprite,u.name,u.price));
		u = pMap->getUnitTemplate(UT_R_COPTER);
		airportUnits.push_back(ConstructUnitView(UT_R_COPTER,u.pASprite,u.name,u.price));
		u = pMap->getUnitTemplate(UT_R_TCOPTER);
		airportUnits.push_back(ConstructUnitView(UT_R_TCOPTER,u.pASprite,u.name,u.price));		
	}
	
	try
	{
		// Prepare the data for the basic menu
        menuEntries.push_back(new MenuView("End turn",ME_EndTurn,new AnimatedSprite(pNE->getSpriteLoader()->loadSpriteFromFile(GFX_PATH "endTurnIcon.png"),USize2(32,32),200)));
        menuEntries.push_back(new MenuView("Quit",ME_Quit,NULL));
        
        // Unit menu
        unitMenuEntries.push_back(new MenuView("Move",ME_Move,NULL));

		pCBFactory = new ConstructBox(pNE->getSpriteLoader(),GFX_PATH "constBackground.png",GFX_PATH "constCursor.png",GFX_PATH "upArrow.png",GFX_PATH "downArrow.png", "./data/fonts/font.png",factoryUnits, pNE->getWindow()->getWindowSize());
		pCBPort = new ConstructBox(pNE->getSpriteLoader(),GFX_PATH "constBackground.png",GFX_PATH "constCursor.png",GFX_PATH "upArrow.png",GFX_PATH "downArrow.png", "./data/fonts/font.png",portUnits, pNE->getWindow()->getWindowSize());
		pCBAirport = new ConstructBox(pNE->getSpriteLoader(),GFX_PATH "constBackground.png",GFX_PATH "constCursor.png",GFX_PATH "upArrow.png",GFX_PATH "downArrow.png", "./data/fonts/font.png",airportUnits, pNE->getWindow()->getWindowSize());
		pMBMenu = new MenuBox(pNE->getSpriteLoader(),pNE->getSpriteFactory(), GFX_PATH "constCursor.png","./data/fonts/font.png",menuEntries,pNE->getWindow()->getWindowSize());
	}
	catch (ConstructionFailedException& cfe)
	{
		LError << cfe.what();
		return false;
    }

	return true;
}

bool GameEngine :: init(void)
{
	bool error = true;

	error = Engine::init();

	LDebug << "GameEngine init'd";

	return error;
}

bool GameEngine :: load(const std::string& mapName)
{
	pMap = new MapGame(pNE->getSpriteLoader(), mapName, GFX_PATH "highlight.png",GFX_PATH "highlightAttack.png");
	if ( !pMap->isValidMap() )
	{
		return false;
	}

	return this->load();
}

bool GameEngine :: run(void)
{
	while ( pNE->getInputManager()->needEscape() == false && pNE->getWindow()->needWindowClosure() == 0 && m_userQuit == false )
	{
		// Drawing part
		pNE->getRenderer()->clearScreen(Colour(0,0,0));

		pMap->draw(*pNE->getRenderer(),*pCam,pVT->getTime());
		
		switch ( gState )
		{
			case GS_VISU:
				{
					pC->draw(*pNE->getRenderer(),*pCam,pVT->getTime());
				}
				break;
			case GS_FACTORY:
				{
					pCBFactory->draw(*pNE->getRenderer(),5000);
				}
				break;
			case GS_PORT:
				{
					pCBPort->draw(*pNE->getRenderer(),5000);
				}
				break;
			case GS_AIRPORT:
				{
					pCBAirport->draw(*pNE->getRenderer(),5000);
				}
				break;
            case GS_SELECT:
                {
                    pMBMenu->draw(*pNE->getRenderer(),pC->getPosition(),pVT->getTime());
                }
                break;
            case GS_MOVE:
                {
                    // TODO: Display the move map stuff
                    pC->draw(*pNE->getRenderer(),*pCam,pVT->getTime());
                }
                break;
			case GS_MENU:
				{
					pMBMenu->draw(*pNE->getRenderer(),pC->getPosition(),pVT->getTime());
				}
				break;
		}

		pNE->getRenderer()->updateWindow();

		// Update part
		if ( pVT->canUpdate() )
		{
            NE::InputManager::ArrowsDirection direction = pNE->getInputManager()->getDirectionsPressed();
            NE::InputManager::Buttons buttons = pNE->getInputManager()->getButtonsPressed();
            
			pCam->update(*pC,*pMap);
			pNE->getInputManager()->update();

			switch ( gState )
			{
				case GS_VISU:
					{
						pC->move(direction);
						if ( (buttons & NE::InputManager::INPUT_X) == NE::InputManager::INPUT_X )
						{
							UnitType currentUT = pMap->getUnitType(pC->getPosition());
							if ( currentUT == UT_NO_UNIT )
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
								else
								{
                                    pMBMenu->setMenus(menuEntries);
									this->gState = GS_MENU;
								}
							}
							else if ( !pMap->getUnit(pC->getPosition())->enabled )
							{
                                pMBMenu->setMenus(menuEntries);
								this->gState = GS_MENU;
							}
							else
							{
                                pMBMenu->setMenus(unitMenuEntries);
                                this->gState = GS_SELECT;
                            }
							
						}
					}
					break;
				case GS_FACTORY:
					{
						pCBFactory->update(direction);
						if ( (buttons & NE::InputManager::INPUT_X) == NE::InputManager::INPUT_X )
						{
							pMap->setTile(pC->getPosition(),pCBFactory->getUnitSelected());
							this->gState = GS_VISU;
						}
					}
					break;
				case GS_PORT:
					{
						pCBPort->update(direction);
						if ( (buttons & NE::InputManager::INPUT_X) == NE::InputManager::INPUT_X )
						{
							pMap->setTile(pC->getPosition(),pCBPort->getUnitSelected());
							this->gState = GS_VISU;
						}
					}
					break;
				case GS_AIRPORT:
					{
						pCBAirport->update(direction);
						if ( (buttons & NE::InputManager::INPUT_X) == NE::InputManager::INPUT_X )
						{
							pMap->setTile(pC->getPosition(),pCBAirport->getUnitSelected());
							this->gState = GS_VISU;
						}
					}
					break;
				case GS_MENU:
					{
						pMBMenu->update(direction);
						if ( (buttons & NE::InputManager::INPUT_X) == NE::InputManager::INPUT_X )
						{
							// Check what is in 
							switch (pMBMenu->getActualEntry())
							{
								case (ME_EndTurn):
								{
									// ToDo Change turn.
									this->pMap->enableUnits();
									this->gState = GS_VISU;
								}
								break;
								case (ME_Quit):
								{
									m_userQuit = true;
								}
								break;
							}
						}
						else if ( (buttons & NE::InputManager::INPUT_B) == NE::InputManager::INPUT_B )
						{
							this->gState = GS_VISU;
						}
					}
					break;
                case GS_SELECT:
                    {
                        pMBMenu->update(direction);
						if ( (buttons & NE::InputManager::INPUT_X) == NE::InputManager::INPUT_X )
						{
                            // Check what is in 
							switch (pMBMenu->getActualEntry())
							{
								case (ME_Move):
								{
									// ToDo Change turn.
									// this->pMap->moveUnit();
                                    selectedUnitPosition = pC->getPosition();
                                    
                                    // If the unit has not enough fuel ... we will move the unit only of the distance possible with the fuel
                                    const Unit* pUnitSelected = pMap->getUnit(selectedUnitPosition);
                                    int movement = pMap->getUnitTemplate(pUnitSelected->type).movement;
                                    if ( pUnitSelected->fuel < pMap->getUnitTemplate(pUnitSelected->type).movement)
                                    {
                                        movement = pUnitSelected->fuel;
                                    }
                                    pMap->setMoveHighlight(selectedUnitPosition,pUnitSelected->type,movement);
                                    
									this->gState = GS_MOVE;
								}
								break;
							}
                        }
                        else if ( (buttons & NE::InputManager::INPUT_B) == NE::InputManager::INPUT_B )
						{
							this->gState = GS_VISU;
						}
                    }
                    break;
                case GS_MOVE:
                    {
                        pC->move(direction);
                        if ( (buttons & NE::InputManager::INPUT_X) == NE::InputManager::INPUT_X )
						{
                            if ( this->pMap->move(selectedUnitPosition, pC->getPosition()) )
                            {
                                pMap->clearHighlight();
                                this->gState = GS_VISU;
                            }
                        }
                        else if ( (buttons & NE::InputManager::INPUT_B) == NE::InputManager::INPUT_B )
						{
                            pMap->clearHighlight();
							this->gState = GS_SELECT;
						}
                    }
                    break;
			}
		}

		pVT->waitNextFrame();
	}

	return true;
}

