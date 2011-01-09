#ifndef __SPRITE_H__
#define __SPRITE_H__

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

#include <string>

#include "../Types/Vec2.h"
#include "../Types/Size2.h"

class SpriteManager;
struct Colour;

struct SDL_Surface;

namespace NE { class Renderer; }

class Sprite
{
private:

	// Disallow the copy
	Sprite(const Sprite& s);
	void operator= (const Sprite& s);

protected:
	
	SDL_Surface* pSurface;		/*!< the internal surface */

public:
	Sprite(SpriteManager& sm, const std::string& fileName,const bool needScaling);
	Sprite(SDL_Surface* pSurface);

	virtual ~Sprite(void);

	virtual int getWidth(void)const;
	virtual int getHeight(void)const;
	virtual USize2 getSize(void)const;

	SDL_Surface* getSurface(void)const { return pSurface; }

	virtual bool draw(const NE::Renderer& r, const IVec2& position);
	virtual bool draw(const NE::Renderer& r, const IVec2& position, const Colour& mask);
};

/*! \class Sprite Sprite.h "Engine/Sprite.h"
 *  \brief Sprite management class
 *
 * Simple sprite class, over SDL Surface design.
 * Can do the following:
 *		- Load from file (directly in the constructor)
 *		- Get the width
 *		- Get the height
 *		- Get surface
 */

/*! \fn Sprite::Sprite(SpriteManager& sm, const std::string& fileName,const bool needScaling)
 * Load the image, using the SpriteManager
 * To check the loading failure, you have to use getSurface() to check if the pointer returns is NULL
 * \param sm the sprite manager to use to load the image
 * \param fileName the file to load
 * \param needScaling if some scaling operation has to be done on this sprite
 */

/*! \fn Sprite::Sprite(SDL_Surface* pSurface)
 * The SDL_Surface should be ready to use.
 * \warning The SDL_Surface will not be deleted, you have to do to it just before deletion of the instance, using getSurface().
 * \param pSurface pointer on the surface to use
 */

/*! \fn virtual Sprite::~Sprite(void)
 * Free the internal surface
 */

/*! \fn virtual int Sprite::getWidth(void)const
 * \brief Get the width
 * \return returns the width of the surface
 */

/*! \fn virtual int Sprite::getHeight(void)const
 * \brief Get the height
 * \return returns the height of the surface
 */

/*! \fn virtual USize2 Sprite::getSize(void)const
 * \brief Get the size
 * \return returns the size of the surface
 */

/*! \fn SDL_Surface* Sprite::getSurface(void)const
 * \brief Get the surface
 * \return returns the surface
 */

/*! \fn virtual bool Sprite::draw(const NE::Renderer& r, const IVec2& position)
 * \brief Draw the Sprite at position
 * \param r the NE::Renderer used to draw the Sprite
 * \param position where to draw the sprite
 * \return true if all goes right
 */

/*! \fn virtual bool Sprite::draw(const NE::Renderer& r, const IVec2& position, const Colour& mask)
 * \brief Draw the Sprite at position
 * \param r the NE::Renderer used to draw the Sprite
 * \param position where to draw the sprite
 * \param mask mask to use when drawing the sprite
 * \return true if all goes right
 */

#endif
