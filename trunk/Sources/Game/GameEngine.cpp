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

#include "../NEngine/NEngine.h"
#include "../NEngine/Window.h"
#include "../NEngine/Renderer.h"
#include "../NEngine/SpriteLoader.h"
#include "../NEngine/InputManager.h"

#include "MapGame.h"
#include "Cursor.h"
#include "Camera.h"

#include "UI/ConstructBox.h"
#include "UI/MenuBox.h"

#include "Engine/Theme.h"
#include "Engine/VTime.h"

#include "Types/Colour.h"

#include "Utils/Logger.h"
#include "NEngine/Exceptions/ConstructionFailedException.h"
#include "NEngine/Exceptions/FileNotFoundException.h"
#include "globals.h"

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
		const UnitTemplate* pU = pMap->getTheme()->getUnit("INFANTRY",0);
		factoryUnits.push_back(ConstructUnitView(pU,pU->getSprite(),pU->getName(),pU->getPrice()));
		pU = pMap->getTheme()->getUnit("BAZOOKA",0);
		factoryUnits.push_back(ConstructUnitView(pU,pU->getSprite(),pU->getName(),pU->getPrice()));
		pU = pMap->getTheme()->getUnit("RECON",0);
		factoryUnits.push_back(ConstructUnitView(pU,pU->getSprite(),pU->getName(),pU->getPrice()));
		pU = pMap->getTheme()->getUnit("TANK",0);
		factoryUnits.push_back(ConstructUnitView(pU,pU->getSprite(),pU->getName(),pU->getPrice()));
		pU = pMap->getTheme()->getUnit("TANKM",0);
		factoryUnits.push_back(ConstructUnitView(pU,pU->getSprite(),pU->getName(),pU->getPrice()));
		pU = pMap->getTheme()->getUnit("NEOTANK",0);
		factoryUnits.push_back(ConstructUnitView(pU,pU->getSprite(),pU->getName(),pU->getPrice()));
		pU = pMap->getTheme()->getUnit("APC",0);
		factoryUnits.push_back(ConstructUnitView(pU,pU->getSprite(),pU->getName(),pU->getPrice()));
		pU = pMap->getTheme()->getUnit("ARTILLERY",0);
		factoryUnits.push_back(ConstructUnitView(pU,pU->getSprite(),pU->getName(),pU->getPrice()));
		pU = pMap->getTheme()->getUnit("ROCKETS",0);
		factoryUnits.push_back(ConstructUnitView(pU,pU->getSprite(),pU->getName(),pU->getPrice()));
		pU = pMap->getTheme()->getUnit("ANTIAIR",0);
		factoryUnits.push_back(ConstructUnitView(pU,pU->getSprite(),pU->getName(),pU->getPrice()));
		pU = pMap->getTheme()->getUnit("MISSILES",0);
		factoryUnits.push_back(ConstructUnitView(pU,pU->getSprite(),pU->getName(),pU->getPrice()));
	}

	// Prepare the data to put in the Construction Box for the Port
	std::vector<ConstructUnitView> portUnits;
	{
		const UnitTemplate* pU = pMap->getTheme()->getUnit("BOMBERSHIP",0);
		portUnits.push_back(ConstructUnitView(pU,pU->getSprite(),pU->getName(),pU->getPrice()));
		pU = pMap->getTheme()->getUnit("CRUISER",0);
		portUnits.push_back(ConstructUnitView(pU,pU->getSprite(),pU->getName(),pU->getPrice()));
		pU = pMap->getTheme()->getUnit("LANDER",0);
		portUnits.push_back(ConstructUnitView(pU,pU->getSprite(),pU->getName(),pU->getPrice()));
		pU = pMap->getTheme()->getUnit("SUB",0);
		portUnits.push_back(ConstructUnitView(pU,pU->getSprite(),pU->getName(),pU->getPrice()));		
	}

	// Prepare the data to put in the Construction Box for the Port
	std::vector<ConstructUnitView> airportUnits;
	{
		const UnitTemplate* pU = pMap->getTheme()->getUnit("FIGHTER",0);
		airportUnits.push_back(ConstructUnitView(pU,pU->getSprite(),pU->getName(),pU->getPrice()));
		pU = pMap->getTheme()->getUnit("BOMBER",0);
		airportUnits.push_back(ConstructUnitView(pU,pU->getSprite(),pU->getName(),pU->getPrice()));
		pU = pMap->getTheme()->getUnit("COPTER",0);
		airportUnits.push_back(ConstructUnitView(pU,pU->getSprite(),pU->getName(),pU->getPrice()));
		pU = pMap->getTheme()->getUnit("TCOPTER",0);
		airportUnits.push_back(ConstructUnitView(pU,pU->getSprite(),pU->getName(),pU->getPrice()));		
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
	pMap = new MapGame(&themeLibrary);
	if ( pMap == NULL )
	{
		LError << "Fail to allocate memory for Map";
		return false;
	}

	if ( pMap->load(mapName) == false )
	{
		return false;
	}

	try
	{
		return this->load();
	}
	catch ( FileNotFoundException& fnfe )
	{
		return false;
	}
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
							const Unit* currentUT = pMap->getUnit(pC->getPosition());
							if ( currentUT == NULL )
							{
								if ( pC->getTileUnderCursor()->getName() == "TT_Red_Factory" )
								{
									this->gState = GS_FACTORY;
								}
								else if ( pC->getTileUnderCursor()->getName() == "TT_Red_Airport" )
								{
									this->gState = GS_AIRPORT;
								}
								else if ( pC->getTileUnderCursor()->getName() == "TT_Red_Port" )
								{
									this->gState = GS_PORT;
								}
								else
								{
                                    pMBMenu->setMenus(menuEntries);
									this->gState = GS_MENU;
								}
							}
							else if ( !pMap->getUnit(pC->getPosition())->state == US_ACTIVE )
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
							pMap->setUnit(pC->getPosition(),pCBFactory->getUnitSelected()->getName(),0);
							this->gState = GS_VISU;
						}
					}
					break;
				case GS_PORT:
					{
						pCBPort->update(direction);
						if ( (buttons & NE::InputManager::INPUT_X) == NE::InputManager::INPUT_X )
						{
							pMap->setUnit(pC->getPosition(),pCBPort->getUnitSelected()->getName(),0);
							this->gState = GS_VISU;
						}
					}
					break;
				case GS_AIRPORT:
					{
						pCBAirport->update(direction);
						if ( (buttons & NE::InputManager::INPUT_X) == NE::InputManager::INPUT_X )
						{
							pMap->setUnit(pC->getPosition(),pCBAirport->getUnitSelected()->getName(),0);
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
                                    unsigned int movement = pUnitSelected->getTemplate()->getMovement();
									if ( pUnitSelected->fuel < movement)
                                    {
                                        movement = pUnitSelected->fuel;
                                    }
                                    // pMap->setMoveHighlight(selectedUnitPosition,*pUnitSelected,movement);
                                    
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
                                // pMap->clearHighlight();
                                this->gState = GS_VISU;
                            }
                        }
                        else if ( (buttons & NE::InputManager::INPUT_B) == NE::InputManager::INPUT_B )
						{
                            // pMap->clearHighlight();
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

