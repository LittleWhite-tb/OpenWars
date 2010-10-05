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

#include <string>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "Engine/Window.h"
#include "Engine/Renderer.h"
#include "Engine/ResourcesManager/SpriteManager.h"
#include "Engine/ResourcesManager/FontManager.h"
#include "Engine/AnimatedSprite.h"
#include "Engine/Sprite.h"

#include "Game/MapEditor.h"
#include "Game/Camera.h"
#include "Game/EditingCursor.h"

#include "Types/Vec2.h"

#include "Utils/Logger.h"
#include "Utils/Scaler.h"

#include "UI/TileBarTiles.h"
#include "UI/TileBarUnits.h"
#include "UI/TileViewer.h"

#include "globals.h"

#ifdef _DEBUG
	// Some specials globals to check if all memory cleaning is properly done
	unsigned int nbASAllocation = 0;
	unsigned int nbASDestruction = 0;
	unsigned int nbSAllocation = 0;
	unsigned int nbSDestruction = 0;
	unsigned int nbFAllocation = 0;
	unsigned int nbFDestruction = 0;
#endif

int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;

	Uint32 startTime = 0;

	// Starting SDL
	if ( SDL_Init(SDL_INIT_VIDEO) == -1 )
	{
		LError << "Error while initializing SDL -> SDL_INIT_VIDEO";
		return 1;
	}

	{
		Window win;
		Renderer* r = RendererFactory(&win, RAPI_SDL);
		int flags = IMG_INIT_PNG;
		int initIMG = IMG_Init(flags);

		// Starting SDL_image 
		if ( (initIMG & flags) != flags )
		{
			LError << "Fail to init the SDL_image with PNG support (" << IMG_GetError() << ")";
		}
		else
		{
			if ( TTF_Init() != 0 )
			{
				LError << "Fail to init the SDL_tff " << TTF_GetError() << ")";
			}
			else
			{
				std::vector<ResolutionInfo> riList;

				win.getResolutionsAvailable(false,riList);
				win.setCaption("OpenAWars Editor","");
				win.showCursor(false);

				// Window test
				if ( win.openWindow(640,480,32,false,false) )
				{
					Scaler::setScaleFactor(win);

					SpriteManager sm;
					FontManager fm;
					MapEditor m(sm,UVec2(15,10));
					EditingCursor ec(sm,"./data/gfx/cursor.png","./data/gfx/cursor_wrong.png",&m,UVec2(5,5));
					Camera cam;
					Keyboard kb;

					bool isUnit = false;

					if ( m.isValidMap() )
					{
						// Prepare the data to put in the TileBar for building
						std::vector<TileView*> buildingTiles;
						{
							buildingTiles.push_back(new TileView(m.getAssociatedSprite(TT_Plain),TT_Plain,0));
							buildingTiles.push_back(new TileView(m.getAssociatedSprite(TT_Tree),TT_Tree,1));
							buildingTiles.push_back(new TileView(m.getAssociatedSprite(TT_Mountain_1),TT_Mountain_1,2));
							buildingTiles.push_back(new TileView(m.getAssociatedSprite(TT_Sea),TT_Sea,3));
							buildingTiles.push_back(new TileView(m.getAssociatedSprite(TT_River_H),TT_River_H,4));
							buildingTiles.push_back(new TileView(m.getAssociatedSprite(TT_Beach_T),TT_Beach_T,5));
							buildingTiles.push_back(new TileView(m.getAssociatedSprite(TT_Reef),TT_Reef,6));
							buildingTiles.push_back(new TileView(m.getAssociatedSprite(TT_Road_H),TT_Road_H,7));
							buildingTiles.push_back(new TileView(m.getAssociatedSprite(TT_Bridge_H),TT_Bridge_H,8));
							buildingTiles.push_back(new TileView(m.getAssociatedSprite(TT_Red_HQ),TT_Red_HQ,9));
							buildingTiles.push_back(new TileView(m.getAssociatedSprite(TT_Blue_HQ),TT_Blue_HQ,9));
							buildingTiles.push_back(new TileView(m.getAssociatedSprite(TT_Green_HQ),TT_Green_HQ,9));
							buildingTiles.push_back(new TileView(m.getAssociatedSprite(TT_Yellow_HQ),TT_Yellow_HQ,9));
							buildingTiles.push_back(new TileView(m.getAssociatedSprite(TT_Red_HQ),TT_Red_HQ,9));
							buildingTiles.push_back(new TileView(m.getAssociatedSprite(TT_Red_City),TT_Red_City,10));
							buildingTiles.push_back(new TileView(m.getAssociatedSprite(TT_Blue_City),TT_Blue_City,10));
							buildingTiles.push_back(new TileView(m.getAssociatedSprite(TT_Green_City),TT_Green_City,10));
							buildingTiles.push_back(new TileView(m.getAssociatedSprite(TT_Yellow_City),TT_Yellow_City,10));
							buildingTiles.push_back(new TileView(m.getAssociatedSprite(TT_Neutral_City),TT_Neutral_City,10));
							buildingTiles.push_back(new TileView(m.getAssociatedSprite(TT_Red_Factory),TT_Red_Factory,11));
							buildingTiles.push_back(new TileView(m.getAssociatedSprite(TT_Blue_Factory),TT_Blue_Factory,11));
							buildingTiles.push_back(new TileView(m.getAssociatedSprite(TT_Green_Factory),TT_Green_Factory,11));
							buildingTiles.push_back(new TileView(m.getAssociatedSprite(TT_Yellow_Factory),TT_Yellow_Factory,11));
							buildingTiles.push_back(new TileView(m.getAssociatedSprite(TT_Neutral_Factory),TT_Neutral_Factory,11));
							buildingTiles.push_back(new TileView(m.getAssociatedSprite(TT_Red_Port),TT_Red_Port,12));
							buildingTiles.push_back(new TileView(m.getAssociatedSprite(TT_Blue_Port),TT_Blue_Port,12));
							buildingTiles.push_back(new TileView(m.getAssociatedSprite(TT_Green_Port),TT_Green_Port,12));
							buildingTiles.push_back(new TileView(m.getAssociatedSprite(TT_Yellow_Port),TT_Yellow_Port,12));
							buildingTiles.push_back(new TileView(m.getAssociatedSprite(TT_Neutral_Port),TT_Neutral_Port,12));
							buildingTiles.push_back(new TileView(m.getAssociatedSprite(TT_Red_Airport),TT_Red_Airport,13));
							buildingTiles.push_back(new TileView(m.getAssociatedSprite(TT_Blue_Airport),TT_Blue_Airport,13));
							buildingTiles.push_back(new TileView(m.getAssociatedSprite(TT_Green_Airport),TT_Green_Airport,13));
							buildingTiles.push_back(new TileView(m.getAssociatedSprite(TT_Yellow_Airport),TT_Yellow_Airport,13));
							buildingTiles.push_back(new TileView(m.getAssociatedSprite(TT_Neutral_Airport),TT_Neutral_Airport,13));
						}

						// Prepare the list of units in the TileBar for Units
						std::vector<UnitView*> unitTiles;
						{
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_R_INFANTRY),UT_R_INFANTRY,0));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_G_INFANTRY),UT_G_INFANTRY,0));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_B_INFANTRY),UT_B_INFANTRY,0));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_Y_INFANTRY),UT_Y_INFANTRY,0));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_R_BAZOOKA),UT_R_BAZOOKA,1));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_G_BAZOOKA),UT_G_BAZOOKA,1));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_B_BAZOOKA),UT_B_BAZOOKA,1));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_Y_BAZOOKA),UT_Y_BAZOOKA,1));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_R_RECON),UT_R_RECON,2));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_G_RECON),UT_G_RECON,2));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_B_RECON),UT_B_RECON,2));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_Y_RECON),UT_Y_RECON,2));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_R_APC),UT_R_APC,3));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_G_APC),UT_G_APC,3));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_B_APC),UT_B_APC,3));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_Y_APC),UT_Y_APC,3));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_R_TANK),UT_R_TANK,4));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_G_TANK),UT_G_TANK,4));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_B_TANK),UT_B_TANK,4));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_Y_TANK),UT_Y_TANK,4));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_R_TANKM),UT_R_TANKM,5));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_G_TANKM),UT_G_TANKM,5));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_B_TANKM),UT_B_TANKM,5));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_Y_TANKM),UT_Y_TANKM,5));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_R_NEOTANK),UT_R_NEOTANK,6));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_G_NEOTANK),UT_G_NEOTANK,6));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_B_NEOTANK),UT_B_NEOTANK,6));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_Y_NEOTANK),UT_Y_NEOTANK,6));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_R_ARTILLERY),UT_R_ARTILLERY,7));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_G_ARTILLERY),UT_G_ARTILLERY,7));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_B_ARTILLERY),UT_B_ARTILLERY,7));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_Y_ARTILLERY),UT_Y_ARTILLERY,7));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_R_ROCKETS),UT_R_ROCKETS,8));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_G_ROCKETS),UT_G_ROCKETS,8));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_B_ROCKETS),UT_B_ROCKETS,8));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_Y_ROCKETS),UT_Y_ROCKETS,8));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_R_ANTIAIR),UT_R_ANTIAIR,9));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_G_ANTIAIR),UT_G_ANTIAIR,9));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_B_ANTIAIR),UT_B_ANTIAIR,9));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_Y_ANTIAIR),UT_Y_ANTIAIR,9));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_R_MISSILES),UT_R_MISSILES,10));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_G_MISSILES),UT_G_MISSILES,10));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_B_MISSILES),UT_B_MISSILES,10));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_Y_MISSILES),UT_Y_MISSILES,10));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_R_TCOPTER),UT_R_TCOPTER,11));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_G_TCOPTER),UT_G_TCOPTER,11));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_B_TCOPTER),UT_B_TCOPTER,11));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_Y_TCOPTER),UT_Y_TCOPTER,11));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_R_COPTER),UT_R_COPTER,12));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_G_COPTER),UT_G_COPTER,12));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_B_COPTER),UT_B_COPTER,12));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_Y_COPTER),UT_Y_COPTER,12));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_R_FIGHTER),UT_R_FIGHTER,13));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_G_FIGHTER),UT_G_FIGHTER,13));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_B_FIGHTER),UT_B_FIGHTER,13));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_Y_FIGHTER),UT_Y_FIGHTER,13));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_R_BOMBER),UT_R_BOMBER,14));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_G_BOMBER),UT_G_BOMBER,14));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_B_BOMBER),UT_B_BOMBER,14));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_Y_BOMBER),UT_Y_BOMBER,14));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_R_LANDER),UT_R_LANDER,15));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_G_LANDER),UT_G_LANDER,15));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_B_LANDER),UT_B_LANDER,15));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_Y_LANDER),UT_Y_LANDER,15));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_R_CRUISER),UT_R_CRUISER,16));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_G_CRUISER),UT_G_CRUISER,16));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_B_CRUISER),UT_B_CRUISER,16));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_Y_CRUISER),UT_Y_CRUISER,16));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_R_BOMBERSHIP),UT_R_BOMBERSHIP,17));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_G_BOMBERSHIP),UT_G_BOMBERSHIP,17));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_B_BOMBERSHIP),UT_B_BOMBERSHIP,17));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_Y_BOMBERSHIP),UT_Y_BOMBERSHIP,17));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_R_SUB),UT_R_SUB,18));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_G_SUB),UT_G_SUB,18));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_B_SUB),UT_B_SUB,18));
							unitTiles.push_back(new UnitView(m.getAssociatedSprite(UT_Y_SUB),UT_Y_SUB,18));
						}

						TileBarTiles buildingTB(sm,win,buildingTiles);
						TileBarUnits unitTB(sm,win,unitTiles);
						TileViewer tileInformationViewer(sm,fm,win,"./data/gfx/UI_Background.png","./data/fonts/times.ttf");
					
						tileInformationViewer.setTile(m.getAssociatedSprite(buildingTB.getSelected()), 
													  parseName(buildingTB.getSelected()));

						while ( kb.isEscapePressed() == 0 )
						{
							r->clearScreen();

							m.draw(*r,cam,0);
							ec.draw(*r,cam,0);
							if ( buildingTB.isClosed() && unitTB.isClosed() )
							{
								tileInformationViewer.draw(*r);
							}

							unitTB.draw(*r,0);
							buildingTB.draw(*r,0);
							
							
							SDL_UpdateRect(win.getWindowSurface(),0,0,0,0);

							cam.update(ec,m);

							if ( (kb.isKey('a') || kb.isKey('A')) && unitTB.isClosed() )
							{
								buildingTB.open();
							}

							if ( (kb.isKey('q') || kb.isKey('Q')) && buildingTB.isClosed() )
							{
								unitTB.open();
							}


							if ( (kb.isKey('c') || kb.isKey('C')) && buildingTB.isOpened()  )
							{
								buildingTB.close();
								isUnit = false;
								tileInformationViewer.setTitle("Element");
								tileInformationViewer.setTile(m.getAssociatedSprite(buildingTB.getSelected()), 
														  parseName(buildingTB.getSelected()));
							}
							
							if ( (kb.isKey('c') || kb.isKey('C')) && unitTB.isOpened()  )
							{
								unitTB.close();
								isUnit = true;
								tileInformationViewer.setTitle("Unit");
								tileInformationViewer.setTile(m.getAssociatedSprite(unitTB.getSelected()), 
															parseName(unitTB.getSelected()));
							}


							if ( buildingTB.isOpened() )
							{
								if ( kb.isKey(SDLK_LEFT) )
								{
									buildingTB.moveLeft();
								}

								if ( kb.isKey(SDLK_RIGHT) )
								{
									buildingTB.moveRight();
								}

								if ( kb.isKey(SDLK_UP) )
								{
									buildingTB.moveUp();
								}

								if ( kb.isKey(SDLK_DOWN) )
								{
									buildingTB.moveDown();
								}
							}
							else if ( unitTB.isOpened() )
							{
								if ( kb.isKey(SDLK_LEFT) )
								{
									unitTB.moveLeft();
								}

								if ( kb.isKey(SDLK_RIGHT) )
								{
									unitTB.moveRight();
								}

								if ( kb.isKey(SDLK_UP) )
								{
									unitTB.moveUp();
								}

								if ( kb.isKey(SDLK_DOWN) )
								{
									unitTB.moveDown();
								}
							}
							else 
							{
								ec.move(kb.getDirectionPressed());
								
								if ( isUnit )
								{
									if ( kb.isKey(SDLK_SPACE) )
									{
										m.setTile(ec.getPosition(),unitTB.getSelected());
									}

									ec.setIsWrong(!m.testTile(ec.getPosition(),unitTB.getSelected()));
								}
								else
								{
									if ( kb.isKey(SDLK_SPACE) )
									{
										m.setTile(ec.getPosition(),buildingTB.getSelected());
									}
									ec.setIsWrong(!m.testTile(ec.getPosition(),buildingTB.getSelected()));
								}

								// Check if we have to move the TileViewer
								if ( ec.getPosition().y >= 6 )
								{
									if ( ec.getPosition().x <= 2  )
									{
										tileInformationViewer.putOnRight();
									}
									else if ( ec.getPosition().x >= 13 )
									{
										tileInformationViewer.putOnLeft();
									}
								}
							}

							kb.update();
							buildingTB.update(0);
							unitTB.update(0);
							SDL_Delay(15);
						}
					}

					m.save("map_test.txt");
				}
			}

			// Stopping SDL_ttf
			TTF_Quit();
			// Bye bye SDL_image
			IMG_Quit();
		}

		delete r;
	}

	// Bye bye SDL
	SDL_Quit();

#ifdef _DEBUG
	// Final check
	LDebug << "Number of Sprite Alloc/Destruction: " << nbSAllocation << " / " << nbSDestruction;
	LDebug << "Number of Animated Sprite Alloc/Destruction: " << nbASAllocation << " / " << nbASDestruction;
	LDebug << "Number of Font Alloc/Destruction: " << nbFAllocation << " / " << nbFDestruction;
#endif

	Logger::deleteLogger();

	return 0;
}