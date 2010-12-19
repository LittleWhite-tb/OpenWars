#ifdef EDITOR
#ifndef __MAPEDITOR_H__
#define __MAPEDITOR_H__

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

#include "Map.h"

class Renderer;
class Camera;

class MapEditor : public Map
{
private:
	void checkCoherencyAround(const UVec2& position);
	void checkCoherency(const UVec2& position);
	void checkCoherencyForRoad(const UVec2& position);
	void checkCoherencyForSee(const UVec2& position);
	void checkCoherencyForRiver(const UVec2& position);

	bool setPlain(const UVec2& position);
	bool setTree(const UVec2& position);
	bool setMountain(const UVec2& position);
	bool setRoad(const UVec2& position);
	bool setSea(const UVec2& position);
	bool setReef(const UVec2& position);
	bool setBeach(const UVec2& position);
	bool setRiver(const UVec2& position);
	bool setBridge(const UVec2& position);
	bool setHQ(const UVec2& position, const TileType type);
	bool setBuilding(const UVec2& position, const TileType type);

public:
	MapEditor(SpriteManager& sm, const std::string& themeName, const UVec2& size);
	MapEditor(SpriteManager& sm, const std::string& fileName):Map(sm,fileName) {}

	bool draw(const Renderer& r, const Camera& c, const unsigned int time);

	bool testTile(const UVec2& position, const TileType tileType)const;

	bool setTile(const UVec2& position, const TileType tileType);
	bool setTile(const UVec2& position, const UnitType unitType);

	bool save(const std::string& fileName);
};

/*! \class MapEditor MapEditor.h "Game/MapEditor.h"
 *  \brief Add editoring functionnalities to the Map
 *
 * The following are added:
 *		- Creating an empty map with a specified size
 *		- Changing the Tile at runtime
 *		- Test if the tile can be set here (without changing anything at the map)
 *		- Saving in a file
 */

/*! \fn void MapEditor::checkCoherencyAround(const UVec2& position)
 * \brief Check the cohenrency of the tile around the position
 * \param position the position of the tile where to look around ( 8 direction around 
 */

/*! \fn void MapEditor::checkCoherency(const UVec2& position)
 * \brief Check the cohenrency of the tile at this position
 * The function is looking at the type of the tile to know the correct function to call
 * \param position the position of the tile to check
 */

/*! \fn void MapEditor::checkCoherencyForRoad(const UVec2& position)
 * \brief Check the cohenrency of the tile at position (the tile is a road)
 * Check the four tiles around the actual one, to put the correct road for the best graphical cohenrency.
 * \param position the position of the tile where to check
 */

/*! \fn void MapEditor::checkCoherencyForSee(const UVec2& position)
 * \brief Check the cohenrency of the tile at position (the tile is a see)
 * Check the height tiles around the actual one, to put the correct see for the best graphical cohenrency. If the tile under the actual one is a beach, will update as a beach.
 * \param position the position of the tile where to check
 */

/*! \fn void MapEditor::checkCoherencyForRiver(const UVec2& position)
 * \brief Check the cohenrency of the tile at position (the tile is a river)
 * Check the height tiles around the actual one, to put the correct see for the best graphical cohenrency.
 * \param position the position of the tile where to check
 */

/*! \fn bool MapEditor::setPlain(const UVec2& position)
 * \brief Set a plain at position and call the cohenrency check
 * \param position the position of the tile to change for a plain one
 */

/*! \fn bool MapEditor::setTree(const UVec2& position)
 * \brief Set a tree at position and call the cohenrency check
 * \param position the position of the tile to change for a tree one
 */

/*! \fn bool MapEditor::setMountain(const UVec2& position)
 * \brief Set a mountain at position and call the cohenrency check
 * \param position the position of the tile to change for a mountain one
 */

/*! \fn bool MapEditor::setRoad(const UVec2& position)
 * \brief Set a road at position and call the cohenrency check
 * \param position the position of the tile to change for a road one
 */

/*! \fn bool MapEditor::setSea(const UVec2& position)
 * \brief Set a sea at position and call the cohenrency check
 * \param position the position of the tile to change for a see one
 */

/*! \fn bool MapEditor::setReef(const UVec2& position)
 * \brief Set a reef at position
 * \param position the position of the tile to change for a reef one
 */

/*! \fn bool MapEditor::setBeach(const UVec2& position)
 * \brief Set a beach at position and call the cohenrency check
 * \param position the position of the tile to change for a beach one
 */

/*! \fn bool MapEditor::setRiver(const UVec2& position)
 * \brief Set a river at position and call the cohenrency check
 * \param position the position of the tile to change for a river one
 */

/*! \fn bool MapEditor::setBridge(const UVec2& position)
 * \brief Set a bridge at position and call the cohenrency check (but not needed for the actual position)
 * \param position the position of the tile to change for a bridge one
 */

/*! \fn bool MapEditor::setHQ(const UVec2& position, const TileType type)
 * \brief Set a HQ at position and call the cohenrency check
 * \param position the position of the tile to change for a HQ one
 * \param type the type of building (should be an HQ)
 */

/*! \fn bool MapEditor::setBuilding(const UVec2& position, const TileType type)
 * \brief Set a building at position and call the cohenrency check
 * \param position the position of the tile to change for a building one
 * \param type the type of building (if HQ, setHQ is called)
 */

/*! \fn MapEditor::MapEditor(SpriteManager& sm, const std::string& themeName, const UVec2& size)
 * \brief Create an empty map, with only T_Plain
 * \param sm the sprite manager to load the sprites used by the map
 * \param themeName the name of the theme to load
 * \param size the size of the map wanted
 */

/*! \fn MapEditor::MapEditor(SpriteManager& sm, const std::string& fileName)
 * \brief Load the map to edit it.
 * \param sm the sprite manager to load the sprites used by the map
 * \param fileName the name of the file to load
 */

/*! \fn bool MapEditor::draw(const Renderer& r, const Camera& c, const unsigned int time)
 */

/*! \fn bool MapEditor::setTile(const UVec2& position, const TileType tileType)
 * \brief Set the Tile at the position
 * Will overwrite the Tile previously contained on the map by the new one.
 * The new Tile is selected following the internal logic of the editor, to set the best tile type for this case, by checking around.
 * \param position the position where to change the tile
 * \param tileType the type of the new tile
 * \return true if all goes right
 */

/*! \fn bool MapEditor::testTile(const UVec2& position, const TileType tileType)const
 * \brief Test if this type tile can be put at the position
 * \param position the position where the tile would be put
 * \param tileType the type of the tile that the user wants to put
 * \return true if we can set the tile
 */

/*! \fn bool MapEditor::setTile(const UVec2& position, const UnitType unitType)
 * \brief Set the Unit at the position
 * Will overwrite the Unit previously contained on the map by the new one.
 * The new Unit is selected following the internal logic of the editor.
 * \param position the position where to change the tile
 * \param unitType the type of the new unit
 * \return true if all goes right
 */

/*! \fn bool MapEditor::save(const std::string& fileName)
 * \brief Save the Map in a file
 * \param fileName the file name where to save the file
 * \return true if all goes right
 */

#endif

#endif
