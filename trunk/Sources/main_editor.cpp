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

#include "Engine/Window.h"
#include "Engine/Renderer.h"
#include "Engine/ResourcesManager/SpriteManager.h"
#include "Engine/AnimatedSprite.h"
#include "Engine/Sprite.h"

#include "Game/MapEditor.h"
#include "Game/Camera.h"
#include "Game/Cursor.h"

#include "Types/Vec2.h"

#include "Utils/Logger.h"
#include "Utils/Scaler.h"

#include "UI/TileBar.h"

#include "globals.h"

#ifdef _DEBUG
	// Some specials globals to check if all memory cleaning is properly done
	unsigned int nbASAllocation = 0;
	unsigned int nbASDestruction = 0;
	unsigned int nbSAllocation = 0;
	unsigned int nbSDestruction = 0;

	unsigned int nbTAllocation = 0;
	unsigned int nbTDestruction = 0;
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
			std::vector<ResolutionInfo> riList;

			win.getResolutionsAvailable(false,riList);
			win.setCaption("OpenAWars Editor","");
			win.showCursor(false);

			// Window test
			if ( win.openWindow(640,480,32,false,false) )
			{
				Scaler::setScaleFactor(win);

				SpriteManager sm;
				MapEditor m(sm,UVec2(15,10));
				Cursor c(sm,"./data/gfx/cursor_alpha.png",&m,UVec2(5,5));
				Camera cam;
				Keyboard kb;

				if ( m.isValidMap() )
				{
					// Prepare the data to put in the TileBar for building
					std::vector<TileView> buildingTiles;
					{
						buildingTiles.push_back(TileView(m.getAssociatedSprite(TT_Plain),TT_Plain,0));
						buildingTiles.push_back(TileView(m.getAssociatedSprite(TT_Tree),TT_Tree,1));
						buildingTiles.push_back(TileView(m.getAssociatedSprite(TT_Mountain_1),TT_Mountain_1,2));
						buildingTiles.push_back(TileView(m.getAssociatedSprite(TT_See),TT_See,3));
						buildingTiles.push_back(TileView(m.getAssociatedSprite(TT_River_H),TT_River_H,4));
						buildingTiles.push_back(TileView(m.getAssociatedSprite(TT_Beach_T),TT_Beach_T,5));
						buildingTiles.push_back(TileView(m.getAssociatedSprite(TT_Reef),TT_Reef,6));
						buildingTiles.push_back(TileView(m.getAssociatedSprite(TT_Road_H),TT_Road_H,7));
						buildingTiles.push_back(TileView(m.getAssociatedSprite(TT_Bridge_H),TT_Bridge_H,8));
						buildingTiles.push_back(TileView(m.getAssociatedSprite(TT_Red_HQ),TT_Red_HQ,9));
						buildingTiles.push_back(TileView(m.getAssociatedSprite(TT_Blue_HQ),TT_Blue_HQ,9));
						buildingTiles.push_back(TileView(m.getAssociatedSprite(TT_Green_HQ),TT_Green_HQ,9));
						buildingTiles.push_back(TileView(m.getAssociatedSprite(TT_Yellow_HQ),TT_Yellow_HQ,9));
						buildingTiles.push_back(TileView(m.getAssociatedSprite(TT_Red_HQ),TT_Red_HQ,9));
						buildingTiles.push_back(TileView(m.getAssociatedSprite(TT_Red_City),TT_Red_City,10));
						buildingTiles.push_back(TileView(m.getAssociatedSprite(TT_Blue_City),TT_Blue_City,10));
						buildingTiles.push_back(TileView(m.getAssociatedSprite(TT_Green_City),TT_Green_City,10));
						buildingTiles.push_back(TileView(m.getAssociatedSprite(TT_Yellow_City),TT_Yellow_City,10));
						buildingTiles.push_back(TileView(m.getAssociatedSprite(TT_Neutral_City),TT_Neutral_City,10));
						buildingTiles.push_back(TileView(m.getAssociatedSprite(TT_Red_Factory),TT_Red_Factory,11));
						buildingTiles.push_back(TileView(m.getAssociatedSprite(TT_Blue_Factory),TT_Blue_Factory,11));
						buildingTiles.push_back(TileView(m.getAssociatedSprite(TT_Green_Factory),TT_Green_Factory,11));
						buildingTiles.push_back(TileView(m.getAssociatedSprite(TT_Yellow_Factory),TT_Yellow_Factory,11));
						buildingTiles.push_back(TileView(m.getAssociatedSprite(TT_Neutral_Factory),TT_Neutral_Factory,11));
						buildingTiles.push_back(TileView(m.getAssociatedSprite(TT_Red_Port),TT_Red_Port,12));
						buildingTiles.push_back(TileView(m.getAssociatedSprite(TT_Blue_Port),TT_Blue_Port,12));
						buildingTiles.push_back(TileView(m.getAssociatedSprite(TT_Green_Port),TT_Green_Port,12));
						buildingTiles.push_back(TileView(m.getAssociatedSprite(TT_Yellow_Port),TT_Yellow_Port,12));
						buildingTiles.push_back(TileView(m.getAssociatedSprite(TT_Neutral_Port),TT_Neutral_Port,12));
						buildingTiles.push_back(TileView(m.getAssociatedSprite(TT_Red_Airport),TT_Red_Airport,13));
						buildingTiles.push_back(TileView(m.getAssociatedSprite(TT_Blue_Airport),TT_Blue_Airport,13));
						buildingTiles.push_back(TileView(m.getAssociatedSprite(TT_Green_Airport),TT_Green_Airport,13));
						buildingTiles.push_back(TileView(m.getAssociatedSprite(TT_Yellow_Airport),TT_Yellow_Airport,13));
						buildingTiles.push_back(TileView(m.getAssociatedSprite(TT_Neutral_Airport),TT_Neutral_Airport,13));
					}

					TileBar buildingTB(sm,win,buildingTiles);
				
					while ( kb.isEscapePressed() == 0 )
					{
						r->clearScreen();

						m.draw(*r,cam,0);
						c.draw(*r,cam,0);

						buildingTB.draw(*r,0);
						
						
						SDL_UpdateRect(win.getWindowSurface(),0,0,0,0);

						cam.update(c,m);

						if ( kb.isKey('a') || kb.isKey('A')  )
						{
							buildingTB.open();
						}
						if ( kb.isKey('c') || kb.isKey('C')  )
						{
							buildingTB.close();
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
						else 
						{
							c.move(kb.getDirectionPressed());
							if ( kb.isKey(SDLK_SPACE) )
							{
								m.setTile(c.getPosition(),buildingTB.getSelected());
							}
						}

						kb.update();
						buildingTB.update(0);
						SDL_Delay(15);
					}
				}

				m.save("map_test.txt");
			}

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
	LDebug << "Number of Tile Alloc/Destruction: " << nbTAllocation << " / " << nbTDestruction;
#endif

	Logger::deleteLogger();

	return 0;
}