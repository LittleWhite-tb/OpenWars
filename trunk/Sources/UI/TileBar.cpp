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

#include "TileBar.h"

#include <SDL/SDL.h>

#include <vector>
#include <utility>

#include "../Engine/ResourcesManager/SpriteManager.h"
#include "../Engine/Window.h"
#include "../Engine/Renderer.h"
#include "../Engine/Sprite.h"
#include "../Engine/AnimatedSprite.h"
#include "../Game/Tile.h"
#include "../Utils/Logger.h"
#include "../Utils/Scaler.h"

#include "../globals.h"

TileBar :: TileBar(SpriteManager& sm, const Window& win, std::vector<View*>& listTiles)
{
	unsigned int barHeight = static_cast<unsigned int>(64 * Scaler::getYScaleFactor());
	unsigned int maximumX = 0;
	SDL_Surface* pSurface = NULL;
	pSurface = SDL_CreateRGBSurface(SDL_HWSURFACE,win.getWidth(),barHeight,32,
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
												0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000
#else
												0xff000000,  0x00ff0000, 0x0000ff00, 0x000000ff
#endif
												);
	if ( pSurface == NULL )
	{
		LError << "SDL_CreateRGBSurfaceFrom() failed (" << SDL_GetError() << ")";
		valid = false;
		return;
	}
/*
	// Put half alpha for the bar
	if ( SDL_SetAlpha(pSurface,SDL_SRCALPHA,128) != 0 )
	{
		LWarning << "SDL_SetAlpha failed for putting half alpha on the bar";
	}
*/
	
	unsigned int* pPixel = reinterpret_cast<unsigned int*>(pSurface->pixels);
	for ( int i = 0 ; i < pSurface->w * pSurface->h ; i++ )
	{
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
		*pPixel = 0x80000000;
#else
		*pPixel = 0x00000080;
#endif
		pPixel++;
	}
	
	pBarSprite = new Sprite(pSurface);

	// Search the maximum positionX to know the size of the vector
	for ( std::vector<View*>::const_iterator itTile = listTiles.begin() ; itTile != listTiles.end() ; ++itTile )
	{
		if ( maximumX < (*itTile)->positionX )
			maximumX = (*itTile)->positionX;
	}
	assert(maximumX+1<=listTiles.size());
	// Resize the vectore to contain the good number of elements
	for ( unsigned int i = 0 ; i < maximumX+1 ; i++ )
	{
		viewList.push_back(std::vector<View*>());
	}

	// Load all the animation needed by the TileBar
	for ( std::vector<View*>::iterator itTile = listTiles.begin() ; itTile != listTiles.end() ; ++itTile )
	{
		int abstractPositionX = (*itTile)->positionX;
			
		(*itTile)->positionX = static_cast<int>(Scaler::getXScaleFactor() * TILE_BAR_XMARGIN) * (1 + (*itTile)->positionX * 2) + static_cast<int>(Scaler::getXScaleFactor() * 32 * (*itTile)->positionX);

		viewList[abstractPositionX].push_back(*itTile);
	}

	// Load the cursor
	pBarCursor = new Sprite(sm,"./data/gfx/tilebar_cursor.png",true);

	// Load the arrows
	pBarArrows = new AnimatedSprite(sm,"./data/gfx/tilebar_arrows.png",45,45,300,true);

	// Final settings
	valid = true;
	counterMovementAnim = 0;
	windowSize = UVec2(win.getWidth(),win.getHeight());
	limit =  (viewList[0][0]->getSprite()->getWidth() + (static_cast<int>(Scaler::getXScaleFactor() * TILE_BAR_XMARGIN)*2)) * viewList.size();
	positionY = win.getHeight();
	state = TBS_Closed;
	currentX = 5;
	currentY = 0;

	LDebug << "TileBar created";
}

TileBar :: ~TileBar(void)
{
	delete pBarArrows;
	delete pBarCursor;

	SDL_FreeSurface(pBarSprite->getSurface());
	delete pBarSprite;

	for ( std::vector<std::vector<View*> >::const_iterator itListView = viewList.begin() ; itListView != viewList.end() ; ++itListView )
	{
		for ( std::vector<View*>::const_iterator itPView = itListView->begin() ; itPView != itListView->end() ; ++itPView )
		{
			delete (*itPView);
		}
	}

	LDebug << "TileBar deleted";
}

void TileBar :: open(void)
{
	if ( state == TBS_Closed )
	{
		LDebug << "TileBar :: open()";

		state = TBS_Opening;
	}
}

