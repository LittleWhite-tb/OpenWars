#ifndef __SDL_SPRITEFACTORY_H__
#define __SDL_SPRITEFACTORY_H__

#ifndef DOXYGEN_IGNORE_TAG
/**
NEngine: Native Engine abstracts multimedia libraries such as SDL, SFML, Allegro
Copyright (C) 2010-2015  Alexandre LAURENT

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

website: https://github.com/LittleWhite-tb/NEngine
e-mail: lw.demoscene@gmail.com
**/
#endif

#include "NEngine/SpriteFactory.h"

#include "NEngine/Types/Colour.h"

namespace NE
{
    class Sprite;

    class SDL_SpriteFactory : public SpriteFactory
    {
    protected:
        Sprite* createSprite(const Colour& colour, const USize2& spriteSize);
    };
}

/*! \class NE::SDL_SpriteFactory SDL_SpriteFactory.h "NEngine/Native/SDL/SDL_SpriteFactory.h"
 *  \brief SpriteFactory implementation for SDL
 *
 * The SpriteFactory creates sprite from a colour and a size
 */

#endif
