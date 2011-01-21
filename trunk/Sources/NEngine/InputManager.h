#ifndef __INPUTMANAGER_H__
#define __INPUTMANAGER_H__

#include <vector>

namespace NE
{
	class Input;

	// Unified (maybe limited) interface for all controllers
	class InputManager
	{
	public:

		typedef int ArrowsDirection;
		typedef int Buttons;

		// Bit field definition for arrows direction
		static const ArrowsDirection AD_UP = 1;
		static const ArrowsDirection AD_UPRIGHT = 3;
		static const ArrowsDirection AD_RIGHT = 2;
		static const ArrowsDirection AD_RIGHTDOWN = 6;
		static const ArrowsDirection AD_DOWN = 4;
		static const ArrowsDirection AD_DOWNLEFT = 12;
		static const ArrowsDirection AD_LEFT = 8;
		static const ArrowsDirection AD_LEFTUP = 9;
		static const ArrowsDirection AD_NONE = 0;

		// Bit Field definition
		static const Buttons INPUT_NONE = 0;
		static const Buttons INPUT_A = 1;
		static const Buttons INPUT_B = 2;
		static const Buttons INPUT_X = 4;
		static const Buttons INPUT_Y = 8;
		static const Buttons INPUT_L = 16;
		static const Buttons INPUT_R = 32;
		static const Buttons INPUT_START = 64;
		static const Buttons INPUT_SELECT = 128;
		static const Buttons INPUT_VOLUMEUP = 256;
		static const Buttons INPUT_VOLUMEDOWN = 512;

	private:

		std::vector<Input*> m_controllers;

	public:

		InputManager(void);
		~InputManager(void);

		void registerController(NE::Input* newController);
		void deleteControllers(void);

		ArrowsDirection getDirectionsPressed(void);
		Buttons getButtonsPressed(void);
		bool needEscape(void);
		void update(void);
	};
}

/*! \class InputManager InputManager.h "Engine/Controls/InputManager.h"
 *  \brief Managers for the Inputs
 */

/* \fn virtual InputManager::InputManager()
 */

/* \fn virtual InputManager::~InputManager()
 */

/* \fn void InputManager::registerController(Input* newController)
 * \brief registers a new controller
 * \param newController the new controller to register
 */

/* \fn virtual InputManager::ArrowsDirection InputManager::getDirectionsPressed(void)const=0
 * \brief Gets the directions
 * \return the directions pressed
 */

/* \fn virtual InputManager::Buttons InputManager::getButtonsState(void)=0
 * \brief Gets the buttons pressed
 * \return the buttons pressed
 */

/* \fn virtual bool InputManager::needEscape(void)=0
 * \brief Get if the escape sequence is pressed
 * \return true if the escape sequenced has been pressed
 */

/* \fn virtual void InputManager::update(void)=0
 * \brief update the buttons states
 */



#endif