void TileBar ::  moveLeft(void)
{
	if ( state == TBS_Opened )
	{
		LDebug << "TileBar :: moveLeft()";
		counterMovementAnim = static_cast<unsigned int>(Scaler::getXScaleFactor() * TILE_DEFAULT_WIDTH) + static_cast<unsigned int>(Scaler::getXScaleFactor() * TILE_BAR_XMARGIN * 2 );

		state = TBS_MoveLeft;
	
		currentX--;
		if ( currentX < 0 )
		{
			currentX = viewList.size() - 1;
		}
	}
}

void TileBar ::  moveRight(void)
{
	if ( state == TBS_Opened )
	{
		LDebug << "TileBar :: moveRight()";
		
		counterMovementAnim = static_cast<unsigned int>(Scaler::getXScaleFactor() * TILE_DEFAULT_WIDTH) + static_cast<unsigned int>(Scaler::getXScaleFactor() * TILE_BAR_XMARGIN * 2);

		state = TBS_MoveRight;
	
		currentX++;
		if ( currentX >= static_cast<int>(viewList.size()) )
		{
			currentX = 0;
		}
	}
}

void TileBar :: moveUp(void)
{
	if ( state == TBS_Opened )
	{
		LDebug << "TileBar :: moveUp()";

		currentY++;
	}
}

void TileBar :: moveDown(void)
{
	if ( state == TBS_Opened )
	{
		LDebug << "TileBar :: moveDown()";

		currentY--;
	}
}

void TileBar :: close(void)
{
	if ( state == TBS_Opened )
	{
		LDebug << "TileBar :: close()";

		state = TBS_Closing;
	}
}

bool TileBar :: draw(const Renderer& r, const unsigned int time)
{
	bool isOk = true;

	IVec2 barPosition( 0 , positionY);

	LDebug << "TileBar :: draw()";

	if ( state != TBS_Closed )
	{
		isOk &= r.drawTile(*pBarSprite,barPosition);
	}
	
	if ( state == TBS_Opened || state == TBS_MoveLeft || state == TBS_MoveRight )
	{
		unsigned int selectedTileXPosition = windowSize.x / 2 - viewList[currentX][0]->getSprite()->getWidth() / 2;
		unsigned int xOffset = 0;
		if ( currentX-1 >= 0 )
		{
			xOffset = (windowSize.x / 2 - viewList[currentX][0]->getSprite()->getWidth() / 2) - viewList[currentX-1][0]->positionX;
		}
		else
		{
			xOffset = (windowSize.x / 2 - viewList[currentX][0]->getSprite()->getWidth() / 2) - viewList[viewList.size()-1][0]->positionX;
		}
		IVec2 cursorPosition(windowSize.x / 2 - pBarCursor->getWidth()/2, positionY + static_cast<unsigned int>(Scaler::getYScaleFactor() * TILE_BAR_HEIGHT) / 2 - pBarCursor->getHeight()/2);

		// Display the Tiles
		for ( unsigned int i = 0 ; i < viewList.size() ; i++ )	// TILE_NB_DRAWN + 1 because we are drawing one extra tile, to avoid some nasty effect when sliding
		{
			// Calculation of the offset for sprite with higher size than normal Tile (e.g.: Mountains)
			unsigned int yOffset = viewList[i%viewList.size()][currentY%viewList[i%viewList.size()].size()]->getSprite()->getHeight() - (static_cast<unsigned int>(Scaler::getYScaleFactor() * TILE_DEFAULT_HEIGHT));

			IVec2 tilePosition(viewList[i%viewList.size()][0]->positionX, positionY + static_cast<int>(Scaler::getYScaleFactor() * TILE_BAR_YMARGIN *2));
			// Offset, because we are drawing one before the first visible
			tilePosition.x -= static_cast<int>(Scaler::getXScaleFactor() * TILE_BAR_XMARGIN *2) + viewList[i%viewList.size()][0]->getSprite()->getWidth();

			if ( state == TBS_Opened )
			{
				// The currently selected sprite will be centered in the cursor
				if ( i == currentX )
				{
					tilePosition.x = windowSize.x / 2 - viewList[i%viewList.size()][0]->getSprite()->getWidth() / 2;
				}

				// The following sprite after the selected one have to be offseted to continue the TileBar correctly
				if ( tilePosition.x > selectedTileXPosition )
				{
					tilePosition.x += xOffset;
				}
			}

			// Apply offset for the sprite with non standard size
			tilePosition.y -= yOffset;

			// Remove little bug that one sprite is visible on the bound left
			if ( state != TBS_Opened || tilePosition.x > 0 )
			{
				isOk &= r.drawTile(*viewList[i%viewList.size()][currentY%viewList[i%viewList.size()].size()]->getSprite(), tilePosition, time);
			}
		}

		// Draw the cursor
		r.drawTile(*pBarCursor,cursorPosition);
		// Draw the arrow if needed
		if ( viewList[currentX].size() > 1 && state == TBS_Opened )
		{
			r.drawTile(*pBarArrows,cursorPosition);
		}
	}

	return isOk;
}

