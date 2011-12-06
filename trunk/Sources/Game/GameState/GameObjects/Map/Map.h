#ifndef __MAP_H__
#define __MAP_H__

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

#include <string>
#include <vector>
#include <map>

#include "Engine/Theme.h"
#include "Engine/Library.h"

#include "Game/GameState/GameObjects/Tile.h"
#include "Game/GameState/GameObjects/Unit.h"

#include "NEngine/Types/Size2.h"
#include "NEngine/Types/Vec2.h"

namespace NE { class Renderer; }
namespace NE { class SpriteLoader; }

class Camera;
class AnimatedSprite;
class MapIntegrityChecker;

class Map
{
private:
    MapIntegrityChecker* pIntegrityChecker;                                 /*!< pointer on the checker to use to keep integrity of the map */

    void checkCoherency(const UVec2& position, const Tile* pTileToPut);

    bool allocateMemory(const USize2& size);

    std::vector < std::vector < const Tile* > >* getTilesMap() { return &tileMap; }
    std::vector < std::vector < Unit > >* getUnitsMap() { return &unitMap; }

protected:

    const Theme* pTheme;        /*!< Pointer on the theme to use */

    unsigned int width;         /*!< Width (in tile) of the map */
    unsigned int height;        /*!< Height (in tile) of the map */

    std::vector < std::vector < const Tile* > > tileMap;    /*!< 2D Array representating the map */
    std::vector < std::vector < Unit > > unitMap;   /*!< 2D Array representating the unit on the map */

public:
    Map(const Theme* const pTheme);
    virtual ~Map(void);

    const std::vector < std::vector < const Tile* > >& constTilesMap()const { return tileMap; }
    const std::vector < std::vector < Unit > >& constUnitsMap()const { return unitMap; }

    const Tile* getTile(const UVec2& position)const;
    bool setTile(const UVec2& position, const std::string& tileName);

    Unit* getUnit(const UVec2& position);
    const Unit* getUnit(const UVec2& position)const;
    bool setUnit(const UVec2& position, const std::string& unitName, unsigned int faction);

    bool testTile(const UVec2& position, const Tile* pTile)const;
    bool testUnit(const UVec2& position, const UnitTemplate* pUnitTemplate)const;

    bool move(const UVec2& origPosition, const UVec2& destPosition);

    void enableUnits(void);

    unsigned int getWidth(void)const { return width; }
    unsigned int getHeight(void)const { return height; }

    const Theme* getTheme(void)const { return pTheme; }

    bool isValidPosition(const UVec2& position)const;

    friend class MapLoader;
    friend class MapFactory;
};

/*! \class Map Map.h "Game/GameState/GameObjects/Map/Map.h"
 *  \brief Map data management class
 */

/*! \fn Map::Map(const Theme* const pTheme)
 *  \param pTheme a pointer to the Theme to use
 */

/*! \fn virtual Map::~Map(void)
 */

/*! \fn const std::vector < std::vector < const Tile* > >& Map :: constTilesMap()const
 *  \brief Get the tiles arrays of the Map
 *  \return the tiles of the Map (as constant data)
 */

/*! \fn const std::vector < std::vector < Unit > >& Map :: constUnitsMap()const
 *  \brief Get the units arrays of the Map
 *  \return the units of the Map (as constant data)
 */

/*! \fn const Tile* Map :: getTile(const UVec2& position)const
 *  \brief Get the tile at this position
 *  \param position the position where to get the tile
 *  \return a pointer to the Tile at this position
 */

/*! \fn bool Map :: setTile(const UVec2& position, const std::string& tileName);
 *  \brief Set a tile in the map
 *  The unit is described by an internal name
 *  \param position the position where to put the unit
 *  \param tileName the name in the theme of the tile to put
 *  \return true if all goes right
 */

/*! \fn Unit* Map :: getUnit(const UVec2& position);
 *  \brief Get the unit at this position
 *  \param position the position where to get the unit
 *  \return a pointer to the Unit at this position
 */

/*! \fn bool Map :: setUnit(const UVec2& position, const std::string& unitName, unsigned int faction);
 *  \brief Set a unit in the map
 *  The unit is described by an internal name and his faction
 *  \param position the position where to put the unit
 *  \param unitName the name in the theme of the unit to put
 *  \param faction the faction of the unit
 *  \return true if all goes right
 */

/*! \fn bool Map::testTile(const UVec2& position, const Tile* pTile)const
 * \brief Test if this unit type can be put at the position
 * \param position the position where the tile would be put
 * \param pTile a pointer to the Tile that the user wants to put
 * \return true if we can set the tile
 */

/*! \fn bool Map::testUnit(const UVec2& position, const UnitTemplate* pUnitTemplate)const
 * \brief Test if this unit type can be put at the position
 * \param position the position where the tile would be put
 * \param pUnitTemplate a pointer to the Unit that the user wants to put
 * \return true if we can set the unit
 */

/*! \fn bool Map::move(const UVec2& origPosition, const UVec2& destPosition)
 *  \brief Move a unit on the map
 *  \param origPosition the position where the unit actually is
 *  \param destPosition the position where to put the unit
 *  \return true if the movement is correct
 */

/*! \fn void Map::enableUnits(void)
 *  \brief enable all the units present on the map
 */

/*! \fn unsigned int Map::getWidth(void)const
 * \brief Return the width of the map
 * \return width of the map
 */

/*! \fn unsigned int Map::getHeight(void)const
 * \brief Return the height of the map
 * \return height of the map
 */

/*! \fn const Theme* Map::getTheme(void)const
 *  \brief Get the Theme used by the Map
 *  \return a pointer to the Theme
 */

/*! \fn bool Map::isValidPosition(const UVec2& position)const
 *  \brief Checks if the position is valid for this map
 *  \param position the position to check
 *  \return true if the position is valid (refering to a case)
 */

#endif
