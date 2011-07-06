#ifdef EDITOR

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

#include "EditorEngine.h"

#include "NEngine/NEngine.h"
#include "NEngine/Window.h"
#include "NEngine/Renderer.h"
#include "NEngine/InputManager.h"

#include "Engine/Theme.h"
#include "Engine/VTime.h"

#include "UI/TileBarUnits.h"
#include "UI/TileBarTiles.h"
#include "UI/TileViewer.h"

#include "MapEditor.h"
#include "EditingCursor.h"
#include "Camera.h"

#include "../Types/Colour.h"

#include "../Utils/Logger.h"

#include "../NEngine/Exceptions/ConstructionFailedException.h"
#include "../NEngine/Exceptions/FileNotFoundException.h"

EditorEngine :: EditorEngine(NE::NEngine* const pNE)
:Engine(pNE),pBuildingTB(NULL),pUnitTB(NULL),pTileViewer(NULL),pMap(NULL),pEC(NULL),pCam(NULL)
{
	LDebug << "EditorEngine constructed";
}

EditorEngine :: ~EditorEngine()
{
	delete pCam;
	delete pEC;
	delete pMap;
	delete pTileViewer;
	delete pUnitTB;
	delete pBuildingTB;

	LDebug << "EditorEngine destructed";
}

bool EditorEngine :: load(void)
{
	pEC = new EditingCursor(pNE->getSpriteLoader(),"./data/gfx/cursor.png","./data/gfx/cursor_wrong.png",pMap,UVec2(5,5));
	pCam = new Camera();

	// Prepare the data to put in the TileBar for building
	std::vector<TileView*> buildingTiles;
	{
		std::list<const Tile* > tilesList;
		pMap->getTheme()->getTilesList(&tilesList);

		for ( std::list < const Tile* >::const_iterator itPTile = tilesList.begin() ;
			  itPTile != tilesList.end() ; ++itPTile )
		{
			if ( (*itPTile)->getMenuEntry() != -1 )
			{
				buildingTiles.push_back(new TileView(*itPTile, (*itPTile)->getMenuEntry()));
			}
		}
	}

	// Prepare the list of units in the TileBar for Units
	std::vector<UnitView*> unitTiles;
	{
		std::list<const UnitTemplateFactionList* > unitsList;
		pMap->getTheme()->getUnitsList(&unitsList);
	
		unsigned int unitCounter = 0;
		for ( std::list < const UnitTemplateFactionList* >::const_iterator itPUnit = unitsList.begin() ;
			  itPUnit != unitsList.end() ; ++itPUnit )
		{
			for ( unsigned int i = 0 ; i < (*itPUnit)->getNumberFaction() ; i++ )
			{
				unitTiles.push_back(new UnitView((*itPUnit)->get(i),unitCounter));
			}

			unitCounter++;
		}
	}

	try
	{
		pUnitTB = new TileBarUnits(pNE->getSpriteLoader(),pNE->getSpriteFactory(),unitTiles,pNE->getWindow()->getWindowSize());
		pBuildingTB = new TileBarTiles(pNE->getSpriteLoader(),pNE->getSpriteFactory(),buildingTiles,pNE->getWindow()->getWindowSize());
		pTileViewer = new TileViewer(pNE->getSpriteLoader(),"./data/gfx/UI_Background.png","./data/fonts/font.png",pNE->getWindow()->getWindowSize());
	}
	catch (ConstructionFailedException& cfe)
	{
		LError << cfe.what();
		return false;
	}
					
	pTileViewer->setTile(pBuildingTB->getSelected()->getSprite(), 
		pBuildingTB->getSelected()->getName());

	return true;
}

