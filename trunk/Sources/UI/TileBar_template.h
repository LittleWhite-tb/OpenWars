#ifndef __TILEBAR_TEMPLATE_H__
#define __TILEBAR_TEMPLATE_H__

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

#include "TileBar.h"

#include "Engine/AnimatedSprite.h"
#include "Engine/Theme.h"

#include "Game/GameState/GameObjects/Tile.h"

#include "Utils/Logger.h"

template <typename T>
TileBar<T> :: TileBar(NE::SpriteFactory* const pSF, const Theme* pTheme, const USize2& windowSize)
        :windowSize(windowSize)
{
    unsigned int barHeight = 64;

    pBarSprite = pSF->createSpriteFromColour(Colour(0x00000080),USize2(windowSize.width,barHeight));
    if ( pBarSprite == NULL )
    {
        ConstructionFailedException("TileBar");
        return;
    }

    // Load the cursor
    pBarCursor = pTheme->getUIItem("tileBarCursor")->getSprite();

    // Load the arrows
    pBarArrows = pTheme->getUIItem("tileBarArrows")->getSprite();

    // Final settings
    movementOffsetX = 0;
    positionY = windowSize.height;
    state = TBS_Closed;
    currentX = 0;
    currentY = 0;
    // Speed
    stepX = windowSize.width / 80;
    stepY = windowSize.height / 60;

    LDebug << "TileBar created";
}

template <typename T>
void TileBar<T> :: moveLeft(void)
{
    if ( state == TBS_Opened )
    {
        LDebug << "TileBar :: moveLeft()";
        movementOffsetX = -(TILE_DEFAULT_WIDTH + borderSize * 2);

        state = TBS_MoveLeft;

        currentX--;
    }
}

template <typename T>
void TileBar<T> :: moveRight(void)
{
    if ( state == TBS_Opened )
    {
        LDebug << "TileBar :: moveRight()";

        movementOffsetX = TILE_DEFAULT_WIDTH + borderSize * 2;

        state = TBS_MoveRight;

        currentX++;
    }
}

template <typename T>
void TileBar<T> :: moveUp(void)
{
    if ( state == TBS_Opened )
    {
        LDebug << "TileBar :: moveUp()";

        currentY++;
    }
}

template <typename T>
void TileBar<T> :: moveDown(void)
{
    if ( state == TBS_Opened )
    {
        LDebug << "TileBar :: moveDown()";

        currentY--;
    }
}

template <typename T>
void TileBar<T> :: add(const T& item, unsigned int positionX)
{
    if ( viewList.size() <= positionX )
    {
        viewList.resize(positionX+1);
    }

    viewList[positionX].push_back(ItemView(item,TILE_BAR_XMARGIN * (1 + positionX * 2) + 32 * positionX));

    limit = item->getSprite()->getSize().width + TILE_BAR_XMARGIN*2 * viewList.size();
    currentX = viewList.size()/2;
    borderSize = (windowSize.width - totalTileShown * viewList[positionX][0].item->getSprite()->getSize().width) / totalTileShown;
}

template <typename T>
void TileBar<T> :: open(void)
{
    if ( state == TBS_Closed )
    {
        LDebug << "TileBar :: open()";

        state = TBS_Opening;
    }
}

template <typename T>
void TileBar<T> :: close(void)
{
    if ( state == TBS_Opened )
    {
        LDebug << "TileBar :: close()";

        state = TBS_Closing;
    }
}

template <typename T>
void TileBar<T> :: move(const NE::InputManager::ArrowsDirection direction)
{
    switch(direction)
    {
        case NE::InputManager::AD_UP:
            moveUp();
            break;
        case NE::InputManager::AD_DOWN:
            moveDown();
            break;
        case NE::InputManager::AD_LEFT:
            moveLeft();
            break;
        case NE::InputManager::AD_RIGHT:
            moveRight();
            break;
        // Remove warnings (we don't mind about the others directions)
        default:
            break;
    }
}

