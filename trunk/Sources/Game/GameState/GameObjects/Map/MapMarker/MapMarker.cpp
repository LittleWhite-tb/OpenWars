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

#include "MapMarker.h"

#include <cassert>

#include "NEngine/NEngine.h"
#include "Engine/AnimatedSprite.h"
#include "Game/GameState/GameObjects/Map/Map.h"
#include "Game/GameState/GameObjects/Camera.h"

#include "globals.h"

MapMarker :: MapMarker(const Map* pMap, AnimatedSprite* pMarkerSprite)
	:pMap(pMap),pMarkerSprite(pMarkerSprite)
{
	assert(pMap);
	assert(pMarkerSprite);

	marks.resize(pMap->getHeight());
	for ( unsigned int y = 0 ; y < pMap->getHeight() ; y++ )
	{
		marks[y].resize(pMap->getWidth(),0);
	}
}

void MapMarker :: setMarksInRange(const UVec2& position, unsigned int minRange, unsigned int maxRange)
{
	for ( unsigned int y = 0 ; y < marks.size() ; y++ )
	{
		for ( unsigned int x = 0 ; x < marks[y].size() ; x++ )
		{
			unsigned int dist = distance(position,UVec2(x,y));
			if ( dist >= minRange && dist <= maxRange ) 
			{
				marks[y][x] = 1;
			}
		}
	}
}

void MapMarker :: clear()
{
	for ( unsigned int y = 0 ; y < marks.size() ; y++ )
	{
		for ( unsigned int x = 0 ; x < marks[y].size() ; x++ )
		{
			marks[y][x] = -1;
		}
	}
}

bool MapMarker :: isMarked(const UVec2& position)const
{
	if ( pMap->isValidPosition(position) == false )
	{
		return false;
	}
	if ( marks[position.y][position.x] != -1 )
	{
		return true;
	}

	return false;
}

void MapMarker :: setMarksForUnitAt(const UVec2& position)
{
	this->clear();

	if ( pMap->isValidPosition(position) == false )
	{
        NE::NEngine::logger()->log(NE::LL_Warning,"Passing invalid position to GlobalAttackMapMarker :: setMarks");
		return;
	}

	const Unit* pUnit = pMap->getUnit(position);

	if ( pUnit == NULL )
	{
        NE::NEngine::logger()->log(NE::LL_Warning,"No unit at: %d;%d for GlobalAttackMapMarker :: setMarks",position.x,position.y);
		return;
	}

	this->setMarks(position,pUnit);
}

bool MapMarker :: draw(const NE::Renderer& r, const Camera& c, const unsigned int time)
{
	UVec2 cameraPosition = c.getPosition();
	IVec2 tilePos(0,0);
	bool bResult = true;

	// The camera is an offset of the Map drawing
	// For each lines
	for ( unsigned int y = cameraPosition.y ; y < MAP_MIN_HEIGHT+cameraPosition.y ; y++ )
	{
		tilePos.x = 0;//mapOffset.width;
		// For each columns
		for ( unsigned int x = cameraPosition.x ; x < MAP_MIN_WIDTH+cameraPosition.x ; x++ )
		{
			if ( marks[y][x] != -1 )	// If we have a mark
			{
				bResult &= pMarkerSprite->draw(r,tilePos,time);
			}

			// Move on the right
            tilePos.x += TILE_DEFAULT_WIDTH;
        }

        // To put 0 here, can be a bit dangerous
        tilePos.y += TILE_DEFAULT_HEIGHT;
	}

	return bResult;
}