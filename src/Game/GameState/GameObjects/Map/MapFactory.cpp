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

#include "MapFactory.h"

#include "NEngine/NEngine.h"

#include "Game/GameState/GameObjects/Map/Map.h"

Map* MapFactory :: createEmptyMap(const Theme* pTheme, const USize2& size)
{
    Map* pMap = new Map(pTheme);

    if ( pMap == NULL )
    {
        NEError << "Failed to allocate Map memory\n";
        throw std::bad_alloc();
    }

    pMap->allocateMemory(size);

    std::vector < std::vector < const Tile* > >* pTilesMap = NULL;
    pTilesMap = pMap->getTilesMap();
    if ( pTilesMap == NULL )
    {
        NEError << "Error while getting the tile board\n";
        delete pMap;
        return NULL;
    }

    for ( unsigned int y = 0 ; y < size.height ; y++ )
    {
        for ( unsigned int x = 0 ; x < size.width ; x++ )
        {
            (*pTilesMap)[y][x] = pTheme->getTile(0);
        }
    }

    return pMap;
}
