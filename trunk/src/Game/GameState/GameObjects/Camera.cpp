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

#include "Game/GameState/GameObjects/Map/Map.h"
#include "Game/GameState/GameObjects/Camera.h"
#include "Game/GameState/GameObjects/Cursor.h"

#include "NEngine/NEngine.h"
#include "NEngine/Types/Vec2.h"

#include "globals.h"

Camera :: Camera(void)
    :position(UVec2(0,0))
{
    NEDebug << "Camera created\n";
}

Camera :: ~Camera(void)
{
    NEDebug << "Camera deleted\n";
}

void Camera :: moveLeft()
{
    if ( position.x > 0 )
        position.x--;
}

void Camera :: moveUp()
{
    if ( position.y > 0 )
        position.y--;
}

void Camera :: moveRight(const Map& map)
{
    if ( position.x < map.getWidth() - MAP_MIN_WIDTH )
        position.x++;
}

void Camera :: moveDown(const Map& map)
{
    if ( position.y < map.getHeight() - MAP_MIN_HEIGHT)
        position.y++;
}

void Camera :: update(const Cursor& c, const Map& map)
{
#ifdef VERBOSE
    LDebug << "Camera :: update (Was: " << position << ")";
#endif

    UVec2 cursorPosition = c.getPosition();

    // We have to apply the camera to avoid infinite recursion of the displacement, when reaching the bound
    if ( cursorPosition.x - this->position.x < BOUND_CAMERA_DISPLACEMENT )
    {
        moveLeft();
    }

    if ( cursorPosition.x - this->position.x > MAP_MIN_WIDTH - BOUND_CAMERA_DISPLACEMENT )
    {
        moveRight(map);
    }

    if ( cursorPosition.y - this->position.y < BOUND_CAMERA_DISPLACEMENT )
    {
        moveUp();
    }

    if ( cursorPosition.y - this->position.y > MAP_MIN_HEIGHT - BOUND_CAMERA_DISPLACEMENT )
    {
        moveDown(map);
    }

#ifdef VERBOSE
    LDebug << "Camera :: update (New position: " << position << ")";
#endif
}
