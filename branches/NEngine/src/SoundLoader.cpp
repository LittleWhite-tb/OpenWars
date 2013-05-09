#ifndef DOXYGEN_IGNORE_TAG
/**
OpenAWars is an open turn by turn strategic game aiming to recreate the feeling of advance (famicon) wars (c)
Copyright (C) 2010-2013  Alexandre LAURENT

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

#include "NEngine/SoundLoader.h"

#include <string>
#include <iostream>

#include "NEngine/NEngine.h"
#include "NEngine/Exceptions/FileNotFoundException.h"

#include "NEngine/Sound.h"

NE::Sound* NE :: SoundLoader :: loadSoundFromFile(const std::string& fileName)
{
    NE::Sound* pSound = m_bank.get(fileName);
    
    if ( pSound == NULL ) // It was not in the bank
    {
        for ( std::list<NE::ISoundLoader*>::const_iterator itLoader = m_loaders.begin() ; 
            itLoader != m_loaders.end() ;
            ++itLoader )
        {
            pSound = (*itLoader)->loadSoundFromFile(fileName);
            if ( pSound != NULL )  // It is loaded, we can stop
            {
                m_bank.add(fileName,pSound);
                break;
            }
        }

        // We gone through all loaders, and the sprite is not loaded ... so, error
        if ( pSound == NULL )
        {
            NEError << "Fail to load sound '" << fileName << "'\n";
            throw FileNotFoundException(fileName);
        }
    }
    
    return pSound;
}
