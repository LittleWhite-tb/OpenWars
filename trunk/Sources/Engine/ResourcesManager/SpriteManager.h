#ifndef __SPRITEMANAGER_H__
#define __SPRITEMANAGER_H__

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

#include <map>
#include <string>

struct SDL_Surface;

class SpriteManager
{
	struct SurfacePair
	{
		SDL_Surface* pSprite;		/*!< Sprite scaled or not */

		SurfacePair(void):pSprite(NULL) {};
		SurfacePair(SDL_Surface* const pSprite):pSprite(pSprite) {};
	};

private:
	std::map<std::string, SurfacePair> spritesBank;			/*!< Bank of sprites already loaded */

	// Block the copy of this class
	SpriteManager(const SpriteManager& sm);
	void operator= (const SpriteManager& sm);

public:
	SpriteManager(void);
	~SpriteManager(void);

	SDL_Surface* getSurface(const std::string& fileName, const bool needScaling);
};

/*! \class SpriteManager SpriteManager.h "Engine/ResourcesManager/SpriteManager.h"
 *  \brief Manager for the sprites resources
 *
 * The class handle the sprites loading.
 * If the sprite is not known, it will be loaded using IMG_Load() (SDL_image). A scaled version of the sprite will be generated.
 * If the sprite is already known, we just return the pointer (SDL_Surface*) on it depending if the user need a scaled one or a normal one
 *
 * The id used to recognise the sprite is simply the path to the sprite file
 *
 * When this is destructed, all pointers are correctly freed (SDL_FreeSurface()), so thanks to this, we don't need to bother about memory liberation in Sprite / AnimatedSprite classes
 */

/*! \fn SpriteManager::SpriteManager(void)
 */

/*! \fn SpriteManager::~SpriteManager(void)
 * Deletes all Sprite loaded
 */

/*! \fn SDL_Surface* SpriteManager::getSurface(const std::string& fileName, const bool needScaling)
 * \brief Gets the surface following the path to the sprite
 * Check the bank to know if the sprite is already loaded, if not, load the sprite and returns it.
 * \param fileName the name of the file to open (used as ID for the bank)
 * \param needScaling ask for a normal sprite or a scaled one
 */

#endif