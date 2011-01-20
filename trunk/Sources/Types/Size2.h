#ifndef __SIZE2_H__
#define __SIZE2_H__

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

#include <iostream>

template <typename T>
struct Size2
{
	T width;			/*!< The value for the width */
	T height;			/*!< The value for the height */

	Size2(void):width(0),height(0) {}

	//! Basic constructor
	/*!
		\param width the value for the width
		\param height the value for the height
	*/
	Size2(const T& width, const T& height):width(width),height(height) {}
    
    bool operator==(const Size2<T>& s)const
    {
        if ( s.width == this->width && s.height == this->height )
        {
            return true;
        }
        
        return false;
    }
};

template <typename T>
std::ostream& operator<< (std::ostream& o, const Size2<T>& s)
{
	o << "Size2(" << s.width << ";" << s.height << ")";

	return o;
}

template <typename T>
bool operator< (const Size2<T>& s1, const Size2<T>& s2)
{
    if ( s1.width < s2.width && s1.height < s2.height )
    {
        return true;
    }
    
    return false;
}

typedef Size2<int> ISize2;
typedef Size2<unsigned int> USize2;

/*! \struct Size2 Size2.h "Types/Size2.h"
 *  \brief 2D Size structure
 *
 *  2D size containing two fileds (width and height).
 */

/*! \fn bool Size2::operator==(const Size2<T>& s)const
 * \brief equality operator
 * \param s the second size to compare against
 */

/*! \fn std::ostream& operator<< (std::ostream& o, const Size2<T>& s)
	\param o the stream where to send the output
	\param s the size to send
	\return the stream (to loop)
*/

#endif
