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

#include "Properties.h"

#include <cassert>

#include "../Utils/Exceptions/FileNotOpenedException.h"
#include "../Utils/LineParser.h"
#include "../Utils/Logger.h"

bool Properties :: loadTiles(LineParser& lp)
{
    bool notAtEnd = true;

    for ( int i = 0 ; i < TT_END_LIST ; i++ )
    {
        int tileID = lp.getInt();
        if ( tileID >= TT_END_LIST )
        {
            LError << "ID not corresponding to any tile (Max expected: " << TT_END_LIST << " Received: " << tileID << ")";
            return false;
        }

        notAtEnd &= lp.readNextLine();
        int defence = lp.getInt();
        notAtEnd &= lp.readNextLine();
        int isRoad = lp.getInt();
        notAtEnd &= lp.readNextLine();
        int isBridge = lp.getInt();
        notAtEnd &= lp.readNextLine();
        int isRiver = lp.getInt();
        notAtEnd &= lp.readNextLine();
        int isSea = lp.getInt();
        notAtEnd &= lp.readNextLine();
        int isBeach = lp.getInt();
        notAtEnd &= lp.readNextLine();
        int isBuilding = lp.getInt();
        notAtEnd &= lp.readNextLine();
        int isHQ = lp.getInt();
        notAtEnd &= lp.readNextLine();

        TileProperties tp(defence, isRoad, isBridge, isRiver, isSea, isBeach, isBuilding, isHQ);

        if ( notAtEnd == false )
        {
            LError << "End of file unexpected";
            return false;
        }

        tiles[static_cast<TileType>(tileID)]=tp;
    }

    return true;
}

bool Properties :: loadUnits(LineParser& lp)
{
    bool notAtEnd = true;

    for ( int i = 0 ; i < UT_END_LIST ; i++ )
    {
        int unitID = lp.getInt();
        if ( unitID >= UT_END_LIST )
        {
            LError << "ID not corresponding to any tile (Max expected: " << UT_END_LIST << " Received: " << unitID << ")";
            return false;
        }

        notAtEnd &= lp.readNextLine();
        int category = lp.getInt();
        notAtEnd &= lp.readNextLine();
        int tCategory = lp.getInt();
        notAtEnd &= lp.readNextLine();
        int movement = lp.getInt();
        notAtEnd &= lp.readNextLine();
        int fuel = lp.getInt();
        notAtEnd &= lp.readNextLine();
        int fuelConsumption = lp.getInt();
        notAtEnd &= lp.readNextLine();
        int ammo = lp.getInt();
        notAtEnd &= lp.readNextLine();
        int maxLive = lp.getInt();
        notAtEnd &= lp.readNextLine();
        int price = lp.getInt();
        notAtEnd &= lp.readNextLine();

        UnitProperties up(category, tCategory, movement, fuel, fuelConsumption, ammo, maxLive, price);

        if ( notAtEnd == false )
        {
            LError << "End of file unexpected";
            return false;
        }

        units[static_cast<UnitType>(unitID)]=up;
    }

    return false;
}

bool Properties :: load(void)
{
    bool bResult = true;

    try
    {
        LineParser lpTiles("data/properties/"+name+"/tiles.ppts");
        LineParser lpUnits("data/properties/"+name+"/units.ppts");

        bResult &= loadTiles(lpTiles);
        bResult &= loadUnits(lpUnits);
    }
    catch ( FileNotOpenedException fnoe )
    {
        return false;
    }

    return bResult;
}

const TileProperties& Properties :: Properties :: getTile(const TileType tType)
{
    assert(tType != TT_Invalid &&  tType != TT_END_LIST);

    return tiles[tType];
}

const UnitProperties& Properties :: getUnit(const UnitType uType)
{
    assert(uType != UT_NO_UNIT &&  uType != UT_END_LIST);

    return units[uType];
}
