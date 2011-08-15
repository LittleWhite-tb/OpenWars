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

#include "MapDrawer.h"

#include "NEngine/Renderer.h"

#include "Engine/AnimatedSprite.h"
#include "Engine/Params.h"
#include "Engine/Theme.h"

#include "Game/GameState/GameObjects/Map/Map.h"
#include "Game/GameState/GameObjects/Camera.h"

#include "Types/Colour.h"

#include "globals.h"

bool MapDrawer :: drawTerrain(const NE::Renderer& r, const Map* pMap, const Camera& c, const unsigned int time)
{
	UVec2 cameraPosition = c.getPosition();
	IVec2 tilePos(0,0);
	bool bError = true;
	const std::vector < std::vector < const Tile* > >& tilesMap = pMap->constTilesMap();

	// The camera is an offset of the Map drawing
	// For each lines
	for ( unsigned int y = cameraPosition.y ; y < MAP_MIN_HEIGHT+cameraPosition.y ; y++ )
	{
		tilePos.x = 0;//mapOffset.width;
		// For each columns
		for ( unsigned int x = cameraPosition.x ; x < MAP_MIN_WIDTH+cameraPosition.x ; x++ )
		{
			// Calculation of the offset for sprite with higher size than normal Tile (e.g.: Mountains)
			unsigned int yOffset = tilesMap[y][x]->getSprite()->getSize().height - TILE_DEFAULT_HEIGHT;

			// Draw the background sprite ( Plain )
			if ( tilesMap[y][x]->getParams()->getAs<bool>("needBackground",false) )
			{
				bError &= pMap->getTheme()->getTile("Plain")->getSprite()->draw(r,tilePos,0);
			}

			// Apply offset
			tilePos.y -= yOffset;

			// Draw terrain
			bError &= tilesMap[y][x]->getSprite()->draw(r,tilePos,time);
			
			// Remove offset ( to not affect other sprite )
            tilePos.y += yOffset;
  
            // Move on the right
            tilePos.x += tilesMap[y][x]->getSprite()->getSize().width;
        }

        // To put 0 here, can be a bit dangerous
        tilePos.y += TILE_DEFAULT_HEIGHT;
    }

	return bError;
}

bool MapDrawer :: drawUnits(const NE::Renderer& r, const Map* pMap, const Camera& c, const unsigned int time)
{
	UVec2 cameraPosition = c.getPosition();
	IVec2 tilePos(0,0);
	bool bError = true;
	const std::vector < std::vector < Unit > >& unitsMap = pMap->constUnitsMap();

	// The camera is an offset of the Map drawing
	// For each lines
	for ( unsigned int y = cameraPosition.y ; y < MAP_MIN_HEIGHT+cameraPosition.y ; y++ )
	{
		tilePos.x = 0;//mapOffset.width;
		// For each columns
		for ( unsigned int x = cameraPosition.x ; x < MAP_MIN_WIDTH+cameraPosition.x ; x++ )
		{
			// Draw unit
			if ( unitsMap[y][x].state != US_NO_UNIT )	// If we have a unit
			{
                if ( unitsMap[y][x].state == US_ACTIVE )
                {
					bError &= unitsMap[y][x].getSprite()->draw(r,tilePos,time);
                }
                else
                {
					bError &= unitsMap[y][x].getSprite()->draw(r,tilePos,Colour(128,128,128,255),0);
                }
			}
  
            // Move on the right
            tilePos.x += TILE_DEFAULT_WIDTH;
        }

        // To put 0 here, can be a bit dangerous
        tilePos.y += TILE_DEFAULT_HEIGHT;
    }

	return bError;
}

/*
bool MapDrawer::draw(const NE::Renderer& r, const Map* pMap, const Camera& c, const unsigned int time)
{
	assert(pMap);

	bool bError = true;
	
	bError &= MapDrawer::drawTerrain(r,pMap,c,time);
	bError &= MapDrawer::drawUnits(r,pMap,c,time);

    return bError;
}
*/