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

#include "SDL_Keyboard.h"

#include <SDL/SDL.h>

#include <cassert>

#include "NEngine/NEngine.h"

NE::SDL_Keyboard :: SDL_Keyboard(void):Input(),m_pKeys(NULL)
{
    NE::NEngine::logger().log(NE::LL_Debug,"Keyboard created");

    this->update(); // We directly update the keys array to have a valid array in any cases
}

NE::SDL_Keyboard :: ~SDL_Keyboard(void)
{
    // The pointer doesn't have to be freed because it's SDL internal array

    NE::NEngine::logger().log(NE::LL_Debug,"Keyboard deleted");
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

NE::InputManager::Buttons NE::SDL_Keyboard :: getButtonsState(void)
{
	InputManager::Buttons buttonPressed = 0;

	if ( m_pKeys[SDLK_q] )
	{
		buttonPressed |= InputManager::INPUT_A;
	}
	if ( m_pKeys[SDLK_w] )
	{
		buttonPressed |= InputManager::INPUT_B;
	}
	if ( m_pKeys[SDLK_a] )
	{
		buttonPressed |= InputManager::INPUT_X;
	}
	if ( m_pKeys[SDLK_s] )
	{
		buttonPressed |= InputManager::INPUT_Y;
	}
	if ( m_pKeys[SDLK_z] )
	{
		buttonPressed |= InputManager::INPUT_START;
	}
	if ( m_pKeys[SDLK_x] )
	{
		buttonPressed |= InputManager::INPUT_SELECT;
	}
	if ( m_pKeys[SDLK_KP_MINUS] )
	{
		buttonPressed |= InputManager::INPUT_VOLUMEDOWN;
	}
	if ( m_pKeys[SDLK_KP_PLUS] )
	{
		buttonPressed |= InputManager::INPUT_VOLUMEUP;
	}

	return buttonPressed;
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
        NE::NEngine::logger().log(NE::LL_Debug,"Keyboard :: update");
#endif

        SDL_PumpEvents();
        m_pKeys = SDL_GetKeyState(&nbKeys);

        this->m_nbKeys = nbKeys;
}
