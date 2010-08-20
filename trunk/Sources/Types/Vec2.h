#ifndef __VEC2_H__
#define __VEC2_H__

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

#include <iostream>

template <typename T>
struct Vec2
{
	T x;
	T y;

	Vec2(void):x(0),y(0) {}
	Vec2(const T& x, const T& y):x(x),y(y) {}
};

template <typename T>
std::ostream& operator<< (std::ostream& o, const Vec2<T> v)
{
	o << "Vec2(" << v.x << ";" << v.y << ")";

	return o;
}

typedef Vec2<int> IVec2;

#endif