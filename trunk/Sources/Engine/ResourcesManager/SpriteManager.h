#ifndef __SPRITEMANAGER_H__
#define __SPRITEMANAGER_H__

#include <map>
#include <string>

struct SDL_Surface;

class SpriteManager
{
private:
	std::map<std::string, SDL_Surface*> spriteBank;

public:
	SpriteManager(void);
	~SpriteManager(void);

	SDL_Surface* getSurface(const std::string& fileName);
};

#endif