#ifndef __CURSOR_H__
#define __CURSOR_H__

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

#include "../NEngine/InputManager.h"

#include "../Game/Tile.h"
#include "../Types/Vec2.h"

class Map;
class Camera;
struct Tile;

namespace NE { class SpriteLoader; }
class AnimatedSprite;

class Cursor
{
private:
	const Map* const pMap;					/*!< Map to look at */

	// We disallow the copy
	Cursor(const Cursor& c);
	Cursor& operator= (const Cursor& c);

protected:
	AnimatedSprite* pCursorSprite;			/*!< Sprite for the cursor */

	UVec2 position;							/*!< Position of the cursor */

public:

	Cursor(NE::SpriteLoader* const pSL, const std::string& fileName, const Map* const pMap, const UVec2& initialPosition);
	virtual ~Cursor(void);

	Tile getTileUnderCursor(void)const;
	TileType getTileTypeUnderCursor(void)const;

	UVec2 getPosition()const { return position; }

	bool move(const NE::InputManager::ArrowsDirection ad);
	bool move(const UVec2& newPosition);

	virtual bool draw(const NE::Renderer& r, const Camera& c, const unsigned int time)const;
};

/*! \class Cursor Cursor.h "Game/Cursor.h"
 *  \brief Manage the cursor on the Map
 *
 * The cursor is a sprite, not related to the mouse, to allow the user to select unit or to move the Camera
 * It can do the following:
 * - Get the actual position
 * - Get the Tile under the cursor
 * - Move
 * - Draw
 */

/*! \fn Cursor::Cursor(NE::SpriteLoader* const pSL, const std::string& fileName, const Map* const pMap, const UVec2& initialPosition)
 * Load the sprite to use for the Cursor and place the cursor to a initial position.
 * \param pSL The SpriteLoader to use to load the sprite for the cursor
 * \param fileName The name of the file to load
 * \param pMap A pointer on the Map to use
 * \param initialPosition The initial position of the cursor
 */

/*! \fn virtual Cursor::~Cursor(void)
 */

/*! \fn Tile Cursor::getTileUnderCursor(void)const
 * \brief Get the tile under the cursor
 * \return the Tile of the Map located under the cursor
 */

/*! \fn TileType Cursor::getTileTypeUnderCursor(void)const
 * \brief Get the tile type under the cursor
 * \return the TileType of the Map located under the cursor
 */

/*! \fn UVec2 Cursor::getPosition()const
 * \brief Get the actual position of the cursor
 * \return The position
 */

/*! \fn bool Cursor::move(const NE::InputManager::ArrowsDirection ad)
 * \brief Move to the next position
 * Will move to the next position ( step of 1 ) depending on the direction
 * \param ad The direction where to move
 * \return true if the displacement was possible
 */

/*! \fn bool Cursor::move(const UVec2& newPosition)
 * \brief Move to a new position
 * Will move the cursor to a new position
 * \param newPosition The position where to move the cursor
 * \return true if the displacement was possible
 */

/*! \fn virtual bool Cursor::draw(const NE::Renderer& r, const Camera& c, const unsigned int time)const
 * \brief Draw the cursor
 * \param r the NE::Renderer to use to draw the Cursor
 * \param c The Camera (used to draw the cursor at the correct place on the screen)
 * \param time The actual time
 * \return true if all goes right
 */

#endif
