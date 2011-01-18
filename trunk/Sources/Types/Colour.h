#ifndef __COLOUR_H__
#define __COLOUR_H__

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

struct Colour
{
	unsigned char r;		/*!< Red componant */
	unsigned char g;		/*!< Green componant */
	unsigned char b;		/*!< Blue componant */
	unsigned char a;		/*!< Alpha componant */

	Colour():r(255),g(255),b(255),a(255) {}
	Colour(const unsigned char r, const unsigned char g, const unsigned char b, const unsigned char a=255):r(r),g(g),b(b),a(a) {}
	Colour(const unsigned int rgba) { setRGBA(rgba); }

	void setRGBA(const unsigned int rgba)
	{
		this->r = (rgba >> 24) & 0x000000FF;
		this->g = (rgba >> 16) & 0x000000FF;
		this->b = (rgba >> 8) & 0x000000FF;
		this->a = rgba & 0x000000FF;
	}
};

std::ostream& operator<< (std::ostream& o, const Colour& c);
bool operator< (const Colour& c1, const Colour& c2);

/*! \struct Colour Colour.h Types/Colour.h
 * \brief Colour container
 *
 * Contain a color in 32bit representation (8R ; 8G ; 8B ; 8A)
 */

/*! \fn Colour::Colour()
 * \brief Create a white colour
 */

/*! \fn Colour::Colour(const unsigned char r, const unsigned char g, const unsigned char b, const unsigned char a)
 * \brief Create the colour from parameters
 * \param r the red component
 * \param g the green component
 * \param b the blue component
 * \param a the alpha component
 */

/*! \fn Colour::Colour(const unsigned int rgba)
 * \brief Create the colour from a 32bit representation (RGBA)
 * \param rgba the colour
 */

/*! \fn void Colour::setRGBA(const unsigned int rgba)
 * \brief Set the colour to rgba
 */

/*! \fn std::ostream& operator<< (std::ostream& o, const Colour& c)
	\param o the stream where to send the output
	\param c the colour to send
	\return the stream (to loop)
*/

#endif
