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

#include "Sprite.h"

#include "../NEngine/NE.h"
#include "../NEngine/NEngine.h"
#include "../NEngine/NETypes.h"

#include "../Types/Rect.h"

#include "ResourcesManager/SpriteManager.h"

#include "../Utils/Logger.h"
#include "../Utils/Scaler.h"

AnimatedSprite :: AnimatedSprite(SpriteManager& sm, const std::string& fileName, const unsigned int width, const unsigned int height, const unsigned int msInterval, const bool needScaling)
	:Sprite(sm,fileName,needScaling),animationCounter(0),lastUpdate(0),msInterval(msInterval)
{
	USize2 surfaceSize = NE::get()->getSurfaceSize(this->pSurface);

	// We scale the size of the sprite surface (since we always apply the scaler on the surface, from the SpriteManager)
	if ( needScaling )
	{
		this->widthSprite = static_cast<unsigned int>(width * Scaler::getXScaleFactor());
		this->heightSprite = static_cast<unsigned int>(height * Scaler::getYScaleFactor());
	}

	// Special cas where the size given by the user is not completely right, or there is only one sprite (no animation)
	if ( surfaceSize.width < static_cast<int>(widthSprite) )
	{
		this->widthSprite = surfaceSize.width;
	}

	if ( surfaceSize.height < static_cast<int>(heightSprite) )
	{
		this->heightSprite = surfaceSize.height;
	}

	numberAnimation = (surfaceSize.width / this->widthSprite) * (surfaceSize.height / this->heightSprite );
	
	LDebug << "AnimatedSprite created from '" << fileName.c_str() << "' (" << this->widthSprite << "x" << this->heightSprite << ") Nb Animation: " << numberAnimation;
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
	unsigned int nbAnimOnWidth = NE::get()->getSurfaceSize(this->pSurface).width / widthSprite;
	
	IVec2 position(	widthSprite * (animationCounter % nbAnimOnWidth),
					heightSprite * (animationCounter / nbAnimOnWidth));

	Rect srcRect(position,USize2(widthSprite,heightSprite));

	//LDebug << "AnimatedSprite :: getSrcRect (" << srcRect.x << ";" << srcRect.y << ";" << srcRect.w << ";" << srcRect.h << ")";

	this->update(time);

	return srcRect;
}

bool AnimatedSprite :: draw(Window* const pWin, const IVec2& position, const unsigned int time)
{
	assert(pWin);

	Rect srcRect = this->getSrcRect(time);

	return NE::get()->drawSurface(pWin,position,this->pSurface,srcRect);
}

bool AnimatedSprite :: draw(Window* const pWin, const IVec2& position, const Colour& mask, const unsigned int time)
{
	assert(pWin);

	Rect srcRect = this->getSrcRect(time);

	return NE::get()->drawSurface(pWin,position,this->pSurface,srcRect,mask);
}