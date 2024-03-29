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

#include "NEngine/NEngine.h"

#include "NEngine/Logging/Filter/NoFilter.hpp"
#include "NEngine/Logging/Formater/ColourFormater.hpp"
#include "NEngine/Logging/Writer/ConsoleWriter.hpp"

#include "NEngine/SpriteLoader.h"
#include "NEngine/SoundLoader.h"
#include "NEngine/InputManager.h"

NE::Logger<NE::LoggerFilter,NE::LoggerFormater,NE::LoggerWriter>* NE::NEngine::m_pLogger = NULL;

bool NE :: NEngine :: init(void)
{
	bool bError = true;

	// Start the logger
	if ( m_pLogger == NULL ) // We check if the user set his own logger
	{
		// if no logger, let's add our own
		m_pLogger = reinterpret_cast<NE::Logger<NE::LoggerFilter,NE::LoggerFormater,NE::LoggerWriter>*>(new NE::Logger<NE::NoFilter,NE::ColourFormater,NE::ConsoleWriter>());
	}

    pSpriteLoader = new SpriteLoader();
    if ( pSpriteLoader == NULL )
    {
        NEError << "Fail to allocate the SpriteLoader\n";
        bError = false;
    }

    pSoundLoader = new SoundLoader();
    if ( pSoundLoader == NULL )
    {
        NEError << "Fail to allocate the SoundLoader\n";
        bError = false;
    }

	pInputManager = new InputManager();
    if ( pInputManager == NULL )
    {
        NEError << "Fail to allocate the InputManager\n";
        bError = false;
    }
    else
    {
        bError &= this->initAPI();
    }

	return bError;
}

bool NE :: NEngine :: stop(void)
{
	bool bError = true;

	bError &= this->stopAPI();

	delete pInputManager;

	return bError;
}

void NE::NEngine::setLogger(NE::Logger<NE::LoggerFilter,NE::LoggerFormater,NE::LoggerWriter>* pNewLogger)
{
	if ( m_pLogger != NULL )
	{
		delete m_pLogger;
	}
	m_pLogger = pNewLogger;
}
