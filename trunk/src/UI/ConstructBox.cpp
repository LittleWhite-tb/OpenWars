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

#include "ConstructBox.h"

#include "NEngine/Renderer.h"
#include "NEngine/InputManager.h"

#include "Engine/Theme.h"
#include "Engine/Font.h"
#include "Engine/AnimatedSprite.h"

#include "Game/GameState/GameObjects/UnitTemplateFactionList.h"

#include "NEngine/NEngine.h"
#include "NEngine/Types/Vec2.h"
#include "NEngine/Types/Colour.h"

#include <vector>
#include <string>
#include <sstream>

ConstructBox :: ConstructBox(const Theme* pTheme)
    :pBackgroundUI(pTheme->getUIItem("ConstructionBackground")->getSprite()),
     pCursor(pTheme->getUIItem("ConstructionCursor")->getSprite()),
     pUpArrow(pTheme->getUIItem("upArrow")->getSprite()),
     pDownArrow(pTheme->getUIItem("downArrow")->getSprite()),
     actualPosition(0),offsetCursorPosition(0)
{
    Colour white(255,255,255,255);
    Colour grey (64,64,64,255);

    pFont = pTheme->getFontObject("classic")->getFont();
    pFontGrey = pTheme->getFontObject("classic")->getFont();

    NEDebug << "Construct Box created\n";
}

ConstructBox :: ~ConstructBox(void)
{
    NEDebug << "Construct Box deleted\n";
}

void ConstructBox :: add(const UnitTemplateFactionList* pListUnitTemplate)
{
    unitsList.push_back(pListUnitTemplate);
}

bool ConstructBox :: draw(const NE::Renderer& r, const unsigned int faction, const unsigned int moneyAvailable, unsigned int time)
{
    bool errorFlag = true;
    USize2 backgroundSize = pBackgroundUI->getSize();

    if ( unitsList.size() > 0 && faction >= unitsList[0]->getNumberFaction() )
    {
        NEWarning << "Try to draw a faction not available\n";
        return true;
    }

    IVec2 uiPosition(20, 20);
    IVec2 upArrowPosition(uiPosition.x - (pUpArrow->getSize().width / 2) + backgroundSize.width / 2 , uiPosition.y);
    IVec2 downArrowPosition(upArrowPosition.x, upArrowPosition.y + backgroundSize.height - pDownArrow->getSize().height);
    IVec2 cursorPosition(0, uiPosition.y + (actualPosition-offsetCursorPosition) * (pCursor->getSize().height+1) + 5);

    errorFlag &= pBackgroundUI->draw(r,uiPosition,time);
    if ( unitsList.size() > 6 )
    {
        if ( offsetCursorPosition > 0 )
        {
            errorFlag &= pUpArrow->draw(r,upArrowPosition,time);
        }

        if ( offsetCursorPosition < 4 )
        {
            errorFlag &= pDownArrow->draw(r,downArrowPosition,time);
        }
    }

    errorFlag &= pCursor->draw(r,cursorPosition,time);

    /**
        Offset cursor make the list behaving in the way that until the cursor is not down, we are displaying the first of the list
    */
    for ( unsigned int i = offsetCursorPosition ; i < unitsList.size() && i < offsetCursorPosition+7 ; i++ )
    {
        IVec2 unitPosition(40, uiPosition.y + 6 + (i-offsetCursorPosition) * (unitsList[i]->get(faction)->getSprite()->getSize().height+1));

        // Convertion of the price into a string
        std::string priceString = "0";
        {
            std::ostringstream oss;

            oss << unitsList[i]->get(faction)->getPrice();

            priceString = oss.str();
        }

        IVec2 unitPricePosition(backgroundSize.width - (pFont->getStringSize(priceString).width), unitPosition.y + 6);
        IVec2 unitNamePosition(backgroundSize.width - (60 + pFont->getStringSize(unitsList[i]->get(faction)->getName()).width) , unitPricePosition.y);

        if ( unitsList[i]->get(faction)->getPrice() <= moneyAvailable )
        {
            errorFlag &= unitsList[i]->get(faction)->getSprite()->draw(r,unitPosition);
            errorFlag &= pFont->draw(r,unitsList[i]->get(faction)->getName(),unitNamePosition);
            errorFlag &= pFont->draw(r,priceString,unitPricePosition);
        }
        else
        {
            errorFlag &= unitsList[i]->get(faction)->getSpriteGreyed()->draw(r,unitPosition);
            errorFlag &= pFontGrey->draw(r,unitsList[i]->get(faction)->getName(),unitNamePosition);
            errorFlag &= pFontGrey->draw(r,priceString,unitPricePosition);
        }
    }

    return errorFlag;
}

void ConstructBox :: update(const NE::InputManager::ArrowsDirection kd)
{
    switch (kd)
    {
        case NE::InputManager::AD_UP:
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
        case NE::InputManager::AD_DOWN:
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

const UnitTemplate* ConstructBox :: getUnitSelected(const unsigned int faction)const
{
    return unitsList[actualPosition]->get(faction);
}
