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

struct SDL_Surface;
struct SDL_Color;

class SpriteManager;

class Sprite
{
private:

	// Disallow the copy
	Sprite(const Sprite& s);
	void operator= (const Sprite& s);

protected:
	
	SDL_Surface* surface;		/*!< the internal surface */

public:

	//! Basic constructor
	/*!
      Load the image, using the SpriteManager
	  To check the loading failure, you have to use getSurface() to check if the pointer returns is NULL
	  \param sm the sprite manager to use to load the image
	  \param fileName the file to load
	  \param needScaling if some scaling operation has to be done on this sprite
    */
	Sprite(SpriteManager& sm, const std::string& fileName,const bool needScaling);

	//! Basic destructor
	/*!
      Free the internal surface
    */
	virtual ~Sprite(void);

	//! Get the width
	/*!
		\return returns the width of the surface
	*/
	virtual const int getWidth(void)const;

	//! Get the height
	/*!
		\return returns the height of the surface
	*/
	virtual const int getHeight(void)const;

	//! Get the surface
	/*!
		\return returns the surface
	*/
	SDL_Surface* const getSurface(void)const { return surface; }
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

#endif