#ifndef __NE_SDL_SPRITE_H__
#define __NE_SDL_SPRITE_H__

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

#include "NEngine/Sprite.h"

#include "NEngine/Types/Vec2.h"

struct SDL_Surface;

namespace NE
{
    class SDL_Sprite : public Sprite
    {
    private:

        SDL_Surface* pSurface;

    protected:
         void* getNativeSprite(void)const { return pSurface; }

        ~SDL_Sprite(void);

    public:
        SDL_Sprite(SDL_Surface* pSprite);

        USize2 getSize(void)const;
    };
}

/*! \class NE::SDL_Sprite SDL_Sprite.h "NEngine/Native/SDL/SDL_Sprite.h"
 *  \brief SDL implementation for Sprite
 */

/*! \fn NE::SDL_Sprite::SDL_Sprite(SDL_Surface* pSprite)
 * \param pSprite Native surface to use by the Sprite
 */

#endif
