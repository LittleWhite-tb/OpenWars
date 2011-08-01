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

#include "Game/Tile.h"
#include "Game/Unit.h"

#include "Types/Size2.h"
#include "Types/Vec2.h"

#include "Engine/Theme.h"
#include "Engine/Library.h"

namespace NE { class Renderer; }
namespace NE { class SpriteLoader; }

class Camera;
class AnimatedSprite;
class MapIntegrityChecker;

class Map
{
private:
    MapIntegrityChecker* pIntegrityChecker;

    void checkCoherency(const UVec2& position, const Tile* pTileToPut);

    bool allocateMemory(const USize2& size);

    std::vector < std::vector < const Tile* > >* getTilesMap() { return &tileMap; }
    std::vector < std::vector < Unit > >* getUnitsMap() { return &unitMap; }

protected:

    const Theme* pTheme;

    unsigned int width;         /*!< Width (in tile) of the map */
    unsigned int height;        /*!< Height (in tile) of the map */

    std::vector < std::vector < const Tile* > > tileMap;    /*!< 2D Array representating the map */
    std::vector < std::vector < Unit > > unitMap;   /*!< 2D Array representating the unit on the map */

    bool drawTerrain(const NE::Renderer& r, const Camera& c, const unsigned int time);

public:
    Map(const Theme* const pTheme);
    virtual ~Map(void);

    const std::vector < std::vector < const Tile* > >* constTilesMap()const { return &tileMap; }
    const std::vector < std::vector < Unit > >* constUnitsMap()const { return &unitMap; }

    bool draw(const NE::Renderer& r, const Camera& c, const unsigned int time);

    const Tile* getTile(const UVec2& position)const;
    bool setTile(const UVec2& position, const std::string& tileName);

    const Unit* getUnit(const UVec2& position);
    bool setUnit(const UVec2& position, const std::string& unitName, unsigned int faction);

    bool testTile(const UVec2& position, const Tile* pTile);
    bool testUnit(const UVec2& position, const UnitTemplate* pUnitTemplate);

    bool move(const UVec2& origPosition, const UVec2& destPosition);

    void enableUnits(void);

    unsigned int getWidth(void)const { return width; }
    unsigned int getHeight(void)const { return height; }

    const Theme* getTheme(void)const { return pTheme; }

    bool isValidPosition(const UVec2& position)const;

    friend class MapLoader;
    friend class MapFactory;

/*
    template <typename T>
    const T& get(const UVec2& position)const
    {
        if ( position.x < this->width && position.y < this->height )
        {
            // The [] operator is not const...
            return pTileMap[position.y][position.x];
        }
        else
        {
            return Tile();
        }
    }
*/

/*
    TileType getTileType(const UVec2& position)const;
    UnitType getUnitType(const UVec2& position)const;

    UnitTemplate getUnitTemplate(const UVec2& position)const;
    UnitTemplate getUnitTemplate(const UnitType ut)const;

    AnimatedSprite* getAssociatedSprite(const TileType type);
    AnimatedSprite* getAssociatedSprite(const UnitType type);

    bool testTile(const UVec2& position, const UnitType unitType)const;
*/
};

/*! \class Map Map.h "Game/Map.h"
 *  \brief Map data management class
 */

/*! \fn bool Map::loadTileSet(NE::SpriteLoader* const pSL)
 * \brief Load the tiles that the map will use
 * Will use a tile set file to know the settings of each tiles
 * \param pSL the SpriteLoader to load the sprites.
 * \return true if all goes right
 */

/*! \fn bool Map::loadUnitSet(NE::SpriteLoader* const pSL)
 * \brief Load the units that the map will use
 * Will use a unit set file to know the settings of each units
 * \param pSL the SpriteLoader to load the sprites.
 * \return true if all goes right
 */

/*! \fn bool Map::loadGraphics(NE::SpriteLoader* const pSL)
 * \brief Load the tiles that the map will use
 * Will load all the tiles available for the theme passed by parameter in a std::map in view to associate the TileType to an AnimatedSprite pointer.
 * \param pSL the SpriteLoader to load the sprites.
 * \return true if all goes right
 */

/*! \fn bool Map::parser(NE::SpriteLoader* const pSL, const std::string& fileName)
 * \brief Map file parser
 * Will parse the information contained in the map. When possible, will check if the information are correct
 * \param pSL the SpriteLoader to load the sprites used by the map
 * \param fileName the name of the file to load
 * \return true if all goes right
 */

