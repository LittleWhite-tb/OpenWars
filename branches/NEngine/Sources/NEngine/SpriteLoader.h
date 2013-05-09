#ifndef NE_SPRITELOADER_H
#define NE_SPRITELOADER_H

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

#include <list>

#include "NEngine/Types/Colour.h"
#include "NEngine/Loader.h"
#include "NEngine/ISpriteLoader.h"
#include "NEngine/Sprite.h"

#include "Bank.h"

namespace NE
{
    class ISpriteLoader;

    class SpriteLoader : public Loader<NE::ISpriteLoader>
    {
    private:
        Colour m_transparencyColour;
        
        Bank<const Sprite> m_bank;

    public:

        SpriteLoader() {}

        const Sprite* loadSpriteFromFile(const std::string& fileName);

        void setTransparencyColour(const Colour& transparencyColour) { m_transparencyColour = transparencyColour; }
        const Colour& getTransparencyColour() { return m_transparencyColour; }
    };
}

#endif
