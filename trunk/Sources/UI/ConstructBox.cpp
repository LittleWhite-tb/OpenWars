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

#include "ConstructBox.h"

#include "../Engine/ResourcesManager/SpriteManager.h"
#include "../Engine/ResourcesManager/FontManager.h"
#include "../Engine/Renderer.h"
#include "../Engine/Window.h"

#include "../Engine/Font.h"
#include "../Engine/Sprite.h"
#include "../Engine/AnimatedSprite.h"

#include "../Types/Vec2.h"

#include "../Utils/Scaler.h"
#include "../Utils/Logger.h"

#include <vector>
#include <string>
#include <sstream>

ConstructBox :: ConstructBox(SpriteManager& sm, FontManager& fm, const Window& win, const std::string& backgroundFileName, const std::string& cursorFileName, const std::string& upArrowFileName,
							 const std::string& downArrowFileName, const std::string& fontFileName, const std::vector<ConstructUnitView>& unitsList)
							 :pBackgroundUI(new Sprite(sm,backgroundFileName,true)),pCursor(new Sprite(sm,cursorFileName,true)),
		pUpArrow(new Sprite(sm,upArrowFileName,true)), pDownArrow(new Sprite(sm,downArrowFileName,true)),windowSize(win.getWidth(),win.getHeight()),unitsList(unitsList),actualPosition(0),offsetCursorPosition(0)
{
	SDL_Color white = {255,255,255};

	pFont = new Font(fm,fontFileName,24,white);

	LDebug << "Construc Box created";
}

ConstructBox :: ~ConstructBox(void)
{
	delete pFont;

	delete pUpArrow;
	delete pDownArrow;
	delete pCursor;
	delete pBackgroundUI;

	LDebug << "Construc Box delete";
}

bool ConstructBox :: draw(const Renderer& r)
{
	bool errorFlag = true;

	IVec2 uiPosition(20, windowSize.y - (pBackgroundUI->getHeight() + static_cast<unsigned int>(20 * Scaler::getYScaleFactor())));
	IVec2 upArrowPosition(uiPosition.x - (pUpArrow->getWidth() / 2) + pBackgroundUI->getWidth() / 2 , uiPosition.y);
	IVec2 downArrowPosition(upArrowPosition.x, upArrowPosition.y + pBackgroundUI->getHeight() - pDownArrow->getHeight());
	IVec2 cursorPosition(0, uiPosition.y + (actualPosition-offsetCursorPosition) * pCursor->getHeight() + static_cast<unsigned int>(5 * Scaler::getYScaleFactor()));

	errorFlag &= r.drawTile(*pBackgroundUI,uiPosition);
	if ( unitsList.size() > 6 )
	{
		if ( offsetCursorPosition > 0 )
		{
			errorFlag &= r.drawTile(*pUpArrow,upArrowPosition);
		}
		
		if ( offsetCursorPosition < 4 )
		{
			errorFlag &= r.drawTile(*pDownArrow,downArrowPosition);
		}
	}
	errorFlag &= r.drawTile(*pCursor,cursorPosition);

	/**
		Offset cursor make the list behaving in the way that until the cursor is not down, we are displaying the first of the list
	*/
	for ( unsigned int i = offsetCursorPosition ; i < unitsList.size() && i < offsetCursorPosition+7 ; i++ )
	{
		IVec2 unitPosition(static_cast<unsigned int>(40 * Scaler::getXScaleFactor()), uiPosition.y + static_cast<unsigned int>(7 * Scaler::getXScaleFactor()) + (i-offsetCursorPosition) * unitsList[i].pUnitSprite->getHeight());
		
		// Convertion of the price into a string
		std::string priceString = "0";
		{
			std::ostringstream oss;

			oss << unitsList[i].unitPrice;

			priceString = oss.str();
		}
		
		IVec2 unitPricePosition(pBackgroundUI->getWidth() - (pFont->getSize(priceString).x), unitPosition.y);
		IVec2 unitNamePosition(unitPricePosition.x - (static_cast<unsigned int>(20 * Scaler::getXScaleFactor()) + pFont->getSize(unitsList[i].unitName).x) , unitPosition.y);

		errorFlag &= r.drawTile(*unitsList[i].pUnitSprite,unitPosition);
		errorFlag &= pFont->draw(r,unitsList[i].unitName,unitNamePosition);
		errorFlag &= pFont->draw(r,priceString,unitPricePosition);
	}

	return errorFlag;
}

void ConstructBox :: update(const ArrowsDirection kd)
{
	switch (kd)
	{
		case AD_UP:
			if ( actualPosition > 0 )
			{
				actualPosition--;
				// Check to know if we have to move the list up
				if ( offsetCursorPosition > 0 && actualPosition < unitsList.size() - 6 )
				{
					offsetCursorPosition--;
				}
			}
			break;
		case AD_DOWN:
			if ( actualPosition < unitsList.size()-1 )
			{
				actualPosition++;
				// Check to know if we have to move the list down
				if ( actualPosition > 5 && actualPosition < unitsList.size() - 1 && offsetCursorPosition < 4 )
				{
					offsetCursorPosition++;
				}
			}
			break;
	}
}

UnitType ConstructBox :: getUnitSelected(void)const
{
	return unitsList[actualPosition].unitType;
}