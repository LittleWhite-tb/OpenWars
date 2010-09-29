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

#include "Scaler.h"

#include <SDL/SDL.h>

#include <cassert>

#include "../Engine/Window.h"

#include "Logger.h"
#include "../globals.h"

// Default values
double Scaler::xScaleFactor = 1.0;
double Scaler::yScaleFactor = 1.0;

void Scaler :: setScaleFactor(const Window& win)
{
	xScaleFactor = (win.getWidth() / (double)MAP_MIN_WIDTH) / (double)TILE_DEFAULT_WIDTH;
	yScaleFactor = (win.getHeight() / (double)MAP_MIN_HEIGHT) / (double)TILE_DEFAULT_HEIGHT;

	LDebug << "Scaler :: setScaleFactor (Found: " << xScaleFactor << ";" << yScaleFactor << ")";
}

bool Scaler :: shrinkSurface(SDL_Surface* const pSrcSurface, SDL_Surface* const pDstSurface)
{
	int x, y, dx, dy, sgap, dgap, ra, ga, ba, aa;
	int n_average;
	int xFactor = static_cast<int>(1 / xScaleFactor);
	int yFactor = static_cast<int>(1 / yScaleFactor);
	SDL_Color *sp, *osp, *oosp;
	SDL_Color *dp;

	assert(pSrcSurface);
	assert(pDstSurface);

#ifdef VERBOSE
	LDebug << "Scaler :: shrinkSurface";
#endif

	// Averaging integer shrink (code from the SDL_gfx _shrinkSurfaceRGBA function)

	// Precalculate division factor
	n_average = xFactor*yFactor;

	// Scan destination
	sp = (SDL_Color*) pSrcSurface->pixels;
	sgap = pSrcSurface->pitch - pSrcSurface->w * 4;

	dp = (SDL_Color *) pDstSurface->pixels;
	dgap = pDstSurface->pitch - pDstSurface->w * 4;

	for (y = 0; y < pDstSurface->h; y++) 
	{
		osp=sp;
		for (x = 0; x < pDstSurface->w; x++) 
		{
			/* Trace out source box and accumulate */
			oosp=sp;
			ra=ga=ba=aa=0;
			for (dy=0; dy < yFactor ; dy++) 
			{
				for (dx=0; dx < xFactor ; dx++) 
				{
					ra += sp->r;
					ga += sp->g;
					ba += sp->b;
					aa += sp->unused;

					sp++;
				} 
			
				/* src dx loop */
				sp = (SDL_Color*)((Uint8*)sp + (pSrcSurface->pitch - 4 * xFactor)); // next y
			}
			
			/* src dy loop */

			/* next box-x */
			sp = (SDL_Color*)((Uint8*)oosp + 4 * xFactor);

			/* Store result in destination */
			dp->r = ra / n_average;
			dp->g = ga / n_average;
			dp->b = ba / n_average;
			dp->unused = aa / n_average;

			// Advance destination pointer 
			dp++;
		} 
		/* dst x loop */

		/* next box-y */
		sp = (SDL_Color *)((Uint8*)osp + pSrcSurface->pitch * yFactor);
		
		// Advance destination pointers 
		dp = (SDL_Color*) ((Uint8 *) dp + dgap);
	} 
	/* dst y loop */

	return true;
}

