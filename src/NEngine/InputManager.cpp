#ifndef DOXYGEN_IGNORE_TAG
/**
NEngine: Native Engine abstracts multimedia libraries such as SDL, SFML, Allegro
Copyright (C) 2010-2013  Alexandre LAURENT

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

#include "NEngine/InputManager.h"

#include "NEngine/Input.h"

#include <typeinfo>
#include <cassert>

#include "NEngine/NEngine.h"

NE::InputManager :: InputManager()
{
    NEDebug << "Input Manager inited\n";
}

NE::InputManager :: ~InputManager(void)
{
	this->deleteControllers();

    NEDebug << "Input Manager destructed\n";
}

void NE::InputManager :: registerController(Input* newController)
{
	m_controllers.push_back(newController);
	m_buttonsStates.push_back(std::vector<ButtonState>(B_END,BS_RELEASED));

    NEDebug << "Registered -> " << typeid(newController).name() << "\n";
}

void NE::InputManager :: deleteControllers(void)
{
	for(std::vector<Input*>::const_iterator itController = m_controllers.begin() ; itController != m_controllers.end() ; ++itController)
	{
        delete (*itController);
	}

	m_controllers.clear();
	m_buttonsStates.clear();
}

NE::InputManager::ArrowsDirection NE::InputManager::getDirectionsPressed(unsigned int controller)
{
    assert(controller < this->numberControllers());

	return m_controllers[controller]->getDirectionsPressed();
}

NE::InputManager::ButtonState NE::InputManager::getButtonState(unsigned int controller, Button button)
{
    assert(controller < this->numberControllers());
    bool buttonPressed = m_controllers[controller]->isPressed(button);

    // TODO: Should this code be placed in update() ?
    if (buttonPressed)
    {
        if (m_buttonsStates[controller][button] == BS_RELEASED ||
            m_buttonsStates[controller][button] == BS_JUSTRELEASED )
        {
            m_buttonsStates[controller][button] = BS_JUSTPRESSED;
        }
        else
        {
            m_buttonsStates[controller][button] = BS_PRESSED;
        }
    }
    else // Released
    {
        if (m_buttonsStates[controller][button] == BS_PRESSED ||
            m_buttonsStates[controller][button] == BS_JUSTPRESSED )
        {
            m_buttonsStates[controller][button] = BS_JUSTRELEASED;
        }
        else
        {
            m_buttonsStates[controller][button] = BS_RELEASED;
        }
    }

    return m_buttonsStates[controller][button];
}

bool NE::InputManager :: needEscape(void)
{
	bool escaping = false;

	for(std::vector<Input*>::const_iterator itController = m_controllers.begin() ; itController != m_controllers.end() ; ++itController)
	{
		escaping |= (*itController)->needEscape();
	}

	return escaping;
}

void NE::InputManager :: update()
{
	for(std::vector<Input*>::const_iterator itController = m_controllers.begin() ; itController != m_controllers.end() ; ++itController)
	{
		(*itController)->update();
	}
}
