#include "SDL_NThread.h"

#include <SDL/SDL_thread.h>

void NE :: SDL_NThread :: start(void)
{
    pThread = SDL_CreateThread(fct,data);
}

void NE :: SDL_NThread :: stop(void)
{
    if ( pThread != NULL )
    {
        SDL_KillThread(pThread);
        pThread = NULL;
    }
}

void NE :: SDL_NThread :: wait(void)
{
    SDL_WaitThread(pThread, NULL);
}
