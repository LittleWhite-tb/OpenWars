#ifndef __MAPINTEGRITYCHECKER_H__
#define __MAPINTEGRITYCHECKER_H__

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

#include <map>
#include <string>

#include "Types/Vec2.h"

class Map;
class Tile;
class UnitTemplate;

class MapIntegrityChecker
{
    typedef const Tile* (*checker) (const Map* pMap, const UVec2& position);

private:

protected:
    const Map* pMap;									/*!< Pointer to the map to check */

    std::map<std::string, checker> coherencyCheckers;	/*!< Dictionnary of checkers */

public:
    MapIntegrityChecker(const Map* pMap);
    virtual ~MapIntegrityChecker();

    virtual void addChecker(const std::string& name)=0;

    const Tile* checkCoherency(const UVec2& position, const Tile* pTile = NULL);

    virtual bool testTile(const UVec2& position, const Tile* pTile)const=0;
    virtual bool testUnit(const UVec2& position, const UnitTemplate* pUnitTemplate)const=0;
};

/*! \class MapIntegrityChecker MapIntegrityChecker.h "Game/GameState/GameObjects/Map/MapIntegrityChecker.h"
 *  \brief base class for Map integrity checking
 */

/*! \fn MapIntegrityChecker::MapIntegrityChecker(const Map* pMap);
 *  \param pMap pointer to the map to check
 */

/*! \fn MapIntegrityChecker::~MapIntegrityChecker();
 */

/*! \fn virtual void MapIntegrityChecker::addChecker(const std::string& name)=0;
 *  \brief Adds a integrity checker in the list of checkers to use to check integrity.
 *  \param name the name of the checker
 *  This new integrity checker will be called by the checkCoherency function when a tile refers to a checker with this name
 */

/*! \fn const Tile* MapIntegrityChecker::checkCoherency(const UVec2& position, const Tile* pTile = NULL)
 *  \brief Check the coherency of the map for this position
 *  \param position the position to check
 *  \param pTile pointer to the Tile to put on the map at this position
 */

/*! \fn virtual bool MapIntegrityChecker::testTile(const UVec2& position, const Tile* pTile)const=0;
 *  \brief Test if a tile can be put at this position
 *  \param position the position to check
 *  \param pTile pointer to the Tile to put on the map at this position
 */

/*! \fn virtual bool MapIntegrityChecker::testUnit(const UVec2& position, const UnitTemplate* pUnitTemplate)const=0;
 *  \brief Test if a unit can be put at this position
 *  \param position the position to check
 *  \param pUnitTemplate pointer to the UnitTemplate to put on the map at this position
 */

#endif
