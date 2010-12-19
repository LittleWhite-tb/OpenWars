#ifndef __FONTMANAGER_H__
#define __FONTMANAGER_H__

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

#include <SDL/SDL_ttf.h>

#include <map>
#include <vector>
#include <string>

class FontManager
{
	struct FontPair
	{
		TTF_Font* pFont;
		int size;

		FontPair(void):pFont(NULL),size(0) {};
		FontPair(TTF_Font* const pFont, const int size):pFont(pFont),size(size) {};
	};

private:
	std::map<std::string, std::vector<FontPair> > fontsBank;			/*!< Bank of fonts already loaded */

	// Block the copy of this class
	FontManager(const FontManager& fm);
	void operator= (const FontManager& fm);

public:
	FontManager(void);
	~FontManager(void);

	TTF_Font* getFont(const std::string& fileName, const int size);
};

/*! \class FontManager FontManager.h "Engine/ResourcesManager/FontManager.h"
 *  \brief Manager for the fonts resources
 *
 * The class handle the fonts loading.
 * If the font is not known, it will be loaded using TTF_OpenFont() (SDL_ttf). A font with the size will be created.
 * If the font is already known, we just return the pointer (TTF_Font*) on it depending on the size wanted
 *
 * The id used to recognise the font is simply the path to the font file
 *
 * When this is destructed, all pointers are correctly freed (TTF_CloseFont()), so thanks to this, we don't need to bother about memory liberation
 */

/*! \fn FontManager::FontManager(void)
 */

/*! \fn FontManager::~FontManager(void)
 * Deletes properly all fonts loaded
 *\

/*! \fn TTF_Font* FontManager::getFont(const std::string& fileName, const int size)
 * \brief Gets the font following the path to the font and the size
 * Check the bank to know if the font is already loaded with this size, if not, load the font and returns it.
 * \param fileName the name of the file to open (used as ID for the bank)
 * \param size the size wanted for the font
 */

#endif