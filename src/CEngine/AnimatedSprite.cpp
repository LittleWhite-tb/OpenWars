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

#include "CEngine/AnimatedSprite.h"

#include <cassert>

#include "NEngine/NEngine.h"
#include "NEngine/Renderer.h"
#include "NEngine/SpriteLoader.h"
#include "NEngine/Sprite.h"

#include "NEngine/Types/Colour.h"
#include "NEngine/Types/Rect.h"

CE::AnimatedSprite::AnimatedSprite(const NE::Sprite* pSprite, const USize2& spriteSize, const unsigned int msInterval)
    :pSprite(pSprite),animationCounter(0),lastUpdate(0),msInterval(msInterval)
{
    USize2 surfaceSize = pSprite->getSize();
    this->spriteSize = spriteSize;

    numberAnimation = (surfaceSize.width / spriteSize.width) * (surfaceSize.height / spriteSize.height );

    NEDebug << "AnimatedSprite " << spriteSize << " Nb Animation: " << numberAnimation << "\n";
}

CE::AnimatedSprite::AnimatedSprite(NE::SpriteLoader* pSL, const std::string& fileName, const USize2& spriteSize, const unsigned int msInterval)
    :animationCounter(0),lastUpdate(0),msInterval(msInterval)
{
    assert(pSL);

    this->pSprite = pSL->loadSpriteFromFile(fileName);
    this->spriteSize = spriteSize;

    USize2 surfaceSize = pSprite->getSize();

    numberAnimation = (surfaceSize.width / spriteSize.width) * (surfaceSize.height / spriteSize.height );

    NEDebug << "AnimatedSprite '" << fileName << "' Nb Animation: " << numberAnimation << "\n";
}

CE::AnimatedSprite::~AnimatedSprite(void)
{
    NEDebug << "AnimatedSprite deleted\n";
}

void CE::AnimatedSprite::update(const unsigned int time)
{
    // LDebug << "AnimatedSprite :: update (" << time << ")";

    if ( time - lastUpdate > msInterval )
    {
        animationCounter++;

        if ( animationCounter >= numberAnimation )
        {
            animationCounter=0;
        }

        lastUpdate = time;
    }
}

Rect CE::AnimatedSprite::getSrcRect(const unsigned int time)
{
    unsigned int nbAnimOnWidth = this->pSprite->getSize().width / spriteSize.width;

    IVec2 position( spriteSize.width * (animationCounter % nbAnimOnWidth),
                    spriteSize.height * (animationCounter / nbAnimOnWidth));

    Rect srcRect(position,spriteSize);

    //NEDebug << "AnimatedSprite :: getSrcRect (" << srcRect.x << ";" << srcRect.y << ";" << srcRect.w << ";" << srcRect.h << ")";

    this->update(time);

    return srcRect;
}

bool CE::AnimatedSprite::draw(const NE::Renderer& r, const IVec2& position, const unsigned int time)
{
    Rect srcRect = this->getSrcRect(time);

    return r.drawSurface(position,pSprite,srcRect);
}

bool CE::AnimatedSprite::draw(const NE::Renderer& r, const IVec2& position, const Colour& mask, const unsigned int time)
{
    Rect srcRect = this->getSrcRect(time);

    return r.drawSurface(position,pSprite,srcRect,mask);
}
