#ifndef __SCALER_H__
#define __SCALER_H__

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

struct SDL_Surface;

class Window;

#include "../Types/Vec2.h"

class Scaler
{
private:

	static double xScaleFactor;		/*!< the scaling factor on the x axis */
	static double yScaleFactor;		/*!< the scaling factor on the y axis */
	static UVec2 offset;			/*!< Offset to apply to have the center the tiles

	//! Shrink the surface
	/*!
		Apply a shrink operation on the source to create the destination.
		The shrink function can only support fraction of the original image.
		\param pSrcSurface the source surface
		\param pDstSurface the destination surface
		\return true if all is right
	*/
	static bool shrinkSurface(SDL_Surface* const pSrcSurface, SDL_Surface* const pDstSurface);

	//! Zoom the surface
	/*!
		Apply a zoom operation on the source to create the destination
		\param pSrcSurface the source surface
		\param pDstSurface the destination surface
		\return true if all is right
	*/
	static bool zoomSurface(SDL_Surface* const pSrcSurface, SDL_Surface* const pDstSurface);

public:

	//! Set the scaling factors
	/*!
		To determine the scaling factor, we are using the size of the window plus some globals set in globals.h
		\param win the window to match
	*/
	static void setScaleFactor(const Window& win);

	//! Scale a surface
	/*!
		Apply the scale factors to the source surface to create the new scaled surface
		Once the operation is done, the source is kept without any modifications (not freed).
		The output surface is newly allocated.
		\param pSrcSurface the sprite to scale
		\return the scaled surface or NULL if the function failed
	*/
	static SDL_Surface* scale(SDL_Surface* const pSrcSurface);

	//! Get the scaling factor on the X axis
	/*!
		\return the current scaling factor for the X axis
	*/
	static double getXScaleFactor(void) { return xScaleFactor; }

	//! Get the scaling factor on the Y axis
	/*!
		\return the current scaling factor for the Y axis
	*/
	static double getYScaleFactor(void) { return yScaleFactor; }

	//* Get the offset
	/*!
		\return the offset to apply to center the map
	*/
	static UVec2 getOffset(void) { return offset; }

};

/*! \class Scaler Scaler.h "Utils/Scaler.h"
 *  \brief Scaling operation utilities
 *
 * Give functions to handle the sprites scaling operations
 * The scale factor is determined by using the size of the window and some globals (see globals.h)
 * The scale functions is inspired by the SDL_gfx library
 * setScaleFactor() neeeds to be call after the Window creation, but before the SpriteManager usage (so before creating a Sprite or AnimatedSprite)
 */

#endif