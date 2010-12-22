#ifndef __MAP_H__
#define __MAP_H__

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

#include <string>
#include <map>

#include "Tile.h"
#include "Unit.h"

#include "../Types/Vec2.h"

class Renderer;
class Camera;
class SpriteManager;
class AnimatedSprite;

class Map
{
protected:

	std::map<TileType, Tile>tilesSet;						/*!< Set of tile to use with this map */
	std::map<UnitType, UnitTemplate>unitsSet;					/*!< Set of tile to use with this map */

	unsigned int width;			/*!< Width (in tile) of the map */
	unsigned int height;		/*!< Height (in tile) of the map */

	std::string m_themeName;	/*!< Name of the theme to use */

	TileType** map;					/*!< 2D Array representating the map */
	UnitType** unitViewMap;				/*!< 2D Array representating the unit on the map */

	bool valid;					/*!< if the map is loaded properly */

	Map(void) {};

	bool loadTileSet(SpriteManager& sm);
	bool loadUnitSet(SpriteManager& sm);
	bool loadGraphics(SpriteManager& sm);

	bool parser(SpriteManager& sm, const std::string& fileName);

	bool drawTerrain(const Camera& c, const unsigned int time);

public:
	Map(SpriteManager& sm, const std::string& fileName);
	virtual ~Map(void);

	virtual bool draw(const Camera& c, const unsigned int time)=0;

	virtual bool setTile(const UVec2& position, const UnitType unitType)=0;
    
	bool isValidMap(void)const { return valid; }

	unsigned int getWidth(void)const { return width; }
	unsigned int getHeight(void)const { return height; }

	Tile getTile(const UVec2& position)const;
	Tile getTile(const TileType& tt)const;

	TileType getTileType(const UVec2& position)const;
	UnitType getUnitType(const UVec2& position)const;

	UnitTemplate getUnitTemplate(const UVec2& position)const;
	UnitTemplate getUnitTemplate(const UnitType ut)const;

	AnimatedSprite* getAssociatedSprite(const TileType type);
	AnimatedSprite* getAssociatedSprite(const UnitType type);
    
	bool testTile(const UVec2& position, const UnitType unitType)const;
};

/*! \class Map Map.h "Game/Map.h"
 *  \brief Map management class
 *
 * Manage the Map for the game.
 * Can do the following:
 *		- Load from file (directly in the constructor, the parsing is done manualy)
 *		- Draw the map
 *		- Get a Tile
 */

/*! \fn bool Map::loadTileSet(SpriteManager& sm)
 * \brief Load the tiles that the map will use
 * Will use a tile set file to know the settings of each tiles
 * \param sm the SpriteManager to load the sprites.
 * \return true if all goes right
 */

/*! \fn bool Map::loadUnitSet(SpriteManager& sm)
 * \brief Load the units that the map will use
 * Will use a unit set file to know the settings of each units
 * \param sm the SpriteManager to load the sprites.
 * \return true if all goes right
 */

/*! \fn bool Map::loadGraphics(SpriteManager& sm)
 * \brief Load the tiles that the map will use
 * Will load all the tiles available for the theme passed by parameter in a std::map in view to associate the TileType to an AnimatedSprite pointer.
 * \param sm the SpriteManager to load the sprites.
 * \return true if all goes right
 */

/*! \fn bool Map::parser(SpriteManager& sm, const std::string& fileName)
 * \brief Map file parser
 * Will parse the information contained in the map. When possible, will check if the information are correct
 * \param sm the sprite manager to load the sprites used by the map
 * \param fileName the name of the file to load
 * \return true if all goes right
 */

/*! \fn bool Map::drawTerrain(const Camera& c, const unsigned int time)
 * \brief Draw the terrain map
 * \param c The Camera (used to draw the correct part of the Map)
 * \param time the actual time (for animation)
 * \return true if all goes right
 */

/*! \fn Map::Map(SpriteManager& sm, const std::string& fileName)
 * Will call the parser
 * If you need to check if the map is correct (and you should), please use isValidMap()
 * \param sm the sprite manager to load the sprites used by the map
 * \param fileName the name of the file to load
 */

/*! \fn virtual Map::~Map(void)
 */

/*! \fn virtual bool Map::draw(const Camera& c, const unsigned int time)=0
 * \brief Draw the map
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
