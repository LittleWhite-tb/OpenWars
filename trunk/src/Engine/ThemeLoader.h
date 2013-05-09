#ifndef __THEMELOADER_H__
#define __THEMELOADER_H__

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

#include <string>

#include "Engine/Library.h"
#include "Engine/Theme.h"

namespace NE { class SpriteLoader; }

class ThemeLoader
{
private:
	static void loadTheme(NE::SpriteLoader* pSpriteLoader, const std::string& themeName, Library<Theme>* pLibrary);

public:
	static void loadThemeList(NE::SpriteLoader* pSpriteLoader, const std::string& listPath, Library<Theme>* pLibrary);
};

/*! \class ThemeLoader ThemeLoader.h "Engine/ThemeLoader.h"
 *  \brief Loader for themes
 *	\sa Theme
 */

/*!	\fn static void ThemeLoader :: loadTheme(NE::SpriteLoader* pSpriteLoader, const std::string& themeName, Library<Theme>* pLibrary)
 *	\brief load a theme called 'themeName'
 *	\param pSpriteLoader the SpriteLoader to use to load the Theme
 *	\param themeName the theme to load
 *	\param pLibrary pointer to the Library to fill
 *	\exception EngineException when the loading of a theme failed
 */

/*!	\fn static void ThemeLoader :: loadThemeList(NE::SpriteLoader* pSpriteLoader, const std::string& listPath, Library<Theme>* pLibrary)
 *	\brief load a list of theme kept in a XML file
 *	\param pSpriteLoader the SpriteLoader to use to load the Theme
 *	\param listPath the path to the XML file to load (list of themes)
 *	\param pLibrary pointer to the Library to fill
 *	\exception EngineException when the XML file is not found
 *	\exception EngineException when the loading of a theme failed
 */

#endif