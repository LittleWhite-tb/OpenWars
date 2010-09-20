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

#include "Cursor.h"

#include "Map.h"
#include "../Engine/Renderer.h"
#include "../Engine/AnimatedSprite.h"
#include "../Engine/Controls/Keyboard.h"
#include "../Utils/Logger.h"
#include "../Utils/Scaler.h"
#include "Camera.h"
#include "../globals.h"

Cursor :: Cursor(SpriteManager& sm, const std::string& fileName, const Map* const pMap, const UVec2& initialPosition/*=IVec2(0,0)*/)
	:pMap(pMap),position(initialPosition)
{
	// The size of the tiles and the cursor are the same to have better effect
	pCursorSprite = new AnimatedSprite(sm,fileName,TILE_DEFAULT_WIDTH, TILE_DEFAULT_HEIGHT, CURSOR_SPEED,true);

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

	LDebug << "Cursor created " << initialPosition;
}

Cursor :: ~Cursor(void)
{
	delete pCursorSprite;

	LDebug << "Cursor deleted";
}

Tile Cursor :: getTileUnderCursor(void)const
{
	return pMap->getTile(this->position);
}

bool Cursor :: move(const ArrowsDirection ad)
{
	UVec2 newPosition = this->position;

	// The conditions are here to allow the user to go in a direction, even if the cursor is already on the bound of the other direction
	switch(ad)
	{
	case AD_UP:
		newPosition.y--;
		break;
	case AD_UPRIGHT:
		if ( position.y > 0 )
		{
			newPosition.y--;
		}

		if ( position.x < pMap->getWidth()-1 )
		{
			newPosition.x++;
		}

		break;
	case AD_RIGHT:
		newPosition.x++;
		break;
	case AD_RIGHTDOWN:
		if ( position.x < pMap->getWidth()-1 )
		{
			newPosition.x++;
		}

		if ( position.y < pMap->getHeight()-1 )
		{
			newPosition.y++;
		}

		break;
	case AD_DOWN:
		newPosition.y++;
		break;
	case AD_DOWNLEFT:
		if ( position.y < pMap->getHeight()-1 )
		{
			newPosition.y++;
		}

		if ( position.x > 0 )
		{
			newPosition.x--;
		}
		break;
	case AD_LEFT:
		newPosition.x--;
		break;
	case AD_LEFTUP:
		if ( position.x > 0 )
		{
			newPosition.x--;
		}

		if ( position.y > 0 )
		{
			newPosition.y--;
		}
		break;
	case AD_NONE:
		return true;
		break;
	}

	return this->move(newPosition);
}

bool Cursor :: move(const UVec2& newPosition)
{
	LDebug << "Cursor :: move to " << newPosition;

	if ( newPosition.x >= pMap->getWidth() || newPosition.y >= pMap->getHeight() )
	{
		return false;
	}

	this->position = newPosition;
	return true;
}

bool Cursor :: draw(const Renderer& r, const Camera& c, const unsigned int time)const
{
	UVec2 cameraPosition = c.getPosition();
	IVec2 screenPosition = IVec2((this->position.x - cameraPosition.x ) * (static_cast<int>(Scaler::getXScaleFactor() * TILE_DEFAULT_WIDTH)),
								 (this->position.y - cameraPosition.y ) * (static_cast<int>(Scaler::getYScaleFactor() * TILE_DEFAULT_HEIGHT)));

	return r.drawTile(*pCursorSprite,screenPosition,time);
}