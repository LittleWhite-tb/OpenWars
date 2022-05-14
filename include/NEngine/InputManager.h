#ifndef __INPUTMANAGER_H__
#define __INPUTMANAGER_H__

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

#include <vector>

namespace NE
{
	class Input;

	// Unified (maybe limited) interface for all controllers
	class InputManager
	{
	public:

		typedef int ArrowsDirection;                    /*!< Direction to go */
		typedef int Button;                            /*!< Buttons pressed */

		// Bit field definition for arrows direction
		static const ArrowsDirection AD_UP = 1;         /*!< Up Direction */
		static const ArrowsDirection AD_UPRIGHT = 3;    /*!< Up and Right Direction */
		static const ArrowsDirection AD_RIGHT = 2;      /*!< Right Direction */
		static const ArrowsDirection AD_RIGHTDOWN = 6;  /*!< Right and Down Direction */
		static const ArrowsDirection AD_DOWN = 4;       /*!< Down Direction */
		static const ArrowsDirection AD_DOWNLEFT = 12;  /*!< Down and Left Direction */
		static const ArrowsDirection AD_LEFT = 8;       /*!< Left Direction */
		static const ArrowsDirection AD_LEFTUP = 9;     /*!< Left and Up Direction */
		static const ArrowsDirection AD_NONE = 0;       /*!< No direction */

		// Bit Field definition
		static const Button INPUT_A = 0;               /*!< A button */
		static const Button INPUT_B = 1;               /*!< B button */
		static const Button INPUT_X = 2;               /*!< X button */
		static const Button INPUT_Y = 3;               /*!< Y button */
		static const Button INPUT_L = 4;              /*!< L button */
		static const Button INPUT_R = 5;              /*!< R button */
		static const Button INPUT_START = 6;          /*!< Start button */
		static const Button INPUT_SELECT = 7;        /*!< Select button */
		static const Button INPUT_VOLUMEUP = 8;      /*!< Volume UP button (GP2X) */
		static const Button INPUT_VOLUMEDOWN = 9;    /*!< Volume Down button (GP2X) */
		static const Button B_END = INPUT_VOLUMEDOWN + 1;

		enum ButtonState
		{
		    BS_RELEASED = 0,
		    BS_JUSTPRESSED = 1,
		    BS_PRESSED = 2,
		    BS_JUSTRELEASED = 3
		};

	private:

		std::vector<Input*> m_controllers;              /*!< Controllers managed */
		std::vector<std::vector<ButtonState> > m_buttonsStates;    /*!< Buttons states */

	public:

		InputManager(void);
		~InputManager(void);

		void registerController(NE::Input* newController);
		void deleteControllers(void);

		std::size_t numberControllers()const { return m_controllers.size(); }
        void update(void);

		ArrowsDirection getDirectionsPressed(unsigned int controller);
		ButtonState getButtonState(unsigned int controller, Button button);

		bool needEscape(void);
	};
}

/*! \class NE::InputManager InputManager.h "Engine/Controls/InputManager.h"
 *  \brief Managers for the Inputs
 */

/*! \fn virtual NE::InputManager::InputManager()
 */

/*! \fn virtual NE::InputManager::~InputManager()
 */

/*! \fn void NE::InputManager::registerController(Input* newController)
 * \brief registers a new controller
 * \param newController the new controller to register
 */

 /*! \fn void NE::InputManager::deleteControllers(void)
 * \brief remove all registered controllers
 */

/*! \fn NE::InputManager::ArrowsDirection NE::InputManager::getDirectionsPressed(void)
 * \brief Gets the directions
 * \return the directions pressed
 */

/*! \fn NE::InputManager::Buttons NE::InputManager::getButtonsPressed(void)
 * \brief Gets the buttons pressed
 * \return the buttons pressed
 */

/*! \fn bool NE::InputManager::needEscape(void)
 * \brief Get if the escape sequence is pressed
 * \return true if the escape sequenced has been pressed
 */

/*! \fn virtual void NE::InputManager::update(void)=0
 * \brief update the buttons states
 */



#endif
