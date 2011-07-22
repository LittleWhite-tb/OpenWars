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

#include "Game/Map/Map.h"
#include "Cursor.h"
#include "Camera.h"

#include "UI/ConstructBox.h"
#include "UI/MenuBox.h"

#include "Engine/Theme.h"
#include "Engine/Params.h"
#include "Engine/VTime.h"

#include "Types/Colour.h"

#include "Utils/Logger.h"
#include "NEngine/Exceptions/ConstructionFailedException.h"
#include "NEngine/Exceptions/FileNotFoundException.h"
#include "globals.h"

GameEngine :: GameEngine(NE::NEngine* const pNE)
:Engine(pNE),pC(NULL),pMBMenu(NULL),gState(GS_VISU),selectedUnitPosition(0,0),m_userQuit(false)
{
	LDebug << "GameEngine constructed";
}

GameEngine :: ~GameEngine(void)
{    
	delete pMBMenu;

	for ( std::map<std::string, ConstructBox*>::iterator itPCB = constructionBoxes.begin() ; itPCB != constructionBoxes.end() ; ++itPCB )
	{
		delete itPCB->second;
	}

	delete pC;

	LDebug << "GameEngine deleted";
}

bool GameEngine :: load(void)
{
	pC = new Cursor(pMap,UVec2(5,5));

	std::list<const Tile* > tilesList;
	pMap->getTheme()->getTilesList(&tilesList);

	std::list<const UnitTemplateFactionList* > unitsList;
	pMap->getTheme()->getUnitsList(&unitsList);

	// Construct all the contruction boxes needed by going throw the tile list
	for ( std::list < const Tile* >::const_iterator itPTile = tilesList.begin() ;
				itPTile != tilesList.end() ; ++itPTile )
	{
		const Params* tileParams = (*itPTile)->getParams();
		// For each unique producer name (if existing)
		if ( tileParams->exists("producerName") && 
			 constructionBoxes.find(tileParams->get("producerName")) == constructionBoxes.end() )
		{
			constructionBoxes[tileParams->get("producerName")] = new ConstructBox(pMap->getTheme(),pNE->getWindow()->getWindowSize());
		}
	}

	// For each unit, we get the tile indicated where the unit is produced
	// If not existing, the loading fails
	for ( std::list < const UnitTemplateFactionList* >::const_iterator itPUnit = unitsList.begin() ;
			  itPUnit != unitsList.end() ; ++itPUnit )
	{
		const Params* unitParams = (*itPUnit)->get(0)->getParams();

		if ( unitParams->exists("producedIn") )
		{
			if ( constructionBoxes.find(unitParams->get("producedIn")) != constructionBoxes.end() )
			{
				constructionBoxes[unitParams->get("producedIn")]->add(*itPUnit);
			}
			else
			{
				LError << "A unit is producable in a tile (producer) not existing -> '" << (*itPUnit)->get(0)->getParams()->get("producedIn") << "'";
				return false;
			}
		}
	}
	
	try
	{
        // Unit menu
        // unitMenuEntries.push_back(new MenuView("Move",ME_Move,NULL));

		pMBMenu = new MenuBox(pNE->getSpriteFactory(),pMap->getTheme(),pNE->getWindow()->getWindowSize());
		if ( pMBMenu == NULL )
		{
			LError << "Fail to allocate MenuBox";
			throw std::bad_alloc("MenuBox allocation failed");
		}

		pMBMenu->add("EndTurnAction",pMap->getTheme()->getUIItem("endTurnIcon")->getSprite(),"End turn");
		pMBMenu->add("QuitAction",NULL,"Quit");
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
			case GS_CONSTRUCTION:
				{
					// Some protections
					if ( !pC->getTileUnderCursor()->getParams()->exists("producerName") )
					{
						LWarning << "Tile '" << pC->getTileUnderCursor()->getInternalName() << "' selected for construction but not having a producer name";
						gState = GS_VISU;
						break;
					}

					if ( constructionBoxes.find(pC->getTileUnderCursor()->getParams()->get("producerName")) == constructionBoxes.end() )
					{
						LWarning << "Tile '" << pC->getTileUnderCursor()->getInternalName() <<  "' does not have a producerName known";
						gState = GS_VISU;
						break;
					}
					
					// We can draw it
					constructionBoxes[pC->getTileUnderCursor()->getParams()->get("producerName")]->draw(*pNE->getRenderer(),0,5000,pVT->getTime());
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
								if ( pC->getTileUnderCursor()->getParams()->exists("producerName") )
								{
									this->gState = GS_CONSTRUCTION;
								}
								else
								{
                                    // pMBMenu->setMenus(menuEntries);
									this->gState = GS_MENU;
								}
							}
							else if ( !pMap->getUnit(pC->getPosition())->state == US_ACTIVE )
							{
                                // pMBMenu->setMenus(menuEntries);
								this->gState = GS_MENU;
							}
							else
							{
                                // pMBMenu->setMenus(unitMenuEntries);
                                this->gState = GS_SELECT;
                            }
							
						}
					}
					break;
				case GS_CONSTRUCTION:
					{	
						if ( !pC->getTileUnderCursor()->getParams()->exists("producerName") )
						{
							LWarning << "Tile '" << pC->getTileUnderCursor()->getInternalName() << "' selected for construction but not having a producer name";
							gState = GS_VISU;
							break;
						}

						if ( constructionBoxes.find(pC->getTileUnderCursor()->getParams()->get("producerName")) == constructionBoxes.end() )
						{
							LWarning << "Tile '" << pC->getTileUnderCursor()->getInternalName() <<  "' does not have a producerName known";
							gState = GS_VISU;
							break;
						}
						
						// We can draw it
						constructionBoxes[pC->getTileUnderCursor()->getParams()->get("producerName")]->update(direction);
						if ( (buttons & NE::InputManager::INPUT_X) == NE::InputManager::INPUT_X )
						{
							pMap->setUnit(pC->getPosition(),constructionBoxes[pC->getTileUnderCursor()->getParams()->get("producerName")]->getUnitSelected(0)->getName(),0);
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
							std::string menuSelection = pMBMenu->getSelectedActionName();
							if ( menuSelection == "EndTurnAction" )
							{
								this->pMap->enableUnits();
								this->gState = GS_VISU;
							}
							else if ( menuSelection == "QuitAction" )
							{
								m_userQuit = true;
							}
							else
							{
								LWarning << "Not implemented action '" << menuSelection << "' in GS_MENU state";
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
							/*
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
							*/
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

