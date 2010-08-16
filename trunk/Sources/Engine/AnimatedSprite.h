#ifndef __ANIMATEDSPRITE_H__
#define __ANIMATEDSPRITE_H__

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

public:
	AnimatedSprite(SpriteManager& sm, const std::string& fileName, const unsigned int width, const unsigned int height, const unsigned int msInterval);
	~AnimatedSprite(void);

	SDL_Rect getSrcRect(const unsigned int time)const;

	const int getWidth(void)const { return widthSprite; }
	const int getHeight(void)const { return heightSprite; }

	const unsigned int getInterval(void)const { return msInterval; }
	const void setInterval(const unsigned int newInterval) { msInterval = newInterval; }
};

#endif