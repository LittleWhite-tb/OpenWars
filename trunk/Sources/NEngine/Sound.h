#ifndef __NE_SOUND_H__
#define __NE_SOUND_H__

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

namespace NE
{
	class Sound
	{
	public:
		Sound(void);
		virtual ~Sound(void);

		virtual void play(const bool loop=false)=0;
		virtual void stop(void)=0;
	};
}

/*! \class NE::Sound Sound.h "NEngine/Sound.h"
 *  \brief Sound interface
 *
 * The Sound class gives an interface to implement new platform specific Sound functions.
 */

/*! \fn NE::Sound::Sound(void)
 */

/* \fn virtual NE::Sound::~Sound(void)
 */

/*! \fn virtual void NE::Sound::play(const bool loop=false)=0
 * \brief play the Sound
 * \param loop true if the Sound must be looped
 */

/*! \fn virtual void NE::Sound::stop(void)=0
 * \brief stop the Sound
 * Do nothing if the Sound is not played
 */

#endif