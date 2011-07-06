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

#include "Engine.h"

#include <cassert>

#include "NEngine/NEngine.h"

#include "Engine/Theme.h"
#include "Engine/VTime.h"

#include "XML/XMLListReader.h"

#include "Utils/Logger.h"
#include "Utils/Exceptions/XMLException.h"

Engine::Engine(NE::NEngine* const pNE)
:pNE(pNE),pVT(NULL)
{
	assert(pNE);
}

Engine :: ~Engine(void)
{
	delete pVT;
}

bool Engine :: init()
{
	pVT = new VTime(pNE->getTime(),60,10);

	if ( pVT == NULL )
	{
		LError << "Fail to allocate memory for Virtual Time";
		return false;
	}

	LDebug << "Engine init'd";

	return true;
}

void Engine :: loadTheme(const std::string& themeName)
{
	Theme* pTheme = new Theme(themeName);
	if ( pTheme == NULL )
	{
		LError << "Fail to allocate Theme";
		throw std::bad_alloc("Fail to allocate Theme");
	}

	if ( pTheme->load(pNE->getSpriteLoader()) == false )
	{
		throw EngineException("Failed to load the theme (" + themeName+ ")");
	}
	else
	{
		themeLibrary.add(pTheme->getName(),pTheme);
	}
}

void Engine :: loadThemeList(const std::string& listPath)
{
	try
	{
		std::list<std::string> paths;
		XMLListReader xmlReader = XMLListReader(listPath);

		xmlReader.parse("theme",&paths);

		for ( std::list<std::string>::const_iterator itPath = paths.begin() ; itPath != paths.end() ; ++itPath )
		{
			loadTheme(*itPath);
		}
	}
	catch ( XMLParsingFailedException& xmle )
	{
		(void)xmle;
		throw EngineException("Fail to open list of theme paths '" + listPath + "'");
	}
}
