#ifndef DOXYGEN_IGNORE_TAG
/**
OpenAWars is an open turn by turn strategic game similar to Advance Wars (c)
Copyright (C) 2010-2015  Alexandre LAURENT

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

website: https://github.com/LittleWhite-tb/OpenWars
e-mail: lw.demoscene@gmail.com
**/
#endif

#include "MenuBox.h"

#include "NEngine/NEngine.h"
#include "NEngine/SpriteFactory.h"
#include "NEngine/Sprite.h"
#include "NEngine/Renderer.h"
#include "NEngine/InputManager.h"

#include "Engine/AnimatedSprite.h"
#include "Engine/Font.h"
#include "Engine/Theme.h"

#include "NEngine/Exceptions/ConstructionFailedException.h"

#include "ow_globals.h"

MenuBox :: MenuBox(NE::SpriteFactory* const pSF, const Theme* pTheme, const USize2& windowSize)
    :pCursor(pTheme->getUIItem("cursor")->getSprite()),actualPosition(0)
{
    pBackground = pSF->createSpriteFromColour(Colour(0xC0C0C0C0), USize2(150,10 + TILE_DEFAULT_HEIGHT));
    if ( pBackground == NULL )
    {
        throw ConstructionFailedException("MenuBox");
        return;
    }

    windowXPosition = windowSize.width;

    pFont = pTheme->getFontObject("classic")->getFont();
}

unsigned int MenuBox :: countNumberValidEntries()const
{
    unsigned int counter = 0;
    for ( std::vector<MenuItem>::const_iterator itEntry = entries.begin() ; itEntry != entries.end() ; ++itEntry )
    {
        if ( itEntry->enabled )
        {
            counter++;
        }
    }

    return counter;
}

MenuBox::MenuItem* MenuBox :: getEntry(const std::string& entryActionName)
{
    for ( unsigned int i = 0 ; i < entries.size() ; i++ )
    {
        if ( entryActionName == entries[i].actionName )
        {
            return &entries[i];
        }
    }

    NEWarning << "MenuBox::getEntry('" << entryActionName << "') not found\n";
    return NULL;
}

void MenuBox :: add(const std::string& actionName, AnimatedSprite* const pSprite, const std::string& displayName)
{
    entries.push_back(MenuBox::MenuItem(actionName, pSprite, displayName));
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

    unsigned int validEntriesCounter = 0;
    for ( unsigned int i = 0 ; i < entries.size() ; i++ ) // For all entries
    {
        if ( entries[i].enabled )   // We draw only valid entries
        {
            itemPosition.y = itemPosition.y -5;
            bError &= r.drawSurface(itemPosition,pBackground); // Draw the background for the entry
            itemPosition.y = itemPosition.y +5;
            if ( validEntriesCounter == actualPosition )
            {
                IVec2 cursorPosition(position.x - 15, itemPosition.y);
                bError &= pCursor->draw(r,cursorPosition,time);
            }
            if ( entries[i].pASprite != NULL )
            {
                bError &= entries[i].pASprite->draw(r,itemPosition,time);
            }
            {
                IVec2 textPosition(position.x + TILE_DEFAULT_WIDTH + 24, itemPosition.y + TILE_DEFAULT_HEIGHT / 2);
                USize2 textSize = pFont->getStringSize(entries[i].displayName);
                textPosition.y -= textSize.height/2;
                pFont->draw(r,entries[i].displayName, textPosition);
            }
            itemPosition.y += 10 + TILE_DEFAULT_HEIGHT;
            validEntriesCounter++;
        }
    }

    return bError;
}

void MenuBox ::update(const NE::InputManager::ArrowsDirection kd)
{
    switch (kd)
    {
        case NE::InputManager::AD_DOWN:
            if ( actualPosition < this->countNumberValidEntries()-1 )
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

const std::string& MenuBox :: getSelectedActionName(void)const
{
    static const std::string returnError = "";

    unsigned int validEntriesCounter = 0;
    for ( unsigned int i = 0 ; i < entries.size() ; i++ ) // For all entries
    {
        if ( entries[i].enabled )
        {
            if ( validEntriesCounter == actualPosition )
            {
                return entries[i].actionName;
            }
            validEntriesCounter++;
        }
    }

    NEWarning << "MenuBox::getSelectedActionName -> No valid entry found\n";
    return returnError;
}

void MenuBox :: enableEntry(const std::string& entryActionName)
{
    MenuItem* pItem = this->getEntry(entryActionName);
    if ( pItem != NULL )
    {
        pItem->enabled = true;
    }
}

void MenuBox :: disableEntry(const std::string& entryActionName)
{
    MenuItem* pItem = this->getEntry(entryActionName);
    if ( pItem != NULL )
    {
        pItem->enabled = false;
    }
}
