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

TileBar :: TileBar(SpriteManager& sm, const Window& win)
{
	unsigned int barHeight = static_cast<unsigned int>(64 * Scaler::getYScaleFactor());
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

	// Load all the animation needed by the TileBar ( all are loading in classical theme )
	tilesList.push_back(
		std::pair<TileView, TileType>(
			TileView(
				new AnimatedSprite(sm,"./data/gfx/tiles/classic/plain.png",32,32,NORMAL_SPEED,true),
				static_cast<int>(Scaler::getXScaleFactor() * TILE_BAR_XMARGIN)), 
			TT_Plain)
		);

	tilesList.push_back(
		std::pair<TileView, TileType>(
			TileView(
				new AnimatedSprite(sm,"./data/gfx/tiles/classic/tree.png",32,32,NORMAL_SPEED,true),
				static_cast<int>(Scaler::getXScaleFactor() * TILE_BAR_XMARGIN) * 3 + static_cast<int>(Scaler::getXScaleFactor() * 32)),
			TT_Tree)
		);
	
	tilesList.push_back(
		std::pair<TileView, TileType>(
			TileView(
				new AnimatedSprite(sm,"./data/gfx/tiles/classic/mountain1.png",32,32,NORMAL_SPEED,true),
				static_cast<int>(Scaler::getXScaleFactor() * TILE_BAR_XMARGIN) * 5 + static_cast<int>(Scaler::getXScaleFactor() * 32) * 2),
			TT_Mountain_1)
		);

	tilesList.push_back(
		std::pair<TileView, TileType>(
			TileView(
				new AnimatedSprite(sm,"./data/gfx/tiles/classic/r_city.png",32,40,NORMAL_SPEED,true),
				static_cast<int>(Scaler::getXScaleFactor() * TILE_BAR_XMARGIN) * 7 + static_cast<int>(Scaler::getXScaleFactor() * 32) * 3),
			TT_Red_City)
		);

	tilesList.push_back(
		std::pair<TileView, TileType>(
			TileView(
				new AnimatedSprite(sm,"./data/gfx/tiles/classic/r_factory.png",32,32,NORMAL_SPEED,true),
				static_cast<int>(Scaler::getXScaleFactor() * TILE_BAR_XMARGIN) * 9 + static_cast<int>(Scaler::getXScaleFactor() * 32) * 4),
			TT_Red_Factory)
		);

	tilesList.push_back(
		std::pair<TileView, TileType>(
			TileView(
				new AnimatedSprite(sm,"./data/gfx/tiles/classic/r_hq.png",32,62,NORMAL_SPEED,true),
				static_cast<int>(Scaler::getXScaleFactor() * TILE_BAR_XMARGIN) * 11 + static_cast<int>(Scaler::getXScaleFactor() * 32) * 5),
			TT_Red_HQ)
		);

	tilesList.push_back(
		std::pair<TileView, TileType>(
			TileView(
				new AnimatedSprite(sm,"./data/gfx/tiles/classic/beach_t_t.png",32,32,NORMAL_SPEED,true),
				static_cast<int>(Scaler::getXScaleFactor() * TILE_BAR_XMARGIN) * 13 + static_cast<int>(Scaler::getXScaleFactor() * 32) * 6),
			TT_Beach_T_T)
		);

	tilesList.push_back(
		std::pair<TileView, TileType>(
			TileView(
				new AnimatedSprite(sm,"./data/gfx/tiles/classic/reef.png",32,32,NORMAL_SPEED,true),
				static_cast<int>(Scaler::getXScaleFactor() * TILE_BAR_XMARGIN) * 15 + static_cast<int>(Scaler::getXScaleFactor() * 32) * 7),
			TT_Reef)
		);

	tilesList.push_back(
		std::pair<TileView, TileType>(
			TileView(
				new AnimatedSprite(sm,"./data/gfx/tiles/classic/bridge_h.png",32,32,NORMAL_SPEED,true),
				static_cast<int>(Scaler::getXScaleFactor() * TILE_BAR_XMARGIN) * 17 + static_cast<int>(Scaler::getXScaleFactor() * 32) * 8),
			TT_Bridge_H)
		);

	tilesList.push_back(
		std::pair<TileView, TileType>(
			TileView(
				new AnimatedSprite(sm,"./data/gfx/tiles/classic/road_h.png",32,32,NORMAL_SPEED,true),
				static_cast<int>(Scaler::getXScaleFactor() * TILE_BAR_XMARGIN) * 19 + static_cast<int>(Scaler::getXScaleFactor() * 32) * 9),
			TT_Road_H)
		);

	// Load the cursor
	pBarCursor = new Sprite(sm,"./data/gfx/tilebar_cursor.png",true);

	// Final settings
	valid = true;
	counterMovementAnim = 0;
	windowSize = UVec2(win.getWidth(),win.getHeight());
	limit =  (tilesList[0].first.pASprite->getWidth() + (static_cast<int>(Scaler::getXScaleFactor() * TILE_BAR_XMARGIN)*2)) * tilesList.size();
	positionY = win.getHeight();
	state = TBS_Closed;
	current = 5;

	LDebug << "TileBar created";
}

