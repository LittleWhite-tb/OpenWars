#ifndef __NE_SOUNDLOADER_H__
#define __NE_SOUNDLOADER_H__

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

#include <string>
#include <map>
#include <list>

#include "NEngine/Loader.h"
#include "NEngine/ISoundLoader.h"
#include "NEngine/Sound.h"

#include "Bank.h"

namespace NE
{
	class SoundLoader : public Loader<NE::ISoundLoader>
	{
	protected:

		Bank<Sound> m_bank;

	public:
		SoundLoader() {}

		Sound* loadSoundFromFile(const std::string& fileName);
	};
}

/*! \class NE::SoundLoader SoundLoader.h "NEngine/SoundLoader.h"
 *  \brief SoundLoader interface
 *
 * The SoundLoader class gives an interface to implement new platform specific Sound loading functions.
 */

/*! \fn virtual Sound* NE::SoundLoader::loadSound(const std::string& fileName)=0;
 * \brief load the sound (internal function)
 * \param fileName the name of the file to load
 * \return pointer on the new Sound or NULL if loading failed (possible causes: missing files / invalid file format)
 */

/*! \fn NE::SoundLoader::SoundLoader(MemoryManager* const pMemoryManager)
 * \param pMemoryManager pointer on the memory manager to use
 */

/*! \fn NE::SoundLoader::~SoundLoader(void)
 */

/*! \fn virtual Sound* NE::SoundLoader::loadSoundFromFile(const std::string& fileName)=0
 * \brief load a Sound from a file
 * \param fileName the name of the file to load
 * \return a pointer to the newly loaded Sound
*/


#endif
