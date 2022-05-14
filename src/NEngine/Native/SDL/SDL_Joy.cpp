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

#include "SDL_Joy.h"

#include <SDL/SDL.h>

#include "NEngine/Input.h"

#include "NEngine/NEngine.h"
#include "NEngine/Exceptions/InputNotFoundException.h"

NE::SDL_Joy :: SDL_Joy():Input(),m_pJoy(SDL_JoystickOpen(0))
{
    if ( m_pJoy == NULL )
    {
        throw InputNotFoundException("SDL Joystick");
    }

    // Desabling the event on the joystick
    SDL_JoystickEventState(SDL_DISABLE);

    NEDebug << "Joystick created\n";
}

NE::SDL_Joy :: ~SDL_Joy()
{
    SDL_JoystickClose(m_pJoy);

    NEDebug << "Joystick deleted\n";
}

bool NE::SDL_Joy :: isPressed(NE::InputManager::Button button)
{
    if ( button == NE::InputManager::INPUT_START &&
         SDL_JoystickGetButton(m_pJoy,8) )
    {
        return true;
    }
    if ( button == NE::InputManager::INPUT_SELECT &&
         SDL_JoystickGetButton(m_pJoy,9) )
    {
        return true;
    }
    if ( button == NE::InputManager::INPUT_R &&
         SDL_JoystickGetButton(m_pJoy,10) )
    {
        return true;
    }
    if ( button == NE::InputManager::INPUT_L &&
         SDL_JoystickGetButton(m_pJoy,11) )
    {
        return true;
    }
    if ( button == NE::InputManager::INPUT_A &&
         SDL_JoystickGetButton(m_pJoy,12) )
    {
        return true;
    }
    if ( button == NE::InputManager::INPUT_B &&
         SDL_JoystickGetButton(m_pJoy,13) )
    {
        return true;
    }
    if ( button == NE::InputManager::INPUT_Y &&
         SDL_JoystickGetButton(m_pJoy,14) )
    {
        return true;
    }
    if ( button == NE::InputManager::INPUT_X &&
         SDL_JoystickGetButton(m_pJoy,15) )
    {
        return true;
    }
    if ( button == NE::InputManager::INPUT_VOLUMEUP &&
         SDL_JoystickGetButton(m_pJoy,16) )
    {
        return true;
    }
    if ( button == NE::InputManager::INPUT_VOLUMEDOWN &&
         SDL_JoystickGetButton(m_pJoy,17) )
    {
        return true;
    }

    return false;
}

void NE::SDL_Joy :: updateDirections()
{
    if ( SDL_JoystickGetButton(m_pJoy,0) )
    {
        m_directions = NE::InputManager::AD_UP;
    }
    else if ( SDL_JoystickGetButton(m_pJoy,1) )
    {
        m_directions = NE::InputManager::AD_LEFTUP;
    }
    else if ( SDL_JoystickGetButton(m_pJoy,2) )
    {
        m_directions = NE::InputManager::AD_LEFT;
    }
    else if ( SDL_JoystickGetButton(m_pJoy,3) )
    {
        m_directions = NE::InputManager::AD_DOWNLEFT;
    }
    else if ( SDL_JoystickGetButton(m_pJoy,4) )
    {
        m_directions = NE::InputManager::AD_DOWN;
    }
    else if ( SDL_JoystickGetButton(m_pJoy,5) )
    {
        m_directions = NE::InputManager::AD_RIGHTDOWN;
    }
    else if ( SDL_JoystickGetButton(m_pJoy,6) )
    {
        m_directions = NE::InputManager::AD_RIGHT;
    }
    else if ( SDL_JoystickGetButton(m_pJoy,7) )
    {
        m_directions = NE::InputManager::AD_UPRIGHT;
    }
    else
    {
        m_directions = NE::InputManager::AD_NONE;
    }
}

bool NE::SDL_Joy :: needEscape(void)
{
    if ( this->isPressed(NE::InputManager::INPUT_R) &&
         this->isPressed(NE::InputManager::INPUT_L) &&
         this->isPressed(NE::InputManager::INPUT_START))
    {
        return true;
    }

    return false;
}

void NE::SDL_Joy :: update(void)
{
    // Updating the joystick state
    SDL_JoystickUpdate();
    updateDirections();
}
