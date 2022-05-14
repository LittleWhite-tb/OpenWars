#ifndef __NE_TIME_H__
#define __NE_TIME_H__

#ifndef DOXYGEN_IGNORE_TAG
/**
NEngine: Native Engine abstracts multimedia libraries such as SDL, SFML, Allegro
Copyright (C) 2010-2015  Alexandre LAURENT

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

website: https://github.com/LittleWhite-tb/NEngine
e-mail: lw.demoscene@gmail.com
**/
#endif

namespace NE
{
	class Time
	{
	public:
		Time(void) {}
		virtual ~Time(void) {}

		virtual unsigned int getTime(void)=0;
		virtual void delay(unsigned int msSec)=0;
	};
}

/*! \class NE::Time Time.h "NEngine/Time.h"
 *  \brief Time interface
 *
 * The Time class gives an interface to implement new platform specific time related functions in the game.
 * Only the two simplest functions are implemented. One to get the time, the other one to wait (pause) the process an amount of time
 */

/*! \fn NE::Time::Time(void)
 */

/*! \fn virtual NE::Time::~Time(void)
 */

/*! \fn virtual unsigned int NE::Time::getTime(void)=0
 * \brief Get the actual time
 * Note: The value return can be from the start of the process or the exact actual time.
 * \return the value of the time.
 */

/*! \fn virtual void NE::Time::delay(unsigned int msSec)=0
 * \brief Pause the process for some milliseconds
 * \param msSec the amount of time to wait in milliseconds
*/

#endif
