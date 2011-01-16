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

#include "AnimatedSprite.h"

#include <cassert>

#include "../NEngine/Renderer.h"
#include "../NEngine/Sprite.h"

#include "../Types/Colour.h"
#include "../Types/Rect.h"

#include "../Utils/Logger.h"
#include "../Utils/Scaler.h"

AnimatedSprite :: AnimatedSprite(NE::Sprite* pSprite, const USize2& spriteSize, const unsigned int msInterval)
    :pSprite(pSprite),animationCounter(0),lastUpdate(0),msInterval(msInterval)
{
    USize2 surfaceSize = pSprite->getSize();
    this->spriteSize = spriteSize;

	// We scale the size of the sprite surface (since we always apply the scaler on the surface, from the SpriteManager)
/*
	if ( needScaling )
	{
		this->widthSprite = static_cast<unsigned int>(width * Scaler::getXScaleFactor());
		this->heightSprite = static_cast<unsigned int>(height * Scaler::getYScaleFactor());
	}
*/

	// Special cas where the size given by the user is not completely right, or there is only one sprite (no animation)
/*
	if ( surfaceSize.width < static_cast<int>(widthSprite) )
	{
		this->widthSprite = surfaceSize.width;
	}

	if ( surfaceSize.height < static_cast<int>(heightSprite) )
	{
		this->heightSprite = surfaceSize.height;
	}
*/
	numberAnimation = (surfaceSize.width / this->spriteSize.width) * (surfaceSize.height / this->spriteSize.height );
	
	LDebug << "AnimatedSprite (" << spriteSize << ") Nb Animation: " << numberAnimation;
}

AnimatedSprite :: ~AnimatedSprite(void)
{
	LDebug << "AnimatedSprite deleted";
}

void AnimatedSprite :: update(const unsigned int time)
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

Rect AnimatedSprite :: getSrcRect(const unsigned int time)
{
	unsigned int nbAnimOnWidth = this->pSprite->getSize().width / spriteSize.width;
	
	IVec2 position(	spriteSize.width * (animationCounter % nbAnimOnWidth),
					spriteSize.height * (animationCounter / nbAnimOnWidth));

	Rect srcRect(position,spriteSize);

	//LDebug << "AnimatedSprite :: getSrcRect (" << srcRect.x << ";" << srcRect.y << ";" << srcRect.w << ";" << srcRect.h << ")";

	this->update(time);

	return srcRect;
}

bool AnimatedSprite :: draw(const NE::Renderer& r, const IVec2& position, const unsigned int time)
{
	Rect srcRect = this->getSrcRect(time);

	return r.drawSurface(position,*pSprite,srcRect);
}

bool AnimatedSprite :: draw(const NE::Renderer& r, const IVec2& position, const Colour& mask, const unsigned int time)
{
	Rect srcRect = this->getSrcRect(time);

	return r.drawSurface(position,*pSprite,srcRect,mask);
}
