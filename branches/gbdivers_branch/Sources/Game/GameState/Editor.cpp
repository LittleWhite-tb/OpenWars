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

#include "Editor.h"

#include "NEngine/NEngine.h"
#include "NEngine/Window.h"
#include "NEngine/Renderer.h"
#include "NEngine/InputManager.h"

#include "Game/GameState/GameObjects/Tile.h"
#include "Game/GameState/GameObjects/UnitTemplate.h"
#include "Game/GameState/GameObjects/Map/Map.h"
#include "Game/GameState/GameObjects/Map/MapLoader.h"
#include "Game/GameState/GameObjects/Map/MapFactory.h"
#include "Game/GameState/GameObjects/Map/MapSaver.h"
#include "Game/GameState/GameObjects/Map/MapDrawer.h"

#include "Engine/Theme.h"
#include "Engine/VTime.h"

#include "UI/TileBar.h"
#include "UI/TileViewer.h"

#include "Game/GameState/EditorObjects/EditingCursor.h"
#include "Game/GameState/GameObjects/Camera.h"

#include "Types/Colour.h"

#include "Utils/Logger.h"

#include "NEngine/Exceptions/ConstructionFailedException.h"
#include "NEngine/Exceptions/FileNotFoundException.h"

Editor :: Editor()
:GameState(),pMap(NULL),pCamera(NULL),pEC(NULL),pBuildingTB(NULL),pUnitTB(NULL),pTileViewer(NULL),isUnitSelected(false)
{
	LDebug << "EditorEngine constructed";
}

Editor :: ~Editor()
{
	delete pEC;
	delete pCamera;
	delete pMap;

	delete pTileViewer;
	delete pUnitTB;
	delete pBuildingTB;

	LDebug << "EditorEngine destructed";
}

bool Editor :: load(NE::NEngine* pNE)
{
	pCamera = new Camera();
	pEC = new EditingCursor(pMap,UVec2(5,5));

	if ( pCamera == NULL || pEC == NULL )
	{
		return false;
	}

	try
	{
		pUnitTB = new TileBar<const UnitTemplate*>(pNE->getSpriteFactory(),pMap->getTheme(),pNE->getWindow()->getWindowSize());
		pBuildingTB = new TileBar<const Tile*>(pNE->getSpriteFactory(),pMap->getTheme(),pNE->getWindow()->getWindowSize());
		pTileViewer = new TileViewer(pMap->getTheme(),pNE->getWindow()->getWindowSize());
	}
	catch (ConstructionFailedException& cfe)
	{
		LError << cfe.what();
		return false;
	}

	// Prepare the data to put in the TileBar for building
	{
		std::list<const Tile* > tilesList;
		pMap->getTheme()->getTilesList(&tilesList);

		for ( std::list < const Tile* >::const_iterator itPTile = tilesList.begin() ;
			  itPTile != tilesList.end() ; ++itPTile )
		{
			if ( (*itPTile)->getMenuEntry() != -1 )
			{
				pBuildingTB->add(*itPTile, (*itPTile)->getMenuEntry());
			}
		}
	}

	// Prepare the list of units in the TileBar for Units
	{
		std::list<const UnitTemplateFactionList* > unitsList;
		pMap->getTheme()->getUnitsList(&unitsList);
	
		unsigned int unitCounter = 0;
		for ( std::list < const UnitTemplateFactionList* >::const_iterator itPUnit = unitsList.begin() ;
			  itPUnit != unitsList.end() ; ++itPUnit )
		{
			for ( unsigned int i = 0 ; i < (*itPUnit)->getNumberFaction() ; i++ )
			{
				pUnitTB->add((*itPUnit)->get(i),unitCounter);
			}

			unitCounter++;
		}
	}	
					
	pTileViewer->setTile(pBuildingTB->getSelected());

	return true;
}

bool Editor :: loadMap(const Library<Theme>* const pThemes, const std::string& mapName)
{
	delete pMap;

	pMap = MapLoader::loadMapFromFile(pThemes,mapName);
	if ( pMap == NULL )
	{
		return false;
	}
	
	return true;
}

bool Editor :: loadMap(const Theme* const pTheme, const USize2& mapSize)
{
	delete pMap;

	pMap = MapFactory::createEmptyMap(pTheme,mapSize);
	if ( pMap == NULL )
	{
		return false;
	}

	return true;
}

bool Editor :: draw(NE::Renderer* pRenderer, unsigned int time)
{
	bool bResult = true;
	// Drawing part
	bResult &= MapDrawer::drawTerrain(*pRenderer,pMap,*pCamera,time);
	bResult &= MapDrawer::drawUnits(*pRenderer,pMap,*pCamera,time);
	bResult &= pEC->draw(*pRenderer,*pCamera,time);

	if ( pBuildingTB->isClosed() && pUnitTB->isClosed() )
	{
		bResult &= pTileViewer->draw(*pRenderer,time);
	}

	bResult &= pUnitTB->draw(*pRenderer,0);
	bResult &= pBuildingTB->draw(*pRenderer,0);

	return bResult;
}

bool Editor :: update(NE::InputManager::ArrowsDirection direction, NE::InputManager::Buttons buttons, unsigned int time)
{
	pCamera->update(*pEC,*pMap);

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
		isUnitSelected = false;
		pTileViewer->setTile(pBuildingTB->getSelected());
	}
	
	if ( (buttons & NE::InputManager::INPUT_X) == NE::InputManager::INPUT_X && pUnitTB->isOpened()  )
	{
		pUnitTB->close();
		isUnitSelected = true;
		pTileViewer->setTile(pUnitTB->getSelected());
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
		
		if ( isUnitSelected )
		{
			if ( (buttons & NE::InputManager::INPUT_X) == NE::InputManager::INPUT_X )
			{
				pMap->setUnit(pEC->getPosition(),pUnitTB->getSelected()->getInternalName(),0);
			}

			pEC->setIsWrong(!pMap->Map::testUnit(pEC->getPosition(),pUnitTB->getSelected()));
		}
		else
		{
			if ( (buttons & NE::InputManager::INPUT_X) == NE::InputManager::INPUT_X )
			{
				pMap->setTile(pEC->getPosition(),pBuildingTB->getSelected()->getInternalName());
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

	pBuildingTB->update(time);
	pUnitTB->update(time);

	return true;
}

void Editor :: saveMap(const std::string& fileName)const
{
	MapSaver::saveMapToFile(fileName,*pMap);
}
