#ifndef __RECT_H__
#define __RECT_H__

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
#include "../Types/Size2.h"

struct Rect
{
	IVec2 position;		/*!< Position of the rectange */
	USize2 size;		/*!< Size of the rectangle */

	Rect(const IVec2& position, const USize2& size):position(position),size(size) {}
};

/*! \struct Rect Rect.h Types/Rect.h
 * \brief Rectangle container
 *
 * Contain a rectangle based on x, y position and width, height
 */

/*! \fn Rect::Rect(const IVec2& position, const USize2& size)
 * \param position the position of the rectangle
 * \param size the size of the rectangle
 */

#endif