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
