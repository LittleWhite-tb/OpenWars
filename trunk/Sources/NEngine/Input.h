#ifndef __INPUT_H__
#define __INPUT_H__

#include "InputManager.h"

namespace NE
{
	class Input
	{
	public:
		virtual ~Input() {};

		virtual NE::InputManager::ArrowsDirection getDirectionsPressed(void)const=0;
		virtual NE::InputManager::Buttons getButtonsState(void)=0;
		virtual bool needEscape(void)=0;
		virtual void update(void)=0;
	};
}

/*! \class NE::Input Input.h "NEngine/Native/SDL/Input.h"
 *  \brief Interface for the different Input
 */

/*! \fn virtual NE::Input::~Input()
 */

/*! \fn virtual InputManager::ArrowsDirection NE::Input::getDirectionsPressed(void)const=0
 * \brief Gets the directions
 * \return the directions pressed
 */

/*! \fn virtual InputManager::Buttons NE::Input::getButtonsState(void)=0
 * \brief Gets the buttons pressed
 * \return the buttons pressed
 */

/*! \fn virtual bool NE::Input::needEscape(void)=0
 * \brief Get if the escape sequence is pressed
 * \return true if the escape sequenced has been pressed
 */

/*! \fn virtual void NE::Input::update(void)=0
 * \brief update the buttons states
 */

#endif
