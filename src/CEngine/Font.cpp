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

#include "CEngine/Font.h"

#include <string>
#include <cassert>

#include "NEngine/Sprite.h"
#include "NEngine/Renderer.h"

#include "NEngine/Types/Size2.h"
#include "NEngine/Types/Rect.h"

#include "NEngine/Exceptions/ConstructionFailedException.h"

CE::Font::Font(const NE::Sprite* pSprite, const USize2& letterSize, const unsigned char startingLetter)
    :pSprite(pSprite),letterSize(letterSize),startingLetter(startingLetter)
{
    assert(pSprite);
}

CE::Font::~Font(void)
{
}

USize2 CE::Font::getStringSize(const std::string& string)
{
    USize2 size;

    size.height = letterSize.height;
    size.width = string.size()*letterSize.width/2;

    return size;
}

bool CE::Font::draw(const NE::Renderer& r, const std::string& text, const IVec2& position)
{
    bool noError = true;
    Rect rectLetter(IVec2(0,0),letterSize);
    unsigned int numberLetterWidth = pSprite->getSize().width / letterSize.width;
    IVec2 drawPosition(position);

    for ( unsigned int i = 0 ; i < text.size() && noError ; i++ )
    {
        unsigned char actualLetter = text.at(i) - startingLetter;
        unsigned line = actualLetter / numberLetterWidth;
        unsigned col = actualLetter % numberLetterWidth;

        rectLetter.position = IVec2(col * letterSize.width , line * letterSize.height);

        noError &= r.drawSurface(drawPosition,pSprite,rectLetter);

        drawPosition.x += letterSize.width/2;
    }

    return noError;
}
