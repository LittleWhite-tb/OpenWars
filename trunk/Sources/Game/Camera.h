#ifndef __CAMERA_H__
#define __CAMERA_H__

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

#include "../Types/Vec2.h"

class Map;
class Cursor;

class Camera
{
private:
	UVec2 position;						/*!< Position of the camera */


	//! Move on the left
	/*!
    */
	void moveLeft();
	//! Move up
	/*!
    */
	void moveUp();
	//! Move on the right
	/*!
	  \param map the Map to check to know if we can move
    */
	void moveRight(const Map& map);
	//! Move down
	/*!
	  \param map the Map to check to know if we can move
    */
	void moveDown(const Map& map);

public:
	//! Basic constructor
	/*!
    */
	Camera(void);
	//! Basic destructor
	/*!
    */
	~Camera(void);

	//! Update the camera
	/*!
      If needed (depending of the position of the Cursor on the screen), the camera will be moved.
	  \param c the cursor to check
	  \param map the map on which one the camera look at
    */
	void update(const Cursor& c, const Map& map);

	//! Get the position
	/*!
      \return The position of the camera
    */
	UVec2 getPosition(void)const { return position; }
};

/*! \class Camera Camera.h "Game/Camera.h"
 *  \brief Manage the camera
 *
 * The camera will create an offset for the cursor, be moved by the cursor, and create offset for the Map drawing
 */


#endif