#ifdef EDITOR

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

#include "EditorEngine.h"

#include "../NEngine/Engine.h"
#include "../NEngine/Window.h"
#include "../NEngine/Renderer.h"

#include "../Engine/VTime.h"

#include "../UI/TileBarUnits.h"
#include "../UI/TileBarTiles.h"
#include "../UI/TileViewer.h"

#include "MapEditor.h"
#include "EditingCursor.h"
#include "Camera.h"

#include "../Engine/Controls/Keyboard.h"

#include "../Types/Colour.h"

#include "../Utils/Logger.h"

#include "../Utils/Exceptions/ConstructionFailedException.h"

EditorEngine :: EditorEngine(NE::Engine* const pNE)
:Engine(pNE),pBuildingTB(NULL),pUnitTB(NULL),pTileViewer(NULL),pMap(NULL),pEC(NULL),pCam(NULL)
{
	LDebug << "EditorEngine constructed";
}

EditorEngine :: ~EditorEngine(void)
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
	pEC = new EditingCursor(*pSM,"./data/gfx/cursor.png","./data/gfx/cursor_wrong.png",pMap,UVec2(5,5));
	pCam = new Camera();

	// Prepare the data to put in the TileBar for building
	std::vector<TileView*> buildingTiles;
	{
		buildingTiles.push_back(new TileView(pMap->getAssociatedSprite(TT_Plain),TT_Plain,0));
		buildingTiles.push_back(new TileView(pMap->getAssociatedSprite(TT_Tree),TT_Tree,1));
		buildingTiles.push_back(new TileView(pMap->getAssociatedSprite(TT_Mountain_1),TT_Mountain_1,2));
		buildingTiles.push_back(new TileView(pMap->getAssociatedSprite(TT_Sea),TT_Sea,3));
		buildingTiles.push_back(new TileView(pMap->getAssociatedSprite(TT_River_H),TT_River_H,4));
		buildingTiles.push_back(new TileView(pMap->getAssociatedSprite(TT_Beach_T),TT_Beach_T,5));
		buildingTiles.push_back(new TileView(pMap->getAssociatedSprite(TT_Reef),TT_Reef,6));
		buildingTiles.push_back(new TileView(pMap->getAssociatedSprite(TT_Road_H),TT_Road_H,7));
		buildingTiles.push_back(new TileView(pMap->getAssociatedSprite(TT_Bridge_H),TT_Bridge_H,8));
		buildingTiles.push_back(new TileView(pMap->getAssociatedSprite(TT_Red_HQ),TT_Red_HQ,9));
		buildingTiles.push_back(new TileView(pMap->getAssociatedSprite(TT_Blue_HQ),TT_Blue_HQ,9));
		buildingTiles.push_back(new TileView(pMap->getAssociatedSprite(TT_Green_HQ),TT_Green_HQ,9));
		buildingTiles.push_back(new TileView(pMap->getAssociatedSprite(TT_Yellow_HQ),TT_Yellow_HQ,9));
		buildingTiles.push_back(new TileView(pMap->getAssociatedSprite(TT_Red_HQ),TT_Red_HQ,9));
		buildingTiles.push_back(new TileView(pMap->getAssociatedSprite(TT_Red_City),TT_Red_City,10));
		buildingTiles.push_back(new TileView(pMap->getAssociatedSprite(TT_Blue_City),TT_Blue_City,10));
		buildingTiles.push_back(new TileView(pMap->getAssociatedSprite(TT_Green_City),TT_Green_City,10));
		buildingTiles.push_back(new TileView(pMap->getAssociatedSprite(TT_Yellow_City),TT_Yellow_City,10));
		buildingTiles.push_back(new TileView(pMap->getAssociatedSprite(TT_Neutral_City),TT_Neutral_City,10));
		buildingTiles.push_back(new TileView(pMap->getAssociatedSprite(TT_Red_Factory),TT_Red_Factory,11));
		buildingTiles.push_back(new TileView(pMap->getAssociatedSprite(TT_Blue_Factory),TT_Blue_Factory,11));
		buildingTiles.push_back(new TileView(pMap->getAssociatedSprite(TT_Green_Factory),TT_Green_Factory,11));
		buildingTiles.push_back(new TileView(pMap->getAssociatedSprite(TT_Yellow_Factory),TT_Yellow_Factory,11));
		buildingTiles.push_back(new TileView(pMap->getAssociatedSprite(TT_Neutral_Factory),TT_Neutral_Factory,11));
		buildingTiles.push_back(new TileView(pMap->getAssociatedSprite(TT_Red_Port),TT_Red_Port,12));
		buildingTiles.push_back(new TileView(pMap->getAssociatedSprite(TT_Blue_Port),TT_Blue_Port,12));
		buildingTiles.push_back(new TileView(pMap->getAssociatedSprite(TT_Green_Port),TT_Green_Port,12));
		buildingTiles.push_back(new TileView(pMap->getAssociatedSprite(TT_Yellow_Port),TT_Yellow_Port,12));
		buildingTiles.push_back(new TileView(pMap->getAssociatedSprite(TT_Neutral_Port),TT_Neutral_Port,12));
		buildingTiles.push_back(new TileView(pMap->getAssociatedSprite(TT_Red_Airport),TT_Red_Airport,13));
		buildingTiles.push_back(new TileView(pMap->getAssociatedSprite(TT_Blue_Airport),TT_Blue_Airport,13));
		buildingTiles.push_back(new TileView(pMap->getAssociatedSprite(TT_Green_Airport),TT_Green_Airport,13));
		buildingTiles.push_back(new TileView(pMap->getAssociatedSprite(TT_Yellow_Airport),TT_Yellow_Airport,13));
		buildingTiles.push_back(new TileView(pMap->getAssociatedSprite(TT_Neutral_Airport),TT_Neutral_Airport,13));
	}

	// Prepare the list of units in the TileBar for Units
	std::vector<UnitView*> unitTiles;
	{
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_R_INFANTRY),UT_R_INFANTRY,0));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_G_INFANTRY),UT_G_INFANTRY,0));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_B_INFANTRY),UT_B_INFANTRY,0));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_Y_INFANTRY),UT_Y_INFANTRY,0));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_R_BAZOOKA),UT_R_BAZOOKA,1));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_G_BAZOOKA),UT_G_BAZOOKA,1));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_B_BAZOOKA),UT_B_BAZOOKA,1));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_Y_BAZOOKA),UT_Y_BAZOOKA,1));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_R_RECON),UT_R_RECON,2));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_G_RECON),UT_G_RECON,2));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_B_RECON),UT_B_RECON,2));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_Y_RECON),UT_Y_RECON,2));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_R_APC),UT_R_APC,3));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_G_APC),UT_G_APC,3));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_B_APC),UT_B_APC,3));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_Y_APC),UT_Y_APC,3));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_R_TANK),UT_R_TANK,4));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_G_TANK),UT_G_TANK,4));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_B_TANK),UT_B_TANK,4));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_Y_TANK),UT_Y_TANK,4));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_R_TANKM),UT_R_TANKM,5));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_G_TANKM),UT_G_TANKM,5));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_B_TANKM),UT_B_TANKM,5));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_Y_TANKM),UT_Y_TANKM,5));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_R_NEOTANK),UT_R_NEOTANK,6));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_G_NEOTANK),UT_G_NEOTANK,6));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_B_NEOTANK),UT_B_NEOTANK,6));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_Y_NEOTANK),UT_Y_NEOTANK,6));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_R_ARTILLERY),UT_R_ARTILLERY,7));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_G_ARTILLERY),UT_G_ARTILLERY,7));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_B_ARTILLERY),UT_B_ARTILLERY,7));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_Y_ARTILLERY),UT_Y_ARTILLERY,7));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_R_ROCKETS),UT_R_ROCKETS,8));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_G_ROCKETS),UT_G_ROCKETS,8));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_B_ROCKETS),UT_B_ROCKETS,8));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_Y_ROCKETS),UT_Y_ROCKETS,8));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_R_ANTIAIR),UT_R_ANTIAIR,9));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_G_ANTIAIR),UT_G_ANTIAIR,9));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_B_ANTIAIR),UT_B_ANTIAIR,9));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_Y_ANTIAIR),UT_Y_ANTIAIR,9));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_R_MISSILES),UT_R_MISSILES,10));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_G_MISSILES),UT_G_MISSILES,10));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_B_MISSILES),UT_B_MISSILES,10));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_Y_MISSILES),UT_Y_MISSILES,10));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_R_TCOPTER),UT_R_TCOPTER,11));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_G_TCOPTER),UT_G_TCOPTER,11));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_B_TCOPTER),UT_B_TCOPTER,11));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_Y_TCOPTER),UT_Y_TCOPTER,11));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_R_COPTER),UT_R_COPTER,12));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_G_COPTER),UT_G_COPTER,12));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_B_COPTER),UT_B_COPTER,12));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_Y_COPTER),UT_Y_COPTER,12));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_R_FIGHTER),UT_R_FIGHTER,13));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_G_FIGHTER),UT_G_FIGHTER,13));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_B_FIGHTER),UT_B_FIGHTER,13));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_Y_FIGHTER),UT_Y_FIGHTER,13));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_R_BOMBER),UT_R_BOMBER,14));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_G_BOMBER),UT_G_BOMBER,14));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_B_BOMBER),UT_B_BOMBER,14));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_Y_BOMBER),UT_Y_BOMBER,14));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_R_LANDER),UT_R_LANDER,15));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_G_LANDER),UT_G_LANDER,15));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_B_LANDER),UT_B_LANDER,15));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_Y_LANDER),UT_Y_LANDER,15));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_R_CRUISER),UT_R_CRUISER,16));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_G_CRUISER),UT_G_CRUISER,16));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_B_CRUISER),UT_B_CRUISER,16));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_Y_CRUISER),UT_Y_CRUISER,16));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_R_BOMBERSHIP),UT_R_BOMBERSHIP,17));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_G_BOMBERSHIP),UT_G_BOMBERSHIP,17));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_B_BOMBERSHIP),UT_B_BOMBERSHIP,17));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_Y_BOMBERSHIP),UT_Y_BOMBERSHIP,17));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_R_SUB),UT_R_SUB,18));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_G_SUB),UT_G_SUB,18));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_B_SUB),UT_B_SUB,18));
		unitTiles.push_back(new UnitView(pMap->getAssociatedSprite(UT_Y_SUB),UT_Y_SUB,18));
	}

	try
	{
		pUnitTB = new TileBarUnits(*pSM,unitTiles,pNE->getWindow()->getWindowSize());
		pBuildingTB = new TileBarTiles(*pSM,buildingTiles,pNE->getWindow()->getWindowSize());
		pTileViewer = new TileViewer(*pSM,*pFM,"./data/gfx/UI_Background.png","./data/fonts/times.ttf",pNE->getWindow()->getWindowSize());
	}
	catch (ConstructionFailedException& cfe)
	{
		LError << cfe.what();
		return false;
	}
					
	pTileViewer->setTile(pMap->getAssociatedSprite(pBuildingTB->getSelected()), 
		pMap->getTile(pBuildingTB->getSelected()).name);

	return true;
}

