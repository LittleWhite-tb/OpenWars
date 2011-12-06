#ifndef __NE_SDL_SPRITELOADER_H__
#define __NE_SDL_SPRITELOADER_H__

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

#include "NEngine/SpriteLoader.h"

#include <string>

namespace NE
{
    class Sprite;

    class SDL_SpriteLoader : public SpriteLoader
    {
    protected:
        Sprite* loadSprite(const std::string& fileName);
    };
}

/*! \class NE::SDL_SpriteLoader SDL_SpriteLoader.h "NEngine/Native/SDL/SDL_SpriteLoader.h"
 *  \brief SDL implementation for SpriteLoader
 */

#endif
