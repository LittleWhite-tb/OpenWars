#ifndef __ANIMATEDSPRITE_H__
#define __ANIMATEDSPRITE_H__

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

#include <SDL/SDL.h>

#include "Sprite.h"

#include "../Types/Vec2.h"

class Window;
class Renderer;
class SpriteManager;

class AnimatedSprite : public Sprite
{
private:
	unsigned int widthSprite;
	unsigned int heightSprite;

	unsigned int numberAnimation;
	unsigned int animationCounter;

	unsigned int lastUpdate;

	unsigned int msInterval;


	void update(const unsigned int time);

public:
	AnimatedSprite(SpriteManager& sm, const std::string& fileName, const unsigned int width, const unsigned int height, const unsigned int msInterval);
	~AnimatedSprite(void);

	SDL_Rect getSrcRect(const unsigned int time);

	const int getWidth(void)const { return widthSprite; }
	const int getHeight(void)const { return heightSprite; }

	const unsigned int getInterval(void)const { return msInterval; }
	const void setInterval(const unsigned int newInterval) { msInterval = newInterval; }
};

#endif