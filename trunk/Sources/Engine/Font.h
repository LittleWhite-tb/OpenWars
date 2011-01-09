#ifndef __FONT_H__
#define __FONT_H__

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

#include <string>

#include "../Types/Vec2.h"

class FontManager;
namespace NE { class Renderer; }

class Font
{
private:

	// Disallow the copy
	Font(const Font& s);
	void operator= (const Font& s);

	TTF_Font* pFont;			/*!< the font */
	SDL_Color colour;			/*!< the colour */

public:
	Font(FontManager& fm, const std::string& fileName, const int size, const SDL_Color& colour);
	~Font(void);

	IVec2 getSize(const std::string& text);

	SDL_Colour getColour(void)const { return colour; }
	void setColour(const SDL_Colour& newColour) { colour = newColour; }

	bool draw(const NE::Renderer& r, const std::string& text, const IVec2& position);
};

/*! \class Font Font.h "Engine/Font.h"
 *  \brief Class for fonts
 *
 *	The Font can:
 *		- Get the size of a text
 *		- Change the colour used to display the font
 *		- Draw
 */

/*! \fn Font::Font(FontManager& fm, const std::string& fileName, const int size, const SDL_Color& colour)
 * Load the font, using the FontManager with the size specified
 * \param fm The FontManager to use to load the font
 * \param fileName The file to load
 * \param size The size wanted for the font
 * \param colour The drawing colour
 */

/*! \fn Font::~Font(void)
 */

/*! \fn IVec2 Font::getSize(const std::string& text)
 * \brief Get the size of the surface that will be created when text is passed
 * Return the size of the surface created for the text passed
 * \param text The text to simulate to get the size
 * \return the size of the surface to render the text
 */

/*! \fn SDL_Colour Font::getColour(void)const
 * \brief Get the colour of the font
 * \return the colour
 */

/*! \fn void Font::setColour(const SDL_Colour& newColour)
 * \brief Set the colour of the font
 * \param newColour the new colour for the font
 */

/*! \fn bool Font::draw(const NE::Renderer& r, const std::string& text, const IVec2& position)
 * \brief Draw a text with the font
 * \param r the NE::Renderer to use to draw the Font
 * \param text the Text to draw
 * \param position the position where to draw
 * \return true if all goes right
 */

#endif
