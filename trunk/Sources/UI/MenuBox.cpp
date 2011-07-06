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

#include "MenuBox.h"

#include "../NEngine/SpriteLoader.h"
#include "../NEngine/SpriteFactory.h"
#include "../NEngine/Sprite.h"
#include "../NEngine/Renderer.h"
#include "../NEngine/InputManager.h"

#include "../Engine/AnimatedSprite.h"
#include "../Engine/Font.h"

#include "../Utils/Logger.h"

#include "../NEngine/Exceptions/ConstructionFailedException.h"

#include "../globals.h"

MenuBox :: MenuBox(NE::SpriteLoader* const pSL, NE::SpriteFactory* const pSF, const std::string& cursorFileName, const std::string& fontFileName, std::vector<MenuView*> entries, const USize2& windowSize)
:pCursor(new AnimatedSprite(pSL->loadSpriteFromFile(cursorFileName),USize2(32,32),200)),actualPosition(0),entries(entries)
{
	pBackground = pSF->createSpriteFromColour(Colour(0xC0C0C0C0), USize2(150,10 + TILE_DEFAULT_HEIGHT));
    if ( pBackground == NULL )
    {
        throw ConstructionFailedException("MenuBox");
		return;
    }

	windowXPosition = windowSize.width;
	
	pFont = new Font(pSL->loadSpriteFromFile(fontFileName),USize2(16,16),' ');
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
}

bool MenuBox :: draw(const NE::Renderer& r, const UVec2& cursorPosition, const unsigned int time)
{
	static const unsigned int margin = 10;
	static bool onRight = true;
	bool bError = true;

	IVec2 position;
	position.y = 50;

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
		position.x = windowXPosition - (pBackground->getSize().width + margin);	
	}
	else
	{
		position.x = margin;
	}

	IVec2 itemPosition(position.x + 20 , position.y + 15 );

	for ( unsigned int i = 0 ; i < entries.size() ; i++ )
	{
        itemPosition.y = itemPosition.y -5;
        bError &= r.drawSurface(itemPosition,*pBackground);
        itemPosition.y = itemPosition.y +5;
		if ( i == actualPosition )
		{
			IVec2 cursorPosition(position.x - 15, itemPosition.y);
			bError &= pCursor->draw(r,cursorPosition,time);
		}
		if ( entries[i]->pASprite != NULL )
		{
			bError &= entries[i]->pASprite->draw(r,itemPosition,time);
		}
		{
			IVec2 textPosition(position.x + TILE_DEFAULT_WIDTH + 24, itemPosition.y + TILE_DEFAULT_HEIGHT / 2);
			USize2 textSize = pFont->getStringSize(entries[i]->name);
			textPosition.y -= textSize.height/2;
			pFont->draw(r,entries[i]->name, textPosition);
		}
		itemPosition.y += 10 + TILE_DEFAULT_HEIGHT;
	}

	return bError;
}

void MenuBox ::update(const NE::InputManager::ArrowsDirection kd)
{
	switch (kd)
	{
		case NE::InputManager::AD_DOWN:
			if ( actualPosition < entries.size()-1 )
			{
				actualPosition++;
			}
			break;
		case NE::InputManager::AD_UP:
			if ( actualPosition > 0 )
			{
				actualPosition--;
			}
			break;
		default:
			break;
	}
}
