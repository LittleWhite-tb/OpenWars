#ifndef DOXYGEN_IGNORE_TAG
/**
NEngine: Native Engine abstracts multimedia libraries such as SDL, SFML, Allegro
Copyright (C) 2010-2015  Alexandre LAURENT

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

website: https://github.com/LittleWhite-tb/NEngine
e-mail: lw.demoscene@gmail.com
**/
#endif

#include "SDL_Semaphore.h"

#include <SDL/SDL_thread.h>

#include <iostream>

#include "NEngine/NEngine.h"
#include "NEngine/Exceptions/ConstructionFailedException.h"

NE::SDL_Semaphore::SDL_Semaphore(const unsigned int initialValue):pSem(SDL_CreateSemaphore(initialValue))
{
    if ( pSem == NULL )
    {
        NEError << "Fail to create semaphore\n";
        throw ConstructionFailedException("SDL_Semaphore");
    }
}

NE :: SDL_Semaphore :: ~SDL_Semaphore(void)
{
    SDL_DestroySemaphore(pSem);
}

void NE :: SDL_Semaphore :: wait(void)
{
    int error = SDL_SemWait(pSem);
    if ( error != 0 )
    {
        NEError << "Fail to wait for the semaphore\n";
    }
}

void NE :: SDL_Semaphore :: post(void)
{
    int error = SDL_SemPost(pSem);

    if ( error != 0 )
    {
        NEError << "Fail to wait for the semaphore\n";
    }
}
