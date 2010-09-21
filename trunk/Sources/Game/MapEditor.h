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

class MapEditor : public Map
{
private:

	std::string m_theme;			/*!< Graphical theme for the map */

	
	//! Check the cohenrency of the tile around the position
	/*!
	  \param position the position of the tile where to look around ( 8 direction around )
    */
	void checkCoherencyAround(const UVec2& position);

	//! Check the cohenrency of the tile at this position
	/*!
	  The function is looking at the type of the tile to know the correct function to call
	  \param position the position of the tile to check
    */
	void checkCoherency(const UVec2& position);

	//! Check the cohenrency of the tile at position (the tile is a road)
	/*!
	  Check the four tiles around the actual one, to put the correct road for the best graphical cohenrency.
	  \param position the position of the tile where to check
    */
	void checkCoherencyForRoad(const UVec2& position);

	//! Check the cohenrency of the tile at position (the tile is a see)
	/*!
	  Check the height tiles around the actual one, to put the correct see for the best graphical cohenrency.
	  \param position the position of the tile where to check
    */
	void checkCoherencyForSee(const UVec2& position);

	//! Check the cohenrency of the tile at position (the tile is a river)
	/*!
	  Check the height tiles around the actual one, to put the correct see for the best graphical cohenrency.
	  \param position the position of the tile where to check
    */
	void checkCoherencyForRiver(const UVec2& position);

	//! Set a plain at position and call the cohenrency check
	/*!
	  \param position the position of the tile to change for a plain one
    */
	bool setPlain(const UVec2& position);

	//! Set a tree at position and call the cohenrency check
	/*!
	  \param position the position of the tile to change for a tree one
    */
	bool setTree(const UVec2& position);

	//! Set a mountain at position and call the cohenrency check
	/*!
	  \param position the position of the tile to change for a mountain one
    */
	bool setMountain(const UVec2& position);

	//! Set a road at position and call the cohenrency check
	/*!
	  \param position the position of the tile to change for a road one
    */
	bool setRoad(const UVec2& position);

	//! Set a see at position and call the cohenrency check
	/*!
	  \param position the position of the tile to change for a see one
    */
	bool setSee(const UVec2& position);

	//! Set a river at position and call the cohenrency check
	/*!
	  \param position the position of the tile to change for a river one
    */
	bool setRiver(const UVec2& position);

public:
	//! Basic constructor
	/*!
      Create an empty map, with only T_Plain
	  \param sm the sprite manager to load the sprites used by the map
	  \param size the size of the map wanted
    */
	MapEditor(SpriteManager& sm, const UVec2& size);

	//! Set the Tile at the position
	/*!
		Will overwrite the Tile previously contained on the map by the new one.
		The new Tile is selected following the internal logic of the editor, to set the best tile type for this case, by checking around.
		\param position the position where to change the tile
		\param tileType the type of the new tile
		\return true if all goes right
	*/
	bool setTile(const UVec2& position, const TileType tileType);

	//! Test if this type tile can be put at the position
	/*!
	  \param position the position where the tile would be put
	  \param tileType the type of the tile that the user wants to put
	*/
	bool testTile(const UVec2& position, const TileType tileType)const;

	//! Save the Map in a file
	/*!
		\param fileName the file name where to save the file
		\return true if all goes right
	*/
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

#endif

#endif