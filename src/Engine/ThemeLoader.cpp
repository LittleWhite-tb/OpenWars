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

#include "ThemeLoader.h"

#include <list>

#include "NEngine/NEngine.h"
#include "NEngine/SpriteLoader.h"
#include "Game/GameEngine.h"
#include "XML/XMLListReader.h"

void ThemeLoader :: loadTheme(NE::SpriteLoader* pSpriteLoader, const std::string& themeName, Library<Theme>* pLibrary)
{
	Theme* pTheme = new Theme(themeName);
    if ( pTheme == NULL )
    {
        NEError << "Fail to allocate Theme\n";
        throw std::bad_alloc();
    }

    if ( pTheme->load(pSpriteLoader) == false )
    {
		delete pTheme;
        throw EngineException("Failed to load the theme (" + themeName+ ")");
    }
    else
    {
        pLibrary->add(pTheme->getName(),pTheme);
    }
}

void ThemeLoader :: loadThemeList(NE::SpriteLoader* pSpriteLoader, const std::string& listPath, Library<Theme>* pLibrary)
{
	try
    {
        std::list<std::string> paths;
        XMLListReader xmlReader = XMLListReader(listPath);

        xmlReader.parse("theme",&paths);

        for ( std::list<std::string>::const_iterator itPath = paths.begin() ; itPath != paths.end() ; ++itPath )
        {
			ThemeLoader::loadTheme(pSpriteLoader,*itPath,pLibrary);
        }
    }
	catch ( XMLParsingFailedException& xmle )
    {
        (void)xmle;
        throw EngineException("Fail to open list of theme paths '" + listPath + "'");
    }
}
