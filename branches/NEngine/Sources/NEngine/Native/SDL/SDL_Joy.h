#ifndef __JOYSTICK_H__
#define __JOYSTICK_H__

#include <SDL/SDL.h>

#include "NEngine/InputManager.h"
#include "NEngine/Input.h"

namespace NE
{
    class SDL_Joy : public Input
    {
    private:
        SDL_Joystick* m_pJoy;
        InputManager::ArrowsDirection m_directions;
        InputManager::Buttons m_buttons;

        void updateDirections();
        void updateButtons();

    public:
        SDL_Joy();
        ~SDL_Joy();

        NE::InputManager::ArrowsDirection getDirectionsPressed(void)const { return m_directions; }
        NE::InputManager::Buttons getButtonsState(void) { return m_buttons; };
        bool needEscape(void);
        void update(void);
    };
}

/*! \class NE::SDL_Joy SDL_Joy.h "NEngine/Native/SDL/SDL_Joy.h"
 *  \brief Handle the joystick
 *
 * Can check the following:
 *              - If a special sequence is pressed (to escape)
 *              - Which direction is pressed
 *              - Which buttons are pressed
 */

/*! \fn NE::SDL_Joy::SDL_Joy(void)
 * \brief Basic constructor
 * Call the update function to have an array ready
 */

/*! \fn NE::SDL_Joy::~SDL_Joy(void)
 * \brief Basic destructor
 * Do nothing because the array get is an internal SDL array
 */

/*! \fn InputManager::ArrowsDirection NE::SDL_Joy::getDirectionsPressed(void)const
 * \brief Check which direction the user wants to go
 * The function is checking the arrow keys and determine which direction the user wants to go. The check allows diagonals directions.
 * \return the direction
 */

/*! \fn bool NE::SDL_Joy::needEscape(void)
 * \brief Check if the user pressed the keys to escape
 * This function is checking the escape kee
 * \return true if the program should escape
 */

/*! \fn InputManager::Buttons NE::SDL_Joy::getButtonsState(void)
 */

/*! \fn void NE::SDL_Joy::update(void)
 * \brief Update the keys array
 */

#endif
