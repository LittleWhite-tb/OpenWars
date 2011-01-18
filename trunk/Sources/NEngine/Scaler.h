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

#include "../Types/Vec2.h"

namespace NE
{
    class Sprite;
    
    class Scaler
    {        
    protected:

        int scaleFactor;		/*!< the scaling factor */
        
        void* getNativeSurface(const Sprite& sprite)const;

        virtual NE::Sprite* shrinkSurface(Sprite* pSrcSurface)const =0;
        virtual NE::Sprite* zoomSurface(Sprite* pSrcSurface)const=0;

    public:
        Scaler(const int scaleFactor = 1):scaleFactor(scaleFactor) {} 
        virtual ~Scaler(void) {}
        
        float getScaleFactor(void);
        void setScaleFactor(const int newScaleFactor) { this->scaleFactor = newScaleFactor; }
        
        Sprite* scale(Sprite* const pSrcSprite);
    };
}

// \warning the scale doesn't delete the source
// \warning if nothing to be done ... returning the source
// \warning if failed returning NULL

#endif
