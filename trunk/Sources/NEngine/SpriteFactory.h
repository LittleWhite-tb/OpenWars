#ifndef __SPRITEFACTORY_H__
#define __SPRITEFACTORY_H__

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

#include <map>

#include "../Types/Colour.h"
#include "../Types/Size2.h"

namespace NE
{
    class Sprite;
    
    class SpriteFactory
    {
    private: 

        std::map<std::pair<USize2, Colour>, Sprite*> spritesBank; /*<! Bank of Sprite already created */

    protected:

        virtual Sprite* createSprite(const Colour& colour, const USize2& spriteSize)=0;

    public:
        virtual ~SpriteFactory(void);
    
        Sprite* createSpriteFromColour(const Colour& colour, const USize2& spriteSize);
    };
}

bool operator< (const std::pair<USize2, Colour>& p1, const std::pair<USize2, Colour>& p2);

/*! \class NE::SpriteFactory SpriteFactory.h "NEngine/SpriteFactory.h"
 *  \brief SpriteFactory interface to create Sprites
 *
 * The SpriteFactory creates Sprite from a colour and a size
 * This class use a bank of Sprite to not create to times the same sprite
 */
 
 /*! \fn virtual NE::Sprite* NE::SpriteFactory::createSprite(const Colour& colour, const USize2& spriteSize)=0;
  * \brief Create a Sprite from a colour and a size
  * \param colour The colour of the Sprite
  * \param spriteSize the size of the Sprite
  * \return the Sprite created.
  */
 
 /*! \fn NE::Sprite* NE::SpriteFactory::createSpriteFromColour(const Colour& colour, const USize2& spriteSize);
  * \brief Create a Sprite from a colour and a size
  * \param colour The colour of the Sprite
  * \param spriteSize the size of the Sprite
  * \return the Sprite created.
  */

#endif
