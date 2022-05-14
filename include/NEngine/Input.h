#ifndef __INPUT_H__
#define __INPUT_H__

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

#include "InputManager.h"

namespace NE
{
	class Input
	{
	public:
		virtual ~Input() {};

		virtual NE::InputManager::ArrowsDirection getDirectionsPressed(void)const=0;
		virtual bool isPressed(NE::InputManager::Button button)=0;
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
 * \brief Get the directions
 * \return the directions pressed
 */

/*! \fn virtual bool NE::Input::isPressed(NE::InputManager::Button button)=0
 * \brief Get the actual state (pressed or not) of the button \a button
 * \return true if the button \a button is pressed
 */

/*! \fn virtual bool NE::Input::needEscape(void)=0
 * \brief Get if the escape sequence is pressed
 * \return true if the escape sequenced has been pressed
 */

/*! \fn virtual void NE::Input::update(void)=0
 * \brief update the buttons states
 */

#endif