bool Scaler :: zoomSurface(SDL_Surface* const pSrcSurface, SDL_Surface* const pDstSurface)
{
	int x, y, sx, sy, *sax, *say, *csax, *csay, csx, csy, ex, ey, t1, t2, sstep, lx, ly;
	SDL_Color *c00, *c01, *c10, *c11;
	SDL_Color *sp, *csp, *dp;
	int dgap;

	assert(pSrcSurface);
	assert(pDstSurface);

#ifdef VERBOSE
	LDebug << "Scaler :: zoomSurface";
#endif

	// Variable setup 

	// For interpolation: assume source dimension is one pixel 
	// smaller to avoid overflow on right and bottom edge.     
	sx = (int) (65536.0 * (float) (pSrcSurface->w - 1) / (float) pDstSurface->w);
	sy = (int) (65536.0 * (float) (pSrcSurface->h - 1) / (float) pDstSurface->h);
	
	// Allocate memory for row increments 
	if ((sax = (int *) malloc((pDstSurface->w + 1) * sizeof(Uint32))) == NULL) 
	{
		LError << "Fail to allocate memory to do the zoom transformation (x)";
		return false;
	}
	if ((say = (int *) malloc((pDstSurface->h + 1) * sizeof(Uint32))) == NULL) 
	{
		free(sax);
		LError << "Fail to allocate memory to do the zoom transformation (y)";
		return false;
	}

	// Precalculate row increments 
	sp = csp = (SDL_Color*) pSrcSurface->pixels;
	dp = (SDL_Color*) pDstSurface->pixels;

	csx = 0;
	csax = sax;
	for (x = 0; x <= pDstSurface->w; x++) 
	{
		*csax = csx;
		csax++;
		csx &= 0xffff;
		csx += sx;
	}

	csy = 0;
	csay = say;
	for (y = 0; y <= pDstSurface->h; y++) 
	{
		*csay = csy;
		csay++;
		csy &= 0xffff;
		csy += sy;
	}

	dgap = pDstSurface->pitch - pDstSurface->w * 4;

	// Scan destination 
	ly = 0;
	csay = say;
	for (y = 0; y < pDstSurface->h; y++) 
	{
		// Setup color source pointers 
		c00 = csp;	    
		c01 = csp;
		c01++;	    
		c10 = (SDL_Color*) ((Uint8 *) csp + pSrcSurface->pitch);
		c11 = c10;
		c11++;
		csax = sax;
		
		lx = 0;

		for (x = 0; x < pDstSurface->w; x++) 
		{
			// Interpolate colors 
			ex = (*csax & 0xffff);
			ey = (*csay & 0xffff);
			t1 = ((((c01->r - c00->r) * ex) >> 16) + c00->r) & 0xff;
			t2 = ((((c11->r - c10->r) * ex) >> 16) + c10->r) & 0xff;
			dp->r = (((t2 - t1) * ey) >> 16) + t1;
			t1 = ((((c01->g - c00->g) * ex) >> 16) + c00->g) & 0xff;
			t2 = ((((c11->g - c10->g) * ex) >> 16) + c10->g) & 0xff;
			dp->g = (((t2 - t1) * ey) >> 16) + t1;
			t1 = ((((c01->b - c00->b) * ex) >> 16) + c00->b) & 0xff;
			t2 = ((((c11->b - c10->b) * ex) >> 16) + c10->b) & 0xff;
			dp->b = (((t2 - t1) * ey) >> 16) + t1;
			t1 = ((((c01->unused - c00->unused) * ex) >> 16) + c00->unused) & 0xff;
			t2 = ((((c11->unused - c10->unused) * ex) >> 16) + c10->unused) & 0xff;
			dp->unused = (((t2 - t1) * ey) >> 16) + t1;

			// Advance source pointers 
			csax++;
			sstep = (*csax >> 16);
			lx += sstep;
			if (lx >= pSrcSurface->w)
			{
				sstep = 0;
			}

			c00 += sstep;
			c01 += sstep;
			c10 += sstep;
			c11 += sstep;

			// Advance destination pointer 
			dp++;
		}

		// Advance source pointer 
		csay++;
		sstep = (*csay >> 16);
		ly += sstep;
		if (ly >= pSrcSurface->h)
		{
			sstep = 0;
		}

		sstep *= pSrcSurface->pitch;

		csp = (SDL_Color*) ((Uint8 *) csp + sstep);

		/*
		* Advance destination pointers 
		*/
		dp = (SDL_Color*) ((Uint8 *) dp + dgap);
	}

	/*
	* Remove temp arrays 
	*/
	free(sax);
	free(say);

	return true;
}

