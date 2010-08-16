#include "SpriteManager.h"

#include <map>
#include <string>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "../../Utils/Logger.h"

SpriteManager :: SpriteManager(void)
{
	LDebug << "SpriteManager created";
}

SpriteManager :: ~SpriteManager(void)
{
	for( std::map<std::string, SDL_Surface*>::const_iterator itSprite = spriteBank.begin() ; itSprite != spriteBank.end() ; ++itSprite )
	{
		SDL_FreeSurface(itSprite->second);
	}
	spriteBank.clear();

	LDebug << "SpriteManager deleted";
}

SDL_Surface* SpriteManager :: getSurface(const std::string& fileName)
{
	LDebug << "SpriteManager :: getSurface (" << fileName << ")";

	if ( spriteBank.find(fileName) == spriteBank.end() )
	{
		spriteBank[fileName] = IMG_Load(fileName.c_str());
		if ( spriteBank[fileName] == NULL )
		{
			LError << "Fail to load image '" << fileName.c_str() << "' (" << IMG_GetError() << ")";
		}
	}
	else // Here the case when the sprite is already constructed
	{
		return spriteBank[fileName];
	}

	return spriteBank[fileName];
}