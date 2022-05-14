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

#include "SDL_Keyboard.h"

#include <SDL/SDL.h>

#include <cassert>

#include "NEngine/NEngine.h"

NE::SDL_Keyboard :: SDL_Keyboard(void):Input(),m_pKeys(NULL)
{
    NEDebug << "Keyboard created\n";

    this->update(); // We directly update the keys array to have a valid array in any cases
}

NE::SDL_Keyboard :: ~SDL_Keyboard(void)
{
    // The pointer doesn't have to be freed because it's SDL internal array

    NEDebug << "Keyboard deleted\n";
}

NE::InputManager::ArrowsDirection NE::SDL_Keyboard :: getDirectionsPressed(void)const
{
        // Silly way to check it ... ( ToDo: Improve if possible )
        // Some cases are hidden, like DOWN and UP ... but I don't mind if the user is a bit silly ... :p
        if ( m_pKeys[SDLK_UP] )
        {
                if ( m_pKeys[SDLK_RIGHT] )
                {
                        return InputManager::AD_UPRIGHT;
                }
                else if ( m_pKeys[SDLK_LEFT] )
                {
                        return InputManager::AD_LEFTUP;
                }

                return InputManager::AD_UP;
        }

        if ( m_pKeys[SDLK_DOWN] )
        {
                if ( m_pKeys[SDLK_RIGHT] )
                {
                        return InputManager::AD_RIGHTDOWN;
                }
                else if ( m_pKeys[SDLK_LEFT] )
                {
                        return InputManager::AD_DOWNLEFT;
                }

                return InputManager::AD_DOWN;
        }

        if ( m_pKeys[SDLK_LEFT] )
        {
                return InputManager::AD_LEFT;
        }
        else if ( m_pKeys[SDLK_RIGHT] )
        {
                return InputManager::AD_RIGHT;
        }

        return InputManager::AD_NONE;
}

bool NE::SDL_Keyboard::isPressed(NE::InputManager::Button button)
{
    if ( button == InputManager::INPUT_A && m_pKeys[SDLK_q] )
    {
        return true;
    }
    if ( button == InputManager::INPUT_B && m_pKeys[SDLK_w] )
    {
        return true;
    }
    if ( button == InputManager::INPUT_X && m_pKeys[SDLK_a] )
    {
        return true;
    }
    if ( button == InputManager::INPUT_Y && m_pKeys[SDLK_s] )
    {
        return true;
    }
    if ( button == InputManager::INPUT_START && m_pKeys[SDLK_z] )
    {
        return true;
    }
    if ( button == InputManager::INPUT_SELECT && m_pKeys[SDLK_x] )
    {
        return true;
    }
    if ( button == InputManager::INPUT_VOLUMEDOWN && m_pKeys[SDLK_KP_MINUS] )
    {
        return true;
    }
    if ( button == InputManager::INPUT_VOLUMEUP && m_pKeys[SDLK_KP_PLUS] )
    {
        return true;
    }

    return false;
}

unsigned char NE::SDL_Keyboard :: isKey(unsigned int key)
{
        assert(static_cast<int>(key) < m_nbKeys);

        return m_pKeys[key];
}

bool NE::SDL_Keyboard :: needEscape(void)
{
	return isKey(SDLK_ESCAPE) == 1;
}

void NE::SDL_Keyboard :: update(void)
{
        int nbKeys = 0;

#ifdef VERBOSE
        NEDebug << "Keyboard :: update\n";
#endif

        SDL_PumpEvents();
        m_pKeys = SDL_GetKeyState(&nbKeys);

        this->m_nbKeys = nbKeys;
}