bool EditorEngine :: init(void)
{
	bool error = true;

	error = Engine::init();

	LDebug << "EditorEngine init'd";

	return error;
}


bool EditorEngine :: load(const std::string& themeName, const UVec2& mapSize)
{
	pMap = new MapEditor(*pSM, themeName , mapSize);
	if ( !pMap->isValidMap() )
	{
		return false;
	}

	return this->load();
}

bool EditorEngine :: load(const std::string& mapName)
{
	pMap = new MapEditor(*pSM, mapName);
	if ( !pMap->isValidMap() )
	{
		return false;
	}

	return this->load();
}

bool EditorEngine :: run(void)
{
	bool isUnit = false;

	while ( pKB->isEscapePressed() == 0 && pNE->getWindow()->needWindowClosure() == false )
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
			pCam->update(*pEC,*pMap);
			pKB->update();

			if ( (pKB->isKey('w') || pKB->isKey('W')) )
			{
				pBuildingTB->open();
				if ( pUnitTB->isOpened() )
				{
					pUnitTB->close();
				}
			}

			if ( (pKB->isKey('q') || pKB->isKey('Q')) )
			{
				pUnitTB->open();
				if ( pBuildingTB->isOpened() )
				{
					pBuildingTB->close();
				}
			}

			if ( pKB->isKey(SDLK_SPACE) && pBuildingTB->isOpened()  )
			{
				pBuildingTB->close();
				isUnit = false;
				pTileViewer->setTitle("Element");
				pTileViewer->setTile(pMap->getAssociatedSprite(pBuildingTB->getSelected()), 
										  pMap->getTile(pBuildingTB->getSelected()).name);
			}
			
			if ( pKB->isKey(SDLK_SPACE) && pUnitTB->isOpened()  )
			{
				pUnitTB->close();
				isUnit = true;
				pTileViewer->setTitle("Unit");
				pTileViewer->setTile(pMap->getAssociatedSprite(pUnitTB->getSelected()), 
											pMap->getUnitTemplate(pUnitTB->getSelected()).name);
			}

			if ( pBuildingTB->isOpened() )
			{
				pBuildingTB->move(pKB->getDirectionPressed());
			}
			else if ( pUnitTB->isOpened() )
			{
				pUnitTB->move(pKB->getDirectionPressed());
			}
			else if ( pUnitTB->isClosed() && pBuildingTB->isClosed() )
			{
				pEC->move(pKB->getDirectionPressed());
				
				if ( isUnit )
				{
					if ( pKB->isKey(SDLK_SPACE) )
					{
						pMap->setTile(pEC->getPosition(),pUnitTB->getSelected());
					}

					pEC->setIsWrong(!pMap->Map::testTile(pEC->getPosition(),pUnitTB->getSelected()));
				}
				else
				{
					if ( pKB->isKey(SDLK_SPACE) )
					{
						pMap->setTile(pEC->getPosition(),pBuildingTB->getSelected());
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

bool EditorEngine :: setTile(const UVec2& position, const UnitType unitType)
{
    bool bError = true;
    
    // We place the unit
	bError &= dynamic_cast<Map*>(this)->setTile(position,unitType);

    return bError;
}

#endif
