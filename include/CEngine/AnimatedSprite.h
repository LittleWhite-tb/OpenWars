#ifndef __ANIMATEDSPRITE_H__
#define __ANIMATEDSPRITE_H__

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
#include "NEngine/Types/Rect.h"

namespace NE { class Renderer; }
namespace NE { class SpriteLoader; }
namespace NE { class Sprite; }

struct Colour;

namespace CE
{
    class AnimatedSprite
    {
    private:

        const NE::Sprite* pSprite;
        USize2 spriteSize;

        unsigned int numberAnimation;           /*!< number of animation in the sprite */
        unsigned int animationCounter;          /*!< number of the current animation */

        unsigned int lastUpdate;                /*!< last time that the animated sprite has been updated */

        unsigned int msInterval;                /*!< interval between two sprites of the animation */

        // Disallow the copy
        AnimatedSprite(const AnimatedSprite& as);
        void operator= (const AnimatedSprite& as);

        void update(const unsigned int time);

    public:
        AnimatedSprite(const NE::Sprite* pSprite, const USize2& spriteSize, const unsigned int msInterval);
        AnimatedSprite(NE::SpriteLoader* pSL, const std::string& fileName, const USize2& spriteSize, const unsigned int msInterval);

        ~AnimatedSprite(void);

        Rect getSrcRect(const unsigned int time);

        USize2 getSize(void)const { return spriteSize; }

        unsigned int getInterval(void)const { return msInterval; }
        void setInterval(const unsigned int newInterval) { msInterval = newInterval; }

        bool draw(const NE::Renderer& r, const IVec2& position, const unsigned int time=0);
        bool draw(const NE::Renderer& r, const IVec2& position, const Colour& mask, const unsigned int time=0);
    };
}

/*! \class CE::AnimatedSprite AnimatedSprite.h "Engine/AnimatedSprite.h"
 *  \brief Animated sprite management class
 *
 * Handle the case of set of sprites for animation
 * Can do the following:
 *      - Load from file (directly in the constructor)
 *      - Get the width
 *      - Get the height
 *      - Get the rectangle to use to draw the correct animation
 *      - Get interval between two sprites of the animation, in milliseconds
 *      - Set interval between two sprites of the animation, in milliseconds
 */

/*! \fn void CE::AnimatedSprite::update(const unsigned int time)
 * \brief Updates the instance to change the sprite to show if needed
 * \param time the actual time
 */

/*! \fn CE::AnimatedSprite::AnimatedSprite(NE::Sprite* pSprite, const USize2& spriteSize, const unsigned int msInterval);
 * Do an animation using a Sprite. The animated sprite size is given by spriteSize.
 * \param pSprite the Sprite to use for the animation
 * \param spriteSize the size of the sprite
 * \param msInterval interval between two sprite in milliseconds
 */

/*! \fn CE::AnimatedSprite::AnimatedSprite(NE::SpriteLoader* pSL, const std::string& fileName, const USize2& spriteSize, const unsigned int msInterval)
 *  \brief Create an animation from a file
 *  \param pSL pointer to the SpriteLoader to use
 *  \param fileName the file to load as an AnimatedSprite
 *  \param spriteSize the size of each sprite
 *  \param msInterval the time between two sprites
 */

/*! \fn CE::AnimatedSprite::~AnimatedSprite(void)
 */

/*! \fn Rect CE::AnimatedSprite::getSrcRect(const unsigned int time)
 * \brief Get the source rectangle for the internal surface, to draw
 * Following the current frame, the rectangle to draw will be returned
 * \param time the actual time
 */

/*! \fn USize2 CE::AnimatedSprite::getSize(void)const
 * \brief Get the size of the animated sprite
 * \return returns the size of the animated sprite
 */

/*! \fn unsigned int CE::AnimatedSprite::getInterval(void)const
 * \brief Get the interval between two frames
 * \return returns the interval in millisecond
 */

/*! \fn void CE::AnimatedSprite::setInterval(const unsigned int newInterval)
 * \brief Set the interval between two frames
 * \param newInterval the new interval in millisecond
 */

/*! \fn bool CE::AnimatedSprite::draw(const NE::Renderer& r, const IVec2& position, const unsigned int time=0)
 * \brief Draw the Sprite at position
 * \param r the NE::Renderer to use to draw the AnimatedSprite
 * \param position where to draw the sprite
 * \param time time of the animation
 * \return true if all goes right
 */

/*! \fn bool CE::AnimatedSprite::draw(const NE::Renderer& r, const IVec2& position, const Colour& mask, const unsigned int time=0)
 * \brief Draw the Sprite at position
 * \param r the NE::Renderer to use to draw the AnimatedSprite
 * \param position where to draw the sprite
 * \param mask mask to use when drawing the sprite
 * \param time time of the animation
 * \return true if all goes right
 */

#endif
