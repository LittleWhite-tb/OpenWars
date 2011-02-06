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

		typedef int ArrowsDirection;                    /*!< Direction to go */
		typedef int Buttons;                            /*!< Buttons pressed */

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
		static const Buttons INPUT_NONE = 0;            /*!< No button pressed */
		static const Buttons INPUT_A = 1;               /*!< A button */
		static const Buttons INPUT_B = 2;               /*!< B button */
		static const Buttons INPUT_X = 4;               /*!< X button */
		static const Buttons INPUT_Y = 8;               /*!< Y button */
		static const Buttons INPUT_L = 16;              /*!< L button */
		static const Buttons INPUT_R = 32;              /*!< R button */
		static const Buttons INPUT_START = 64;          /*!< Start button */
		static const Buttons INPUT_SELECT = 128;        /*!< Select button */
		static const Buttons INPUT_VOLUMEUP = 256;      /*!< Volume UP button (GP2X) */
		static const Buttons INPUT_VOLUMEDOWN = 512;    /*!< Volume Down button (GP2X) */

	private:

		std::vector<Input*> m_controllers;              /*!< Controllers managed */

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
