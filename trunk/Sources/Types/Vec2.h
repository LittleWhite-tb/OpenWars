#ifndef __VEC2_H__
#define __VEC2_H__

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

#include <iostream>

template <typename T>
struct Vec2
{
	T x;				/*!< The value on the x axis */
	T y;				/*!< The value on the y axis */

	Vec2(void):x(0),y(0) {}

	//! Basic constructor
	/*!
		\param x the value on the x axis
		\param y the value on the y axis
	*/
	Vec2(const T& x, const T& y):x(x),y(y) {}
    
    bool operator==(const Vec2<T>& v)const
    {
        if ( v.x == this->x && v.y == this->y )
        {
            return true;
        }
        
        return false;
    }
};

template <typename T>
std::ostream& operator<< (std::ostream& o, const Vec2<T>& v)
{
	o << "Vec2(" << v.x << ";" << v.y << ")";

	return o;
}

typedef Vec2<int> IVec2;
typedef Vec2<unsigned int> UVec2;

/*! \struct Vec2 Vec2.h "Types/Vec2.h"
 *  \brief 2D Vector structure
 *
 *  2D vector containing two fileds (x and y).
 */

/*! \fn bool Vec2::operator==(const Vec2<T>& v)const
 * \brief equality operator
 * \param v the second vector to compare against
 */

/*! \fn std::ostream& operator<< (std::ostream& o, const Vec2<T>& v)
	\param o the stream where to send the output
	\param v the vector to send
	\return the stream (to loop)
*/

#endif
