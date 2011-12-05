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

#include <NEngine/SpriteLoader.h>
#include "Game/GameEngine.h"
#include "XML/XMLListReader.h"

void ThemeLoader :: loadTheme(NE::SpriteLoader* pSpriteLoader, const std::string& themeName, Library<Theme>* pLibrary)
{
    Theme* pTheme = new Theme(themeName);

    if ( pTheme == NULL )
    {
        LError << "Fail to allocate Theme";
        throw std::bad_alloc();
    }

    if ( pTheme->load(pSpriteLoader) == false )
    {
        throw EngineException("Failed to load the theme (" + themeName+ ")");
    }
    else
    {
        pLibrary->add(pTheme->getName(),pTheme);
    }
}

void ThemeLoader :: loadThemeList(NE::SpriteLoader* pSpriteLoader, const std::string& listPath, Library<Theme>* pLibrary)
{
    std::cout << "B0" << std::endl;
    try
    {
        std::cout << "B1" << std::endl;
        std::list<std::string> paths;
        std::cout << "B2" << std::endl;
        XMLListReader xmlReader = XMLListReader(listPath);
        std::cout << "B3" << std::endl;

        xmlReader.parse("theme",&paths);
        std::cout << "B4" << std::endl;

        for ( std::list<std::string>::const_iterator itPath = paths.begin() ; itPath != paths.end() ; ++itPath )
        {
            std::cout << "B5" << std::endl;
            ThemeLoader::loadTheme(pSpriteLoader,*itPath,pLibrary);
        }
        std::cout << "B6" << std::endl;
    }
    catch ( XMLParsingFailedException& xmle )
    {
        std::cout << "B7" << std::endl;
        (void)xmle;
        throw EngineException("Fail to open list of theme paths '" + listPath + "'");
    }
}
