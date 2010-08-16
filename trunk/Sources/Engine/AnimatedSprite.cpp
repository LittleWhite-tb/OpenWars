#include "AnimatedSprite.h"

#include "Sprite.h"

#include "Window.h"
#include "Renderer.h"
#include "ResourcesManager/SpriteManager.h"

#include "../Utils/Logger.h"

AnimatedSprite :: AnimatedSprite(SpriteManager& sm, const std::string& fileName, const unsigned int width, const unsigned int height, const unsigned int msInterval)
	:Sprite(sm,fileName),widthSprite(width),heightSprite(height),animationCounter(0),lastUpdate(0),msInterval(msInterval)
{
	numberAnimation = (this->surface->w / widthSprite) * (this->surface->h / heightSprite );
	
	LDebug << "AnimatedSprite created from '" << fileName.c_str() << "' (" << width << "x" << height << ") Nb Animation: " << numberAnimation;
	
}

AnimatedSprite :: ~AnimatedSprite(void)
{
	LDebug << "AnimatedSprite deleted";
}

SDL_Rect AnimatedSprite :: getSrcRect(const unsigned int time)const
{
	unsigned int nbAnimOnWidth = this->surface->w / widthSprite;
	int x = widthSprite * numberAnimation % nbAnimOnWidth;
	int y = heightSprite * numberAnimation / nbAnimOnWidth;

	SDL_Rect srcRect = { static_cast<Sint16>(x) , static_cast<Sint16>(y) , static_cast<Uint16>(widthSprite), static_cast<Uint16>(heightSprite)};

	LDebug << "AnimatedSprite :: getSrcRect (" << srcRect.x << ";" << srcRect.y << ";" << srcRect.w << ";" << srcRect.h << ")";

	return srcRect;
}