bool EditorEngine :: load(const UVec2& mapSize)
{
	pMap = new MapEditor(&themeLibrary,mapSize);
	if ( pMap == NULL )
	{
		LError << "Fail to allocate memory for MapEditor";
		return false;
	}

	if ( !pMap->isValidMap() )
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

bool EditorEngine :: load(const std::string& mapName)
{
	pMap = new MapEditor(&themeLibrary);
	if ( pMap == NULL )
	{
		LError << "Fail to allocate memory for MapEditor";
		return false;
	}

	pMap->load(mapName);
	if ( !pMap->isValidMap() )
	{
		return false;
	}

	return this->load();
}

bool EditorEngine :: run(void)
{
	bool isUnit = false;

	while ( pNE->getInputManager()->needEscape() == false && pNE->getWindow()->needWindowClosure() == false )
	{
		// Drawing part
		pNE->getRenderer()->clearScreen(Colour(0,0,0));

		pMap->draw(*pNE->getRenderer(),*pCam,pVT->getTime());
		pEC->draw(*pNE->getRenderer(),*pCam,pVT->getTime());

		if ( pBuildingTB->isClosed() && pUnitTB->isClosed() )
		{
			pTileViewer->draw(*pNE->getRenderer());
		}

		pUnitTB->draw(*pNE->getRenderer(),0);
		pBuildingTB->draw(*pNE->getRenderer(),0);

		pNE->getRenderer()->updateWindow();

		// Update part
		if ( pVT->canUpdate() )
		{
            NE::InputManager::ArrowsDirection direction = pNE->getInputManager()->getDirectionsPressed();
            NE::InputManager::Buttons buttons = pNE->getInputManager()->getButtonsPressed();
            
			pCam->update(*pEC,*pMap);
			pNE->getInputManager()->update();

			if ( (buttons & NE::InputManager::INPUT_A) == NE::InputManager::INPUT_A )
			{
				pBuildingTB->open();
				if ( pUnitTB->isOpened() )
				{
					pUnitTB->close();
				}
			}

			if ( (buttons & NE::InputManager::INPUT_B) == NE::InputManager::INPUT_B )
			{
				pUnitTB->open();
				if ( pBuildingTB->isOpened() )
				{
					pBuildingTB->close();
				}
			}

			if ( (buttons & NE::InputManager::INPUT_X) == NE::InputManager::INPUT_X && pBuildingTB->isOpened()  )
			{
				pBuildingTB->close();
				isUnit = false;
				pTileViewer->setTitle("Element");
				pTileViewer->setTile(pBuildingTB->getSelected()->getSprite(), 
										  pBuildingTB->getSelected()->getName());
			}
			
			if ( (buttons & NE::InputManager::INPUT_X) == NE::InputManager::INPUT_X && pUnitTB->isOpened()  )
			{
				pUnitTB->close();
				isUnit = true;
				pTileViewer->setTitle("Unit");
				pTileViewer->setTile(pUnitTB->getSelected()->getSprite(), 
										  pUnitTB->getSelected()->getName());
			}

			if ( pBuildingTB->isOpened() )
			{
				pBuildingTB->move(direction);
			}
			else if ( pUnitTB->isOpened() )
			{
				pUnitTB->move(direction);
			}
			else if ( pUnitTB->isClosed() && pBuildingTB->isClosed() )
			{
				pEC->move(direction);
				
				if ( isUnit )
				{
					if ( (buttons & NE::InputManager::INPUT_X) == NE::InputManager::INPUT_X )
					{
						pMap->setTile(pEC->getPosition(),pUnitTB->getSelected()->getName());
					}

					pEC->setIsWrong(!pMap->Map::testTile(pEC->getPosition(),pUnitTB->getSelected()));
				}
				else
				{
					if ( (buttons & NE::InputManager::INPUT_X) == NE::InputManager::INPUT_X )
					{
						pMap->setTile(pEC->getPosition(),pBuildingTB->getSelected()->getName());
					}
					pEC->setIsWrong(!pMap->testTile(pEC->getPosition(),pBuildingTB->getSelected()));
				}

				// Check if we have to move the TileViewer
				if ( pEC->getPosition().y >= 6 )
				{
					if ( pEC->getPosition().x <= 2  )
					{
						pTileViewer->putOnRight();
					}
					else if ( pEC->getPosition().x >= 13 )
					{
						pTileViewer->putOnLeft();
					}
				}
			}

			
			pBuildingTB->update(pVT->getTime());
			pUnitTB->update(pVT->getTime());
		}

		pVT->waitNextFrame();
	}

	return true;
}

void EditorEngine :: saveMap(const std::string& fileName)
{
	pMap->save(fileName);
}
/*
bool EditorEngine :: setTile(const UVec2& position, const UnitType unitType)
{
    bool bError = true;
    
    // We place the unit
	bError &= dynamic_cast<Map*>(this)->setTile(position,unitType);

    return bError;
}
*/
#endif
