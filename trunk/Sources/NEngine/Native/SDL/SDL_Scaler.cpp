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

#include "SDL_Scaler.h"

#include <SDL/SDL.h>

#include "../../Sprite.h"
#include "SDL_Sprite.h"

#include "../../Scaler.h"

#include "../../../Types/Colour.h"

#include "../../../Utils/Logger.h"

NE::Sprite* NE :: SDL_Scaler :: shrinkSurface(NE::Sprite* pSrcSurface)const
{    
    // Note: the scaler is negative if we are in this function
    SDL_Surface* pSDLSrcSurface = static_cast<SDL_Surface*>(this->getNativeSurface(*pSrcSurface));
    
    // Check if we have an even size surface
    if ( pSDLSrcSurface->w % 2 != 0 || pSDLSrcSurface->h % 2 != 0 )
    {
        LError << "Non even size surface not supported for shrinking";
        return NULL;
    }
    
    SDL_Surface* pSDLDstSurface = SDL_CreateRGBSurface(SDL_HWSURFACE, pSDLSrcSurface->w / -this->scaleFactor, pSDLSrcSurface->h / -this->scaleFactor, pSDLSrcSurface->format->BitsPerPixel, pSDLSrcSurface->format->Rmask, pSDLSrcSurface->format->Gmask, pSDLSrcSurface->format->Bmask, pSDLSrcSurface->format->Amask);
    if ( pSDLDstSurface == NULL )
    {
        LError << "Fail to create the destination surface based on the source";
        return NULL;
    }
    
    unsigned int* srcPointer = static_cast<unsigned int*>(pSDLSrcSurface->pixels);
    unsigned int* dstPointer = static_cast<unsigned int*>(pSDLDstSurface->pixels);
    
    for ( int y = 0 ; y < pSDLSrcSurface->h ; y+=2)
    {
        for ( int x = 0 ; x < pSDLSrcSurface->w ; x+=2)
        {
            // We have to break down the colour per bits to do the sum of 4 colours (avoiding the overflow)
            Colour c1(*srcPointer);
            Colour c2(*(srcPointer+1));
            Colour c3(*(srcPointer+pSDLSrcSurface->w));
            Colour c4(*(srcPointer+pSDLSrcSurface->w+1));
            Colour finalColour((c1.r + c2.r + c3.r + c4.r)/4,
                                (c1.g + c2.g + c3.g + c4.g)/4,
                                (c1.b + c2.b + c3.b + c4.b)/4,
                                (c1.a + c2.a + c3.a + c4.a)/4);
            
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
            *dstPointer = (finalColour.a << 24) + (finalColour.b << 16) + (finalColour.g << 8) + finalColour.r;
#else
            *dstPointer = (finalColour.r << 24 + (finalColour.g << 16) + (finalColour.b << 8) + finalColour.a;
#endif
            
            srcPointer += 2;
        }
        
        // We jump a line over
        srcPointer += pSDLSrcSurface->w;
    }
    
    return new SDL_Sprite(pSDLDstSurface);
}


NE::Sprite* NE :: SDL_Scaler :: zoomSurface(NE::Sprite* pSrcSurface)const
{
    SDL_Surface* pSDLSrcSurface = static_cast<SDL_Surface*>(this->getNativeSurface(*pSrcSurface));
    SDL_Surface* pSDLDstSurface = SDL_CreateRGBSurface(SDL_HWSURFACE, pSDLSrcSurface->w * this->scaleFactor, pSDLSrcSurface->h * this->scaleFactor, pSDLSrcSurface->format->BitsPerPixel, pSDLSrcSurface->format->Rmask, pSDLSrcSurface->format->Gmask, pSDLSrcSurface->format->Bmask, pSDLSrcSurface->format->Amask);
    if ( pSDLDstSurface == NULL )
    {
        LError << "Fail to create the destination surface based on the source";
        return NULL;
    }
    
    unsigned int* srcPointer = static_cast<unsigned int*>(pSDLSrcSurface->pixels);
    unsigned int* dstPointer = static_cast<unsigned int*>(pSDLDstSurface->pixels);
    
    for ( int y = 0 ; y < pSDLSrcSurface->h ; )
    {
        for ( int scaleFactorCounterY = 0 ; scaleFactorCounterY < scaleFactor ; scaleFactorCounterY++ )
        {
            for ( int x = 0 ; x < pSDLSrcSurface->w ;)
            {
                for ( int scaleFactorCounterX = 0 ; scaleFactorCounterX < scaleFactor ; scaleFactorCounterX++ )
                {
                    *dstPointer = *srcPointer;
                    dstPointer++;
                }
                
                srcPointer++;
            }
            
            srcPointer -= pSDLSrcSurface->w;
        }
        
        srcPointer += pSDLSrcSurface->w;
    }
    
   return new SDL_Sprite(pSDLDstSurface);
}
