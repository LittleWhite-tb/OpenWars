#ifndef DOXYGEN_IGNORE_TAG
/**
OpenAWars is an open turn by turn strategic game aiming to recreate the feeling of advance (famicon) wars (c)
Copyright (C) 2010-2011  Alexandre LAURENT

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

#include "SDL_Window.h"

#include <SDL/SDL.h>

#include "NEngine/NEngine.h"
#include "NEngine/Types/Size2.h"

bool NE::SDL_Window::isRedCrossPressed = false;

// Callback called once SDL_Quit event appear
int sdlQuitEventFilter(const SDL_Event* pEvent)
{
    if ( pEvent->type == SDL_QUIT )
    {
        NE::SDL_Window::isRedCrossPressed = true;
    }

    return 0;
}

NE :: SDL_Window :: ~SDL_Window(void)
{
    if ( pNativeWindow != NULL )
    {
        NE::NEngine::logger()->log(NE::LL_Warning,"The window is not properly cleared");
    }
}

unsigned int NE :: SDL_Window :: getFlags(const bool isFullscreen, const bool isOpenGL)const
{
    unsigned int sdlVideoFlags = SDL_DOUBLEBUF | SDL_ANYFORMAT;
    const SDL_VideoInfo* pVideoInfo = SDL_GetVideoInfo();   // The documentation does not descrive a case of this function returning NULL pointer

    NE::NEngine::logger()->log(NE::LL_Debug,"Window :: getFlags (%d;%d)",isFullscreen,isOpenGL);

    if ( pVideoInfo->hw_available ) // is Hardware surface possible?
    {
        sdlVideoFlags = sdlVideoFlags | SDL_HWSURFACE;
    }
    else
    {
        sdlVideoFlags = sdlVideoFlags | SDL_SWSURFACE;
    }

    if ( isFullscreen )
    {
        // We add the flag for fullscreen
        sdlVideoFlags = sdlVideoFlags | SDL_FULLSCREEN;
    }

    if ( !pVideoInfo->wm_available ) // In case of the platform doesn't have a Window Manager, we go in fullscreen
    {
        sdlVideoFlags = sdlVideoFlags | SDL_FULLSCREEN;
    }

    if ( isOpenGL )
    {
        // We just want to force double buffering when OpenGL is
        SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

        sdlVideoFlags = sdlVideoFlags | SDL_OPENGL;
    }

    return sdlVideoFlags;
}

bool NE :: SDL_Window :: createWindow(const USize2& winSize, const unsigned short bpp, const bool isFullscreen, const std::string& windowName, const std::string& windowIcon, const bool showCursor)
{
    Uint32 sdlVideoFlags = this->getFlags(isFullscreen,false);

    NE::NEngine::logger()->log(NE::LL_Debug,"SDL_Window :: createWindow (%dx%d x %d ; %d)",winSize.width,winSize.height,bpp,isFullscreen);

    pNativeWindow = SDL_SetVideoMode(winSize.width,winSize.height,bpp,sdlVideoFlags);

    if ( pNativeWindow != NULL )
    {
        NE::NEngine::logger()->log(NE::LL_Debug,"Obtained: %dx%d x %d",pNativeWindow->w,pNativeWindow->h,pNativeWindow->format->BitsPerPixel);

        // Set additionnal settings
        SDL_WM_SetCaption(windowName.c_str(), windowIcon.c_str());
        if ( showCursor )
        {
            SDL_ShowCursor(SDL_ENABLE);
        }
        else
        {
            SDL_ShowCursor(SDL_DISABLE);
        }

        // Installing the event
        SDL_SetEventFilter(&sdlQuitEventFilter);

        return true;
    }

    NE::NEngine::logger()->log(NE::LL_Error,"Error while opening the window");
    return false;
}


void NE :: SDL_Window :: destroyWindow(void)
{
    // Nothing here ... with SDL is done in SDL_Quit (SDL_Engine -> stop())
    pNativeWindow = NULL;
}

USize2 NE :: SDL_Window :: getWindowSize(void)const
{
    return USize2(pNativeWindow->w,pNativeWindow->h);
}

int NE :: SDL_Window :: getBitsPerPixel(void)const
{
    return pNativeWindow->format->BitsPerPixel;
}