TileBar :: ~TileBar(void)
{
	for ( std::vector<std::pair<TileView, TileType> >::const_iterator itASprites = tilesList.begin() ; itASprites != tilesList.end() ; ++itASprites )
	{
		delete itASprites->first.pASprite;
	}

	delete pBarCursor;

	SDL_FreeSurface(pBarSprite->getSurface());
	delete pBarSprite;

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
	
		current--;
		if ( current < 0 )
		{
			current = tilesList.size() - 1;
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
	
		current++;
		if ( current >= static_cast<int>(tilesList.size()) )
		{
			current = 0;
		}
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
		unsigned int selectedTileXPosition = windowSize.x / 2 - tilesList[current].first.pASprite->getWidth() / 2;
		unsigned int xOffset = 0;
		if ( current-1 >= 0 )
		{
			xOffset = (windowSize.x / 2 - tilesList[current].first.pASprite->getWidth() / 2) - tilesList[current-1].first.positionX;
		}
		else
		{
			xOffset = (windowSize.x / 2 - tilesList[current].first.pASprite->getWidth() / 2) - tilesList[tilesList.size()-1].first.positionX;
		}
		IVec2 cursorPosition(windowSize.x / 2 - pBarCursor->getWidth()/2, positionY + static_cast<unsigned int>(Scaler::getYScaleFactor() * TILE_BAR_HEIGHT) / 2 - pBarCursor->getHeight()/2);

		// Display the Tiles
		for ( unsigned int i = 0 ; i < TILE_NB_DRAWN + 1 ; i++ )	// TILE_NB_DRAWN + 1 because we are drawing one extra tile, to avoid some nasty effect when sliding
		{
			// Calculation of the offset for sprite with higher size than normal Tile (e.g.: Mountains)
			unsigned int yOffset = tilesList[i%tilesList.size()].first.pASprite->getHeight() - (static_cast<unsigned int>(Scaler::getYScaleFactor() * TILE_DEFAULT_HEIGHT));

			IVec2 tilePosition(tilesList[i%tilesList.size()].first.positionX, positionY + static_cast<int>(Scaler::getYScaleFactor() * TILE_BAR_YMARGIN *2));
			// Offset, because we are drawing one before the first visible
			tilePosition.x -= static_cast<int>(Scaler::getXScaleFactor() * TILE_BAR_XMARGIN *2) + tilesList[i%tilesList.size()].first.pASprite->getWidth();

			if ( state == TBS_Opened )
			{
				// The currently selected sprite will be centered in the cursor
				if ( i == current )
				{
					tilePosition.x = windowSize.x / 2 - tilesList[i%tilesList.size()].first.pASprite->getWidth() / 2;
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
				isOk &= r.drawTile(*tilesList[i%tilesList.size()].first.pASprite, tilePosition, time);
			}
		}

		// Draw the cursor
		r.drawTile(*pBarCursor,cursorPosition);
	}

	return isOk;
}

void TileBar :: update(const unsigned int time)
{
	LDebug << "TileBar :: update()";

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
				for ( std::vector<std::pair<TileView, TileType> >::iterator itASprites = tilesList.begin() ; itASprites != tilesList.end() ; ++itASprites )
				{
					itASprites->first.positionX-=8;
				}
				counterMovementAnim-=8;
			}
			else
			{
				for ( std::vector<std::pair<TileView, TileType> >::iterator itASprites = tilesList.begin() ; itASprites != tilesList.end() ; ++itASprites )
				{
					itASprites->first.positionX-=counterMovementAnim;
				}
				counterMovementAnim-=counterMovementAnim;
			}

			if ( counterMovementAnim <= 0 )
			{
				// Final check to move the sprites from back to front
				for ( std::vector<std::pair<TileView, TileType> >::iterator itASprites = tilesList.begin() ; itASprites != tilesList.end() ; ++itASprites )
				{
					if ( itASprites->first.positionX < 0 )
					{
						itASprites->first.positionX = (limit - ((static_cast<int>(Scaler::getXScaleFactor() * TILE_BAR_XMARGIN) + itASprites->first.pASprite->getWidth())));
					}
				}
				state = TBS_Opened;
			}
			break;
		case TBS_MoveLeft:
			if ( counterMovementAnim > 8 )
			{
				for ( std::vector<std::pair<TileView, TileType> >::iterator itASprites = tilesList.begin() ; itASprites != tilesList.end() ; ++itASprites )
				{
					itASprites->first.positionX+=8;
				}

				counterMovementAnim-=8;
			}
			else
			{
				for ( std::vector<std::pair<TileView, TileType> >::iterator itASprites = tilesList.begin() ; itASprites != tilesList.end() ; ++itASprites )
				{
					itASprites->first.positionX+=counterMovementAnim;
				}
				counterMovementAnim-=counterMovementAnim;
			}

			if ( counterMovementAnim <= 0 )
			{
				for ( std::vector<std::pair<TileView, TileType> >::iterator itASprites = tilesList.begin() ; itASprites != tilesList.end() ; ++itASprites )
				{
					if ( itASprites->first.positionX > limit )
					{
						itASprites->first.positionX -= limit;
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