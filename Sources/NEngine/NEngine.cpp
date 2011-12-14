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

#include "NEngine.h"

#include "SpriteLoader.h"
#include "InputManager.h"

NE::Logger<NE::NoFilter,NE::ColourFormater,NE::ConsoleWriter> NE::NEngine::m_logger;

bool NE :: NEngine :: init(void)
{
	bool bError = true;

    pSpriteLoader = new SpriteLoader();
    if ( pSpriteLoader == NULL )
    {
        NE::NEngine::logger().log(NE::LL_Error,"Fail to allocate the SpriteLoader");
        bError = false;
    }

	pInputManager = new InputManager();
    if ( pInputManager == NULL )
    {
        NE::NEngine::logger().log(NE::LL_Error,"Fail to allocate the InputManager");
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
