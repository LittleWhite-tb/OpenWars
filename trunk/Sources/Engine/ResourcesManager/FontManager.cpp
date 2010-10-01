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

#include "FontManager.h"

#include <map>
#include <string>

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "../../Utils/Logger.h"

FontManager :: FontManager(void)
{
	LDebug << "SpriteManager created";
}

FontManager :: ~FontManager(void)
{
	// For all files
	for( std::map<std::string, std::vector<FontPair> >::const_iterator itFonts = fontsBank.begin() ; itFonts != fontsBank.end() ; ++itFonts )
	{
		// For all sizes
		for ( std::vector<FontPair>::const_iterator itFont = itFonts->second.begin() ; itFont != itFonts->second.end() ; ++itFont )
		{
			TTF_CloseFont(itFont->pFont);
		}
	}

	fontsBank.clear();

	LDebug << "FontManager deleted";
}

TTF_Font* FontManager :: getFont(const std::string& fileName,const int size)
{
	std::map<std::string, std::vector<FontPair> >::iterator itFonts;

	LDebug << "FontManager :: getFont (" << fileName << ") size:" << size;

	itFonts = fontsBank.find(fileName);
	if ( itFonts == fontsBank.end() ) // We never load this font yet
	{
		TTF_Font* pFont = TTF_OpenFont(fileName.c_str(),size);
		if ( pFont == NULL )
		{
			LError << "Fail to load font '" << fileName.c_str() << "' (" << TTF_GetError() << ")";
		}
		else
		{
			// Adding the font
			fontsBank[fileName].push_back(FontPair(pFont,size));
		}

		return pFont;
	}
	else
	{
		for ( std::vector<FontPair>::iterator itFont = itFonts->second.begin() ; itFont != itFonts->second.end() ; ++itFont )
		{
			if ( itFont->size == size ) // So same file, same size
			{
				return itFont->pFont;
			}
		}

		// If we are here, we have to load
		TTF_Font* pFont = TTF_OpenFont(fileName.c_str(),size);
		if ( pFont == NULL )
		{
			LError << "Fail to load font '" << fileName.c_str() << "' (" << TTF_GetError() << ")";
		}
		else
		{
			fontsBank[fileName].push_back(FontPair(pFont,size));
			return pFont;
		}
	}

	return NULL;	// Bad isn't it?
}