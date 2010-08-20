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

#include "AnimatedSprite.h"

#include "Sprite.h"

#include "Window.h"
#include "Renderer.h"
#include "ResourcesManager/SpriteManager.h"

#include "../Utils/Logger.h"

AnimatedSprite :: AnimatedSprite(SpriteManager& sm, const std::string& fileName, const unsigned int width, const unsigned int height, const unsigned int msInterval)
	:Sprite(sm,fileName),widthSprite(width),heightSprite(height),animationCounter(0),lastUpdate(0),msInterval(msInterval)
{
	// Special cas where the size given by the user is not completely right, or there is only one sprite (no animation)
	if ( this->surface->w < static_cast<int>(widthSprite) )
	{
		this->widthSprite = this->surface->w;
	}

	if ( this->surface->h < static_cast<int>(heightSprite) )
	{
		this->heightSprite = this->surface->h;
	}

	numberAnimation = (this->surface->w / this->widthSprite) * (this->surface->h / this->heightSprite );
	
	LDebug << "AnimatedSprite created from '" << fileName.c_str() << "' (" << width << "x" << height << ") Nb Animation: " << numberAnimation;
	
}

AnimatedSprite :: ~AnimatedSprite(void)
{
	LDebug << "AnimatedSprite deleted";
}

void AnimatedSprite :: update(const unsigned int time)
{
	LDebug << "AnimatedSprite :: update (" << time << ")";

	if ( time - lastUpdate > msInterval )
	{
		LDebug << "\tNext animation";

		animationCounter++;

		if ( animationCounter >= numberAnimation )
		{
			animationCounter=0;
		}

		lastUpdate = time;
	}
}

SDL_Rect AnimatedSprite :: getSrcRect(const unsigned int time)
{
	unsigned int nbAnimOnWidth = this->surface->w / widthSprite;
	
	int x = widthSprite * (animationCounter % nbAnimOnWidth);
	int y = heightSprite * (animationCounter / nbAnimOnWidth);

	SDL_Rect srcRect = { static_cast<Sint16>(x) , static_cast<Sint16>(y) , static_cast<Uint16>(widthSprite), static_cast<Uint16>(heightSprite)};

	LDebug << "AnimatedSprite :: getSrcRect (" << srcRect.x << ";" << srcRect.y << ";" << srcRect.w << ";" << srcRect.h << ")";

	this->update(time);

	return srcRect;
}