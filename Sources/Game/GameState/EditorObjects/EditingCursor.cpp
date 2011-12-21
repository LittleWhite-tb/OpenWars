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

#include "EditingCursor.h"

#include "NEngine/NEngine.h"

#include "Engine/AnimatedSprite.h"
#include "Engine/Theme.h"

#include "Game/GameState/GameObjects/Map/Map.h"
#include "Game/GameState/GameObjects/Camera.h"

#include "UI/UIItem.h"

#include "globals.h"

EditingCursor :: EditingCursor(const Map* const pMap, const UVec2& initialPosition)
	:Cursor(pMap,initialPosition),isWrong(false)
{
	// The size of the tiles and the cursor are the same to have better effect
	pWrongCursorSprite = pMap->getTheme()->getUIItem("cursorWrong")->getSprite();

    NE::NEngine::logger()->log(NE::LL_Debug,"EditingCursor created %d;%d ",initialPosition.x,initialPosition.y);
}

EditingCursor :: ~EditingCursor(void)
{
    NE::NEngine::logger()->log(NE::LL_Debug,"EditingCursor deleted");
}

bool EditingCursor :: draw(const NE::Renderer& r, const Camera& c, const unsigned int time)const
{
	UVec2 cameraPosition = c.getPosition();
	IVec2 screenPosition = IVec2((this->position.x - cameraPosition.x ) * TILE_DEFAULT_WIDTH,
								 (this->position.y - cameraPosition.y ) * TILE_DEFAULT_HEIGHT);
/*
	screenPosition.x += Scaler::getOffset().width;
	screenPosition.y += Scaler::getOffset().height;
*/
	if ( isWrong )
	{
		return pWrongCursorSprite->draw(r,screenPosition,time);
	}
	else
	{
		return pCursorSprite->draw(r,screenPosition,time);
	}
}