void TileBar :: update(const unsigned int time)
{
#ifdef VERBOSE
	LDebug << "TileBar :: update()";
#endif

	switch (state)
	{
		case TBS_Closing:
			positionY+=16;
			if ( positionY >= windowSize.y )
			{
				state = TBS_Closed;
			}
			break;
		case TBS_Opening:
			positionY-=16;
			if ( positionY <= windowSize.y - static_cast<int>(Scaler::getYScaleFactor() * 64) )
			{
				state = TBS_Opened;
			}
			break;
		case TBS_MoveRight:
			if ( counterMovementAnim > 8 )
			{
				for ( std::vector<std::vector<View*> >::iterator itVectorASprites = viewList.begin() ; itVectorASprites != viewList.end() ; ++itVectorASprites )
				{
					for ( std::vector<View*>::iterator itASprites = itVectorASprites->begin() ; itASprites != itVectorASprites->end() ; ++itASprites )
					{
						(*itASprites)->positionX-=8;
					}
				}
				counterMovementAnim-=8;
			}
			else
			{
				for ( std::vector<std::vector<View*> >::iterator itVectorASprites = viewList.begin() ; itVectorASprites != viewList.end() ; ++itVectorASprites )
				{
					for ( std::vector<View*>::iterator itASprites = itVectorASprites->begin() ; itASprites != itVectorASprites->end() ; ++itASprites )
					{
						(*itASprites)->positionX-=counterMovementAnim;
					}
				}
				counterMovementAnim-=counterMovementAnim;
			}

			if ( counterMovementAnim <= 0 )
			{
				// Final check to move the sprites from back to front
				for ( std::vector<std::vector<View*> >::iterator itVectorASprites = viewList.begin() ; itVectorASprites != viewList.end() ; ++itVectorASprites )
				{
					for ( std::vector<View*>::iterator itASprites = itVectorASprites->begin() ; itASprites != itVectorASprites->end() ; ++itASprites )
					{
						if ( (*itASprites)->positionX < 0 )
						{
							(*itASprites)->positionX = (limit - ((static_cast<int>(Scaler::getXScaleFactor() * TILE_BAR_XMARGIN) + (*itASprites)->getSprite()->getWidth())));
						}
					}
				}
				state = TBS_Opened;
			}
			break;
		case TBS_MoveLeft:
			if ( counterMovementAnim > 8 )
			{
				for ( std::vector<std::vector<View*> >::iterator itVectorASprites = viewList.begin() ; itVectorASprites != viewList.end() ; ++itVectorASprites )
				{
					for ( std::vector<View*>::iterator itASprites = itVectorASprites->begin() ; itASprites != itVectorASprites->end() ; ++itASprites )
					{
						(*itASprites)->positionX+=8;
					}
				}

				counterMovementAnim-=8;
			}
			else
			{
				for ( std::vector<std::vector<View*> >::iterator itVectorASprites = viewList.begin() ; itVectorASprites != viewList.end() ; ++itVectorASprites )
				{
					for ( std::vector<View*>::iterator itASprites = itVectorASprites->begin() ; itASprites != itVectorASprites->end() ; ++itASprites )
					{
						(*itASprites)->positionX+=counterMovementAnim;
					}
				}
				counterMovementAnim-=counterMovementAnim;
			}

			if ( counterMovementAnim <= 0 )
			{
				for ( std::vector<std::vector<View*> >::iterator itVectorASprites = viewList.begin() ; itVectorASprites != viewList.end() ; ++itVectorASprites )
				{
					for ( std::vector<View*>::iterator itASprites = itVectorASprites->begin() ; itASprites != itVectorASprites->end() ; ++itASprites )
					{
						if ( (*itASprites)->positionX > limit )
						{
							(*itASprites)->positionX -= limit;
						}
					}
				}

				state = TBS_Opened;
			}
			break;
#ifdef _DEBUG
		default:
			break;
#endif
	}
}

#endif // EDITOR