/*! \fn bool Map::drawTerrain(const NE::Renderer& r, const Camera& c, const unsigned int time)
 * \brief Draw the terrain map
 * \param r the NE::Renderer to use to draw the Map
 * \param c The Camera (used to draw the correct part of the Map)
 * \param time the actual time (for animation)
 * \return true if all goes right
 */

/*! \fn Map::Map(NE::SpriteLoader* const pSL, const std::string& fileName)
 * Will call the parser
 * If you need to check if the map is correct (and you should), please use isValidMap()
 * \param pSL the SpriteLoader to load the sprites used by the map
 * \param fileName the name of the file to load
 */

/*! \fn virtual Map::~Map(void)
 */

/*! \fn virtual bool Map::draw(const NE::Renderer& r, const Camera& c, const unsigned int time)=0
 * \brief Draw the map
 * \param r the NE::Renderer to use to draw the Map
 * \param c The Camera (used to draw the correct part of the Map)
 * \param time the actual time (for animation)
 * \return true if all goes right
 */

/*! \fn virtual bool Map::setTile(const UVec2& position, const UnitType unitType)=0
 * \brief Set the Unit at the position
 * Will overwrite the Unit previously contained on the map by the new one.
 * The new Unit is selected following the internal logic of the editor.
 * \param position the position where to change the tile
 * \param unitType the type of the new unit
 * \return true if all goes right
 */

/*! \fn bool Map::isValidMap(void)const
 * \brief Return if the map is valid
 * \return true if the map is valid
 */

/*! \fn unsigned int Map::getWidth(void)const
 * \brief Return the width of the map
 * \return width of the map
 */

/*! \fn unsigned int Map::getHeight(void)const
 * \brief Return the height of the map
 * \return height of the map
 */

/*! \fn TileType Map::getTileType(const UVec2& position)const
 * \brief Return the type corresponding to the position
 * The function will check if the position is outside the map. If it is, the Tile returned has for type TT_Invalid
 * \param position the position of the Tile to get
 * \return the TileType corresponding to the input position ... TT_Invalid if the position is not valid
 */

/*! \fn Tile Map::getTile(const UVec2& position)const
 * \brief Return the tile corresponding to the position
 * The function will check if the position is outside the map. If it is, the Tile returned has for type TT_Invalid
 * \param position the position of the Tile to get
 * \return the Tile corresponding to the input position
 */

/*! \fn Tile Map::getTile(const TileType& tt)const
 * \brief Return the tile corresponding to the TileType
 * \param tt the TileType
 * \return the Tile corresponding to the input TileType
 */

/*! \fn UnitType Map::getUnitType(const UVec2& position)const
 * \brief Return the UnitType corresponding to the position
 * The function will check if the position is outside the map. If it is, NULL is returned
 * \param position the position of the UnitType to get
 * \return the Unit corresponding to the input position or UT_NO_UNIT
 */

/*! \fn UnitTemplate Map::getUnitTemplate(const UVec2& position)const
 * \brief Return the UnitTemplate corresponding to the position
 * The function will check if the position is outside the map. If it is, NULL is returned
 * \param position the position of the Unit to get
 * \return the UnitTemplate corresponding to the input position or NULL
 */

/*! \fn UnitTemplate Map::getUnitTemplate(const UnitType ut)const
 * \brief Return the UnitTemplate corresponding to the UnitType
 * \param ut the UnitType of the Unit to return the position of the Unit to get
 * \return the UnitTemplate corresponding to the input UnitType
 */

/*! \fn AnimatedSprite* Map::getAssociatedSprite(const TileType type)
 * \brief Return the sprite corresponding to the type
 * If the type is not found in the map library, return NULL
 * \param type the type associated to the sprite to return
 * \return the AnimatedSprite pointer associated to the type
 */

/*! \fn AnimatedSprite* Map::getAssociatedSprite(const UnitType type)
 * \brief Return the sprite corresponding to the type
 * If the type is not found in the map library, return NULL
 * \param type the type associated to the sprite to return
 * \return the AnimatedSprite pointer associated to the type
 */

/*! \fn bool Map::testTile(const UVec2& position, const UnitType unitType)const
 * \brief Test if this unit type can be put at the position
 * \param position the position where the tile would be put
 * \param unitType the type of the unit that the user wants to put
 * \return true if we can set the unit
 */

#endif
