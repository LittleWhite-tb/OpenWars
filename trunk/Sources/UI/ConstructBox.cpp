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

#include "../Engine/Font.h"
#include "../Engine/Sprite.h"
#include "../Engine/AnimatedSprite.h"

#include "../Types/Vec2.h"
#include "../Types/Colour.h"

#include "../Utils/Scaler.h"
#include "../Utils/Logger.h"

#include <vector>
#include <string>
#include <sstream>

ConstructBox :: ConstructBox(SpriteManager& sm, FontManager& fm, const std::string& backgroundFileName, const std::string& cursorFileName, const std::string& upArrowFileName,
							 const std::string& downArrowFileName, const std::string& fontFileName, const std::vector<ConstructUnitView>& unitsList, const USize2& windowSize)
							 :pBackgroundUI(new Sprite(sm,backgroundFileName,true)),pCursor(new Sprite(sm,cursorFileName,true)),
							 pUpArrow(new Sprite(sm,upArrowFileName,true)), pDownArrow(new Sprite(sm,downArrowFileName,true)),windowSize(windowSize),unitsList(unitsList),actualPosition(0),offsetCursorPosition(0)
{
	SDL_Color white = {255,255,255};
	SDL_Color grey = {64,64,64};

	pFont = new Font(fm,fontFileName,22,white);
	pFontGrey = new Font(fm,fontFileName,22,grey);

	LDebug << "Construc Box created";
}

ConstructBox :: ~ConstructBox(void)
{
	delete pFontGrey;
	delete pFont;

	delete pUpArrow;
	delete pDownArrow;
	delete pCursor;
	delete pBackgroundUI;

	LDebug << "Construc Box delete";
}

bool ConstructBox :: draw(const NE::Renderer& r, const unsigned int moneyAvailable)
{
	bool errorFlag = true;

	IVec2 uiPosition(20, windowSize.y - (pBackgroundUI->getHeight() + static_cast<unsigned int>(20 * Scaler::getYScaleFactor())));
	IVec2 upArrowPosition(uiPosition.x - (pUpArrow->getWidth() / 2) + pBackgroundUI->getWidth() / 2 , uiPosition.y);
	IVec2 downArrowPosition(upArrowPosition.x, upArrowPosition.y + pBackgroundUI->getHeight() - pDownArrow->getHeight());
	IVec2 cursorPosition(0, uiPosition.y + (actualPosition-offsetCursorPosition) * pCursor->getHeight() + static_cast<unsigned int>(5 * Scaler::getYScaleFactor()));

	errorFlag &= pBackgroundUI->draw(r,uiPosition);
	if ( unitsList.size() > 6 )
	{
		if ( offsetCursorPosition > 0 )
		{
			errorFlag &= pUpArrow->draw(r,upArrowPosition);
		}
		
		if ( offsetCursorPosition < 4 )
		{
			errorFlag &= pDownArrow->draw(r,downArrowPosition);
		}
	}

	errorFlag &= pCursor->draw(r,cursorPosition);

	/**
		Offset cursor make the list behaving in the way that until the cursor is not down, we are displaying the first of the list
	*/
	for ( unsigned int i = offsetCursorPosition ; i < unitsList.size() && i < offsetCursorPosition+7 ; i++ )
	{
		IVec2 unitPosition(static_cast<unsigned int>(40 * Scaler::getXScaleFactor()), uiPosition.y + static_cast<unsigned int>(6 * Scaler::getXScaleFactor()) + (i-offsetCursorPosition) * (unitsList[i].pUnitSprite->getHeight()+1));
		
		// Convertion of the price into a string
		std::string priceString = "0";
		{
			std::ostringstream oss;

			oss << unitsList[i].unitPrice;

			priceString = oss.str();
		}
		
		IVec2 unitPricePosition(pBackgroundUI->getWidth() - (pFont->getSize(priceString).x), unitPosition.y + (static_cast<unsigned int>(6 * Scaler::getXScaleFactor())));
		IVec2 unitNamePosition(pBackgroundUI->getWidth() - (static_cast<unsigned int>(60 * Scaler::getXScaleFactor()) + pFont->getSize(unitsList[i].unitName).x) , unitPricePosition.y);

		if ( unitsList[i].unitPrice <= moneyAvailable )
		{
			errorFlag &= unitsList[i].pUnitSprite->draw(r,unitPosition);
			errorFlag &= pFont->draw(r,unitsList[i].unitName,unitNamePosition);
			errorFlag &= pFont->draw(r,priceString,unitPricePosition);
		}
		else
		{
			errorFlag &= unitsList[i].pUnitSprite->draw(r,unitPosition,Colour(128,128,128,255));
			errorFlag &= pFontGrey->draw(r,unitsList[i].unitName,unitNamePosition);
			errorFlag &= pFontGrey->draw(r,priceString,unitPricePosition);
		}
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
