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

    NE::NEngine::logger().log(NE::LL_Debug,"Joystick created");
}

NE::SDL_Joy :: ~SDL_Joy()
{
    SDL_JoystickClose(m_pJoy);

    NE::NEngine::logger().log(NE::LL_Debug,"Joystick deleted");
}

void NE::SDL_Joy :: updateButtons(void)
{
    m_buttons = NE::InputManager::INPUT_NONE;

    if ( SDL_JoystickGetButton(m_pJoy,8) )
    {
        m_buttons |= NE::InputManager::INPUT_START;
    }
    if ( SDL_JoystickGetButton(m_pJoy,9) )
    {
        m_buttons |= NE::InputManager::INPUT_SELECT;
    }
    if ( SDL_JoystickGetButton(m_pJoy,10) )
    {
        m_buttons |= NE::InputManager::INPUT_R;
    }
    if ( SDL_JoystickGetButton(m_pJoy,11) )
    {
        m_buttons |= NE::InputManager::INPUT_L;
    }
    if ( SDL_JoystickGetButton(m_pJoy,12) )
    {
        m_buttons |= NE::InputManager::INPUT_A;
    }
    if ( SDL_JoystickGetButton(m_pJoy,13) )
    {
        m_buttons |= NE::InputManager::INPUT_B;
    }
    if ( SDL_JoystickGetButton(m_pJoy,14) )
    {
        m_buttons |= NE::InputManager::INPUT_Y;
    }
    if ( SDL_JoystickGetButton(m_pJoy,15) )
    {
        m_buttons |= NE::InputManager::INPUT_X;
    }
    if ( SDL_JoystickGetButton(m_pJoy,16) )
    {
        m_buttons |= NE::InputManager::INPUT_VOLUMEUP;
    }
    if ( SDL_JoystickGetButton(m_pJoy,17) )
    {
        m_buttons |= NE::InputManager::INPUT_VOLUMEDOWN;
    }
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
    NE::InputManager::ArrowsDirection buttons = this->getButtonsState();

    if ( (buttons & NE::InputManager::INPUT_R) == NE::InputManager::INPUT_R &&
        (buttons & NE::InputManager::INPUT_L) == NE::InputManager::INPUT_L &&
        (buttons & NE::InputManager::INPUT_START) == NE::InputManager::INPUT_START )
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
    updateButtons();
}
