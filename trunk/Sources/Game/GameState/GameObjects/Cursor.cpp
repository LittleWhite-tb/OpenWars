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

#include "Cursor.h"

#include "NEngine/NEngine.h"
#include "NEngine/InputManager.h"

#include "Engine/AnimatedSprite.h"

#include "Game/GameState/GameObjects/Map/Map.h"
#include "Game/GameState/GameObjects/Camera.h"

#include "globals.h"

Cursor :: Cursor(const Map* const pMap, const UVec2& initialPosition/*=IVec2(0,0)*/)
	:pMap(pMap),position(initialPosition)
{
	// The size of the tiles and the cursor are the same to have better effect
	pCursorSprite = pMap->getTheme()->getUIItem("cursor")->getSprite();

	// Check if the position entered is correct
	if ( position.x >= pMap->getWidth() )
	{
		// 0, if it was wrong
		position.x = 0;
	}

	if ( position.y >= pMap->getHeight() )
	{
		// 0, if it was wrong
		position.y = 0;
	}

    NE::NEngine::logger()->log(NE::LL_Debug,"Cursor created %d;%d",initialPosition.x,initialPosition.y);
}

Cursor :: ~Cursor(void)
{
    NE::NEngine::logger()->log(NE::LL_Debug,"Cursor deleted");
}

const Tile* Cursor :: getTileUnderCursor(void)const
{
	return pMap->getTile(this->position);
}

bool Cursor :: move(const NE::InputManager::ArrowsDirection ad)
{
	UVec2 newPosition = this->position;

	// The conditions are here to allow the user to go in a direction, even if the cursor is already on the bound of the other direction
	switch(ad)
	{
	case NE::InputManager::AD_UP:
		newPosition.y--;
		break;
	case NE::InputManager::AD_UPRIGHT:
		if ( position.y > 0 )
		{
			newPosition.y--;
		}

		if ( position.x < pMap->getWidth()-1 )
		{
			newPosition.x++;
		}

		break;
	case NE::InputManager::AD_RIGHT:
		newPosition.x++;
		break;
	case NE::InputManager::AD_RIGHTDOWN:
		if ( position.x < pMap->getWidth()-1 )
		{
			newPosition.x++;
		}

		if ( position.y < pMap->getHeight()-1 )
		{
			newPosition.y++;
		}

		break;
	case NE::InputManager::AD_DOWN:
		newPosition.y++;
		break;
	case NE::InputManager::AD_DOWNLEFT:
		if ( position.y < pMap->getHeight()-1 )
		{
			newPosition.y++;
		}

		if ( position.x > 0 )
		{
			newPosition.x--;
		}
		break;
	case NE::InputManager::AD_LEFT:
		newPosition.x--;
		break;
	case NE::InputManager::AD_LEFTUP:
		if ( position.x > 0 )
		{
			newPosition.x--;
		}

		if ( position.y > 0 )
		{
			newPosition.y--;
		}
		break;
	case NE::InputManager::AD_NONE:
		return true;
		break;
	}

	return this->move(newPosition);
}

bool Cursor :: move(const UVec2& newPosition)
{
	if ( newPosition.x >= pMap->getWidth() || newPosition.y >= pMap->getHeight() )
	{
		return false;
	}

	this->position = newPosition;
	return true;
}

bool Cursor :: draw(const NE::Renderer& r, const Camera& c, const unsigned int time)const
{
	UVec2 cameraPosition = c.getPosition();
	IVec2 screenPosition = IVec2((this->position.x - cameraPosition.x ) * TILE_DEFAULT_WIDTH,
								 (this->position.y - cameraPosition.y ) * TILE_DEFAULT_HEIGHT);
/*
	screenPosition.x += Scaler::getOffset().width;
	screenPosition.y += Scaler::getOffset().height;
*/
	return pCursorSprite->draw(r,screenPosition,time);
}