SDL_Surface* Scaler :: scale(SDL_Surface* const pSrcSurface)
{
	SDL_Surface* pTmpSrcSurface = NULL;
	SDL_Surface* pDstSurface = NULL;
	unsigned int dstWidth = static_cast<unsigned int>(pSrcSurface->w * xScaleFactor);
	unsigned int dstHeight = static_cast<unsigned int>(pSrcSurface->h * yScaleFactor);
	bool isTransformed = false;
	bool hasTmpSrcSurface = false;

#ifdef VERBOSE
	LDebug << "Scaler :: scale (Dst:" << dstWidth << "x" << dstHeight << ")";
#endif

	assert(pSrcSurface);
	assert(pSrcSurface->format->BitsPerPixel != 8);	// I am not handling 8 bit surface

	if ( xScaleFactor == 1 && yScaleFactor == 1 )
	{
		// Nothing to do, we have the correct size
		pDstSurface = SDL_CreateRGBSurface(SDL_HWSURFACE, pSrcSurface->w, pSrcSurface->h, pSrcSurface->format->BitsPerPixel, pSrcSurface->format->Rmask, pSrcSurface->format->Gmask, pSrcSurface->format->Bmask, pSrcSurface->format->Amask);
		if ( pDstSurface == NULL )
		{
			LError << "Fail to create the destination surface based on the source";
			return NULL;
		}

		// Silly copy
		// HACK ... for unknown reason the SDL_BlitSurface doesn't copy the alpha channel of the source ...
		// Moreover ... the memcpy is maybe quicker
		// SDL_BlitSurface(pSrcSurface, NULL, pDstSurface, NULL);
		memcpy(pDstSurface->pixels,pSrcSurface->pixels,pSrcSurface->format->BitsPerPixel/8 * pSrcSurface->w * pSrcSurface->h);

		return pDstSurface;
	}

	// In case that my surface have a non 32 bits format ... I transform it to a 32 bits surface
	if ( pSrcSurface->format->BitsPerPixel != 32 )
	{
		pTmpSrcSurface = SDL_CreateRGBSurface(SDL_HWSURFACE, pSrcSurface->w, pSrcSurface->h, 32,
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
												0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000
#else
												0xff000000,  0x00ff0000, 0x0000ff00, 0x000000ff
#endif
												);

		if ( pTmpSrcSurface == NULL )
		{
			LError << "Fail to create the temporary source surface for scaling, when we don't have a native 32bits surface";
			return NULL;
		}

		// Silly copy
		SDL_BlitSurface(pSrcSurface, NULL, pTmpSrcSurface, NULL);

		hasTmpSrcSurface = true;
	}
	else
	{
		// We are using the source directly
		pTmpSrcSurface = pSrcSurface;

		hasTmpSrcSurface = false;
	}

	pDstSurface = SDL_CreateRGBSurface(SDL_HWSURFACE, dstWidth, dstHeight, 32, pSrcSurface->format->Rmask, pSrcSurface->format->Gmask, pSrcSurface->format->Bmask, pSrcSurface->format->Amask);
	if ( pDstSurface == NULL )
	{
		LError << "Fail to create the new surface with SDL_CreateRGBSurface";
		return NULL;
	}

	// Lock the surface
	if ( SDL_MUSTLOCK(pSrcSurface) )
	{
		SDL_LockSurface(pSrcSurface);
	}

	// Do the transformation
	if ( xScaleFactor < 1 && yScaleFactor < 1 )
	{
		isTransformed = shrinkSurface(pTmpSrcSurface,pDstSurface);
	}
	else if ( xScaleFactor > 1 && yScaleFactor > 1 )
	{
		isTransformed = zoomSurface(pTmpSrcSurface,pDstSurface);
	}
	else
	{
		LDebug << "Factors: (" << xScaleFactor << ";" << yScaleFactor;
		LDebug << "Assert reached because we are in a case that the transformation needs both operation... ...not implemented...";
		assert(0);
	}

	if ( isTransformed == false )
	{
		LWarning << "Fail to scale the surface!";
		return NULL;
	}

	// Turn on source-alpha support
	SDL_SetAlpha(pDstSurface, SDL_SRCALPHA, 255);


	// Unlock the surface
	if ( SDL_MUSTLOCK(pSrcSurface) )
	{
		SDL_UnlockSurface(pSrcSurface);
	}

	// Because, we have created a temporary source (in 32 bits format)
	if ( hasTmpSrcSurface )
	{
		// We have to free it
		SDL_FreeSurface(pTmpSrcSurface);
	}

	return pDstSurface;
}
