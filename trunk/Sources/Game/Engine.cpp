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

#include "Engine.h"

#include <cassert>

#include "../NEngine/NEngine.h"

#include "../Engine/ResourcesManager/FontManager.h"

#include "../Engine/VTime.h"

#include "../Engine/Controls/Keyboard.h"

#include "../Utils/Logger.h"

Engine::Engine(NE::NEngine* const pNE)
:pNE(pNE),pFM(NULL),pVT(NULL),pKB(NULL)
{
	assert(pNE);
}

Engine :: ~Engine(void)
{
	delete pKB;
	delete pVT;
	delete pFM;
}

bool Engine :: init()
{
	pFM = new FontManager();

	pVT = new VTime(60,10);
	pKB = new Keyboard();

	if ( pFM == NULL || pVT == NULL ||pKB == NULL )
	{
		// THe memory will be cleaned by the destructor
		return false;
	}

	LDebug << "EditorEngine init'd";

	return true;
}