template <typename T>
bool TileBar<T> :: draw(const NE::Renderer& r, const unsigned int time)
{
    bool isOk = true;

    IVec2 barPosition(0 ,positionY);

    if ( state != TBS_Closed )
    {
        isOk &= r.drawSurface(barPosition,*pBarSprite);
    }

    if ( state == TBS_Opened || state == TBS_MoveLeft || state == TBS_MoveRight )
    {
        IVec2 cursorPosition(windowSize.width / 2 - pBarCursor->getSize().width/2+3,
                             positionY + TILE_BAR_HEIGHT / 2 - pBarCursor->getSize().height/2);

        // From the first tile to show on left; to the

        for ( int i = 0 ; i < totalTileShown ; i++ )
        {
            int indexX = (currentX-nbShownAroundSelected + i);
            if ( indexX < 0 )
            {
                indexX = viewList.size() - abs(indexX);
            }
            indexX = indexX % viewList.size();

            int yOffset = viewList[indexX][currentY%viewList[indexX].size()].item->getSprite()->getSize().height - TILE_DEFAULT_HEIGHT;
            IVec2 tilePosition((i*2+1) * borderSize + i * viewList[0][0].item->getSprite()->getSize().width + movementOffsetX, positionY + TILE_BAR_YMARGIN *2 - yOffset);

            viewList[indexX][currentY % viewList[indexX].size()].item->getSprite()->draw(r,tilePosition,time);
        }

        // Need to draw an additionnal sprite on the right
        if ( state == TBS_MoveRight )
        {
            int indexX = (currentX-nbShownAroundSelected - 1);
            if ( indexX < 0 )
            {
                indexX = viewList.size() - abs(indexX);
            }
            indexX = indexX % viewList.size();
            int yOffset = viewList[indexX][currentY%viewList[indexX].size()].item->getSprite()->getSize().height - TILE_DEFAULT_HEIGHT;
            IVec2 tilePosition(movementOffsetX - viewList[indexX][0].item->getSprite()->getSize().width - borderSize, positionY + TILE_BAR_YMARGIN *2 - yOffset);

            viewList[indexX][currentY % viewList[indexX].size()].item->getSprite()->draw(r,tilePosition,time);
        }

        int indexX = currentX-1;
        if ( indexX < 0 )
        {
            indexX = viewList.size() - abs(indexX);
        }
        indexX = indexX % viewList.size();

        // Draw the cursor
        isOk &= pBarCursor->draw(r,cursorPosition,time);
        // Draw the arrow if needed
        if ( viewList[indexX].size() > 1 && state == TBS_Opened )
        {
            isOk &= pBarArrows->draw(r,cursorPosition);
        }
    }

    return isOk;
}

template <typename T>
void TileBar<T> :: update(const unsigned int time)
{
    switch (state)
    {
        case TBS_Closing:
            positionY+=stepY;
            if ( positionY >= windowSize.height )
            {
                state = TBS_Closed;
            }
            break;
        case TBS_Opening:
            positionY-=stepY;
            if ( positionY <= windowSize.height - 64 )
            {
                state = TBS_Opened;
            }
            break;
        case TBS_MoveRight:
            if ( movementOffsetX > static_cast<int>(stepX) )
            {
                movementOffsetX-=stepX;
            }
            else
            {
                movementOffsetX-=movementOffsetX;
            }

            if ( movementOffsetX <= 0 )
            {
                state = TBS_Opened;
            }
            break;
        case TBS_MoveLeft:
            if ( movementOffsetX < -stepX )
            {
                movementOffsetX+=stepX;
            }
            else
            {
                movementOffsetX-=movementOffsetX;
            }

            if ( movementOffsetX >= 0 )
            {
                state = TBS_Opened;
            }
            break;
        // Remove warnings (static case)
        case TBS_Opened:
        case TBS_Closed:
            break;
    }
}

template <typename T>
T TileBar<T> :: getSelected(void)
{
    int indexX = currentX-1;
    if ( indexX < 0 )
    {
        indexX = viewList.size() - abs(indexX);
    }
    indexX = indexX % viewList.size();

    if ( viewList[indexX].size() == 1 )
    {
        return viewList[indexX][0].item;
    }
    else
    {
        return viewList[indexX][currentY%viewList[indexX].size()].item;
    }
}

#endif