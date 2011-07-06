#ifndef __CAMERA_H__
#define __CAMERA_H__

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

#include "../Types/Vec2.h"

class Map;
class Cursor;

class Camera
{
private:
	UVec2 position;						/*!< Position of the camera */

	void moveLeft();
	void moveUp();
	void moveRight(const Map& map);
	void moveDown(const Map& map);

public:
	Camera(void);
	~Camera(void);

	void update(const Cursor& c, const Map& map);

	UVec2 getPosition(void)const { return position; }
};

/*! \class Camera Camera.h "Game/Camera.h"
 *  \brief Manage the camera
 *
 * The camera will create an offset for the cursor, be moved by the cursor, and create offset for the Map drawing
 */

/*! \fn void Camera::moveLeft()
 * \brief Move on the left
 */

/*! \fn void Camera::moveUp()
 * \brief Move up
 */

/*! \fn void Camera::moveRight(const Map& map)
 * \brief Move on the right
 * \param map the Map to check to know if we can move
 */

/*! \fn void Camera::moveDown(const Map& map)
 * \brief Move down
 * \param map the Map to check to know if we can move
 */

/*! \fn Camera::Camera(void)
 */

/*! \fn Camera::~Camera(void)
 */

/*! \fn void Camera::update(const Cursor& c, const Map& map)
 * \brief Update the camera
 * If needed (depending of the position of the Cursor on the screen), the camera will be moved.
 * \param c the cursor to check
 * \param map the map on which one the camera look at
 */

/*! \fn UVec2 Camera::getPosition(void)const
 * \brief Get the position
 * \return The position of the camera
 */


#endif