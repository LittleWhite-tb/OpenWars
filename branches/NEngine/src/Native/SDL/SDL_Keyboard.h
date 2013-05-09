#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

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

#include "NEngine/InputManager.h"
#include "NEngine/Input.h"

namespace NE
{
    class SDL_Keyboard : public Input
    {
    private:
            int m_nbKeys;                     /*!< The number of keys repertoried in the array */
            unsigned char* m_pKeys;            /*!< Array of keys state */

            unsigned char isKey(unsigned int key);

    public:
            SDL_Keyboard(void);
            ~SDL_Keyboard(void);

            NE::InputManager::ArrowsDirection getDirectionsPressed(void)const;

            bool needEscape(void);

            NE::InputManager::Buttons getButtonsState(void);

            void update(void);
    };
}

/*! \class NE::SDL_Keyboard SDL_Keyboard.h "NEngine/Native/SDL/SDL_Keyboard.h"
 *  \brief Handle the pressed keys
 *
 * Can check the following:
 *              - If the escape key is pressed
 *              - Which direction is pressed ( by checking the arrows keys )
 */

/*! \fn unsigned char NE::SDL_Keyboard::isKey(unsigned int key)
 * \brief Check the specified key
 * \param key the key to check
 * \return 0 if the key is not pressed
 */

/*! \fn NE::SDL_Keyboard::SDL_Keyboard(void)
 * \brief Basic constructor
 * Call the update function to have an array ready
 */

/*! \fn NE::SDL_Keyboard::~SDL_Keyboard(void)
 * \brief Basic destructor
 * Do nothing because the array get is an internal SDL array
 */

/*! \fn InputManager::ArrowsDirection NE::SDL_Keyboard::getDirectionsPressed(void)const
 * \brief Check which direction the user wants to go
 * The function is checking the arrow keys and determine which direction the user wants to go. The check allows diagonals directions.
 * \return the direction
 */

/*! \fn bool NE::SDL_Keyboard::needEscape(void)
 * \brief Check if the user pressed the keys to escape
 * This function is checking the escape kee
 * \return true if the program should escape
 */

/*! \fn InputManager::Buttons NE::SDL_Keyboard::getButtonsState(void)
 */

/*! \fn void NE::SDL_Keyboard::update(void)
 * \brief Update the keys array
 */

#endif
