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

#include <sstream>

#include "MapLoader.h"

#include "NEngine/NEngine.h"

#include "Engine/Library.h"

#include "Game/GameState/GameObjects/Map/Map.h"

#include "Utils/LineParser.h"

Map* MapLoader :: loadMapFromFile(const Library<Theme>* const pThemes, const std::string& fileName)
{
    std::string themeName = "classic";
    Map* pMap = NULL;
    std::vector < std::vector < const Tile* > >* pTilesMap = NULL;
    std::vector < std::vector < Unit > >* pUnitsMap = NULL;
    unsigned int mapLineCounter = 0;
    unsigned int unitMapLineCounter = 0;
    USize2 size;
    bool error = false;

    LineParser lp(fileName);

    NE::NEngine::logger().log(NE::LL_Debug,"MapLoader::loadMapFromFile '%s'",fileName.c_str());

    do
    {
        if ( lp.getLineNumber() == 1 )
        {
            themeName = lp.getLine();

            if ( !pThemes->exists(themeName) )
            {
                NE::NEngine::logger().log(NE::LL_Error,"Map is asking for a theme not found");
                error = true;
            }

            pMap = new Map(pThemes->get(themeName));
            if ( pMap == NULL )
            {
                NE::NEngine::logger().log(NE::LL_Error,"Failed to allocate Map memory");
                throw std::bad_alloc();
            }

            NE::NEngine::logger().log(NE::LL_Debug,"Theme: %s",themeName.c_str());

        }
        else if ( lp.getLineNumber() == 2 )
        {
            size = lp.getUSize2();

            if ( size.width != 0 || size.height != 0 )  // If it looks correct (we can add a maximum size... to be safer)
            {
                pMap->allocateMemory(size);
                pTilesMap = pMap->getTilesMap();
                pUnitsMap = pMap->getUnitsMap();
                if ( pTilesMap == NULL || pUnitsMap == NULL )
                {
                    NE::NEngine::logger().log(NE::LL_Error,"Error while getting the Map boards");
                    error = true;
                }
            }
            else
            {
                NE::NEngine::logger().log(NE::LL_Error,"Size of the map not valid (%d;%d)",size.width,size.height);
                error = true;
            }
        }
        else if ( lp.getLineNumber() >= 3 && lp.getLineNumber() < 3 + size.height ) // For all lines representating the map
        {
            std::stringstream ss(lp.getLine());
            int tileID = -1;

            mapLineCounter++;

            // We are reading one line, by one
            for ( unsigned int x = 0 ; x < size.width ; x++ )
            {
                ss >> tileID;
                if ( tileID != -1 )
                {
                    if ( pThemes->get(themeName)->containsTile(tileID) )
                    {
                        (*pTilesMap)[lp.getLineNumber()-3][x] = pThemes->get(themeName)->getTile(tileID);
                    }
                    else
                    {
                        NE::NEngine::logger().log(NE::LL_Warning,"Tile data in the map invalid (%d) at position %d;%d",tileID,x,lp.getLineNumber()-3);
                        error = true;
                    }
                }
                else
                {
                    NE::NEngine::logger().log(NE::LL_Error,"Fail to read the tile type @%d;%d",x,lp.getLineNumber()-3);
                    error = true;
                }
            }
        }
        else if ( lp.getLineNumber() >= 3+size.height && lp.getLineNumber() < 3+size.height*2 ) // For the unit map
        {
            std::stringstream ss(lp.getLine());
            int unitID = -42;

            unitMapLineCounter++;

            // We are reading one line, by one
            for ( unsigned int x = 0 ; x < size.width ; x++ )
            {
                ss >> unitID;
                if ( unitID != -42 )
                {
                    if ( unitID == -1 )
                    {
                        (*pUnitsMap)[lp.getLineNumber()-(3+size.height)][x] = Unit();
                    }
                    else if ( pThemes->get(themeName)->containsUnit(unitID) )
                    {
                        (*pUnitsMap)[lp.getLineNumber()-(3+size.height)][x] = Unit(pThemes->get(themeName)->getUnit(unitID));
                    }
                    else
                    {
                        NE::NEngine::logger().log(NE::LL_Warning,"Data in the map invalid (%d)",unitID);
                        error = true;
                    }
                }
                else
                {
                    NE::NEngine::logger().log(NE::LL_Error,"Fail to read the tile type @%d;%d",x,lp.getLineNumber()-(3+size.height));
                    error = true;
                }
            }
        }
    }while(error != true && lp.readNextLine());

    if ( error == true )
    {
        delete pMap;
        return NULL;
    }

    return pMap;
}
