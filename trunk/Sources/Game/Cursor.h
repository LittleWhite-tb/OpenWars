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

#include "../Engine/Controls/Keyboard.h"
#include "../Types/Vec2.h"

class Map;
class Camera;
struct Tile;
class Renderer;
class SpriteManager;
class AnimatedSprite;

class Cursor
{
private:
	const Map* const pMap;					/*!< Map to look at */

	AnimatedSprite* pCursorSprite;			/*!< Sprite for the cursor */

	UVec2 position;							/*!< Position of the cursor */

	// We disallow the copy
	Cursor(const Cursor& c);
	Cursor& operator= (const Cursor& c);

public:
	//! Constructor
	/*!
      Load the sprite to use for the Cursor and place the cursor to a initial position.
	  \param sm The SpriteManager to use to load the sprite for the cursor
	  \param fileName The name of the file to load
	  \param pMap A pointer on the Map to use
	  \param initialPosition The initial position of the cursor
    */
	Cursor(SpriteManager& sm, const std::string& fileName, const Map* const pMap, const UVec2& initialPosition);

	//! Basic destructor
	/*!
      Will just release the AnimatedSprite used by the cursor
    */
	~Cursor(void);

	//! Get the tile under the cursor
	/*!
      \return the Tile of the Map located under the cursor
    */
	Tile getTileUnderCursor(void)const;

	//! Get the actual position of the cursor
	/*!
      \return The position
    */
	UVec2 getPosition()const { return position; }

	//! Move to the next position
	/*!
      Will move to the next position ( step of 1 ) depending on the direction
	  \param ad The direction where to move
	  \return true if the displacement was possible
    */
	bool move(const ArrowsDirection ad);

	//! Move to a new position
	/*!
      Will move the cursor to a new position
	  \param newPosition The position where to move the cursor
	  \return true if the displacement was possible
    */
	bool move(const UVec2& newPosition);

	//! Draw the cursor
	/*!
	  \param r The Renderer to use to draw the cursor
	  \param c The Camera (used to draw the cursor at the correct place on the screen)
	  \param time The actual time
	  \return true if all goes right
    */
	bool draw(const Renderer& r, const Camera& c, const unsigned int time)const;
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

#endif