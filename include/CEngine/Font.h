#ifndef __FONT_H__
#define __FONT_H__

#ifndef DOXYGEN_IGNORE_TAG
/**
CEngine gives tools to easily build 2D games
Copyright (C) 2015-2015  Alexandre LAURENT

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

website: https://github.com/LittleWhite-tb/CEngine
e-mail: lw.demoscene@gmail.com
**/
#endif

#include <string>

#include "NEngine/Types/Vec2.h"
#include "NEngine/Types/Size2.h"
#include "NEngine/Types/Colour.h"

namespace NE { class Renderer; }
namespace NE { class Sprite; }

namespace CE
{
    class Font
    {
    private:

        const NE::Sprite* pSprite;

        USize2 letterSize;
        unsigned char startingLetter;

        // Disallow the copy
        Font(const Font& s);
        void operator= (const Font& s);

    public:
        Font(const NE::Sprite* pSprite, const USize2& letterSize, const unsigned char startingLetter);
        ~Font(void);

        USize2 getLetterSize(void) { return letterSize; }
        USize2 getStringSize(const std::string& string);

        bool draw(const NE::Renderer& r, const std::string& text, const IVec2& position);
    };
}

/*! \class CE::Font Font.h "Engine/Font.h"
 *  \brief Bitmap font
 *
 */

/*! \fn CE::Font::Font(const NE::Sprite* pSprite, const USize2& letterSize, const unsigned char startingLetter)
 * \param pSprite the Sprite to use as source
 * \param letterSize the size of one letter
 * \param startingLetter the letter with which one the bitmap is starting
 */

/*! \fn CE::Font::~Font(void)
 */

 /*! \fn USize2 CE::Font::getLetterSize(void)
  * \brief Get the size of one letter
  * \return the size of one letter
  */

/*! \fn USize2 CE::Font::getStringSize(const std::string& string)
 * \brief Get the size of the text when using this Font
 * \param string The text to calculate the size
 * \return the size of the surface to render the text
 */

/*! \fn bool CE::Font::draw(const NE::Renderer& r, const std::string& text, const IVec2& position)
 * \brief Draw a text with the font
 * \param r the NE::Renderer to use to draw the Font
 * \param text the Text to draw
 * \param position the position where to draw
 * \return true if all goes right
 */

#endif
