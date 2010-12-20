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

#include "MenuBox.h"

#include "../NEngine/NE.h"
#include "../NEngine/NEngine.h"
#include "../NEngine/NETypes.h"

#include "../Engine/ResourcesManager/SpriteManager.h"
#include "../Engine/ResourcesManager/FontManager.h"
#include "../Engine/Renderer.h"
#include "../Engine/Sprite.h"
#include "../Engine/AnimatedSprite.h"
#include "../Engine/Font.h"

#include "../Utils/Scaler.h"
#include "../Utils/Logger.h"

#include "../Utils/Exceptions/ConstructionFailedException.h"

#include "../globals.h"

MenuBox :: MenuBox(SpriteManager& sm, FontManager& fm, const Window& win, const std::string& cursorFileName, const std::string& fontFileName, std::vector<MenuView*> entries)
:pCursor(new AnimatedSprite(sm,cursorFileName,32,32,200,true)),actualPosition(0),entries(entries)
{
	// Creating the background
	SDL_Surface* pSurface = NULL;
	pSurface = SDL_CreateRGBSurface(SDL_HWSURFACE,150,10 + static_cast<unsigned int>(TILE_DEFAULT_HEIGHT * Scaler::getYScaleFactor()),32,
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
												0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000
#else
												0xff000000,  0x00ff0000, 0x0000ff00, 0x000000ff
#endif
												);
	if ( pSurface == NULL )
	{
		LError << "SDL_CreateRGBSurfaceFrom() failed (" << SDL_GetError() << ")";
		throw ConstructionFailedException("MenuBox");
		return;
	}
	
	unsigned int* pPixel = reinterpret_cast<unsigned int*>(pSurface->pixels);
	for ( int i = 0 ; i < pSurface->w * pSurface->h ; i++ )
	{
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
		*pPixel = 0xC0C0C0C0;
#else
		*pPixel = 0xC0C0C0C0;
#endif
		pPixel++;
	}

	pBackground = new Sprite(pSurface);

	SDL_Colour red={255,0,0,255};

	windowXPosition = NE::get()->getWindowSize(win).width;
	
	pFont = new Font(fm,fontFileName,18,red);
}

MenuBox :: ~MenuBox()
{
/*
	for (std::vector<MenuView>::iterator itEntry = pEntries->begin() ; itEntry != pEntries->end() ; ++itEntry)
	{
		delete itEntry->pASprite;
	}
*/
    delete pFont;
	delete pCursor;

	SDL_FreeSurface(pBackground->getSurface());
	delete pBackground;
}

bool MenuBox :: draw(const Renderer& r, const UVec2& cursorPosition, const unsigned int time)
{
	static const unsigned int margin = static_cast<unsigned int>(10 * Scaler::getXScaleFactor());
	static bool onRight = true;
	bool bError = true;

	IVec2 position;
	position.y = static_cast<unsigned int>(50 * Scaler::getYScaleFactor());

	// Calculate the position dependant on the cursor
	if ( cursorPosition.x >= MAP_MIN_WIDTH-4 )
	{
		onRight = false;
	}
	else if ( cursorPosition.x <= 3 )
	{
		onRight = true;
	}

	if (onRight == true)
	{
		position.x = windowXPosition - (pBackground->getWidth() + margin);	
	}
	else
	{
		position.x = margin;
	}

	IVec2 itemPosition(position.x + static_cast<unsigned int>(20 * Scaler::getXScaleFactor()) , position.y + static_cast<unsigned int>(5 * Scaler::getYScaleFactor()));

	for ( unsigned int i = 0 ; i < entries.size() ; i++ )
	{
        itemPosition.y = itemPosition.y -5;
        bError &= r.drawTile(*pBackground,itemPosition);
        itemPosition.y = itemPosition.y +5;
		if ( i == actualPosition )
		{
			IVec2 cursorPosition(position.x - static_cast<unsigned int>(15 * Scaler::getXScaleFactor()), itemPosition.y);
			bError &= r.drawTile(*pCursor, cursorPosition, time);
		}
		if ( entries[i]->pASprite != NULL )
		{
			bError &= r.drawTile(*(entries[i]->pASprite),itemPosition,time);
		}
		{
			IVec2 textPosition(position.x + static_cast<unsigned int>((TILE_DEFAULT_WIDTH + 24) * Scaler::getXScaleFactor()), itemPosition.y + static_cast<unsigned int>(TILE_DEFAULT_HEIGHT * Scaler::getYScaleFactor() / 2));
			IVec2 textSize = pFont->getSize(entries[i]->name);
			textPosition.y -= textSize.y/2;
			pFont->draw(r,entries[i]->name, textPosition);
		}
		itemPosition.y += 10 + static_cast<unsigned int>(TILE_DEFAULT_HEIGHT * Scaler::getYScaleFactor());
	}

	return bError;
}

void MenuBox ::update(const ArrowsDirection kd)
{
	switch (kd)
	{
		case AD_DOWN:
			if ( actualPosition < entries.size()-1 )
			{
				actualPosition++;
			}
			break;
		case AD_UP:
			if ( actualPosition > 0 )
			{
				actualPosition--;
			}
			break;
		default:
			break;
	}
}
