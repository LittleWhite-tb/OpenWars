#ifndef DOXYGEN_IGNORE_TAG
/**
OpenAWars is an open turn by turn strategic game aiming to recreate the feeling of advance (famicon) wars (c)
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

website: http://code.google.com/p/openawars/
e-mail: lw.demoscene@gmail.com
**/
#endif

#include "NEngine/InputManager.h"

#include "NEngine/Input.h"

#include <typeinfo>

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

    NEDebug << "Registered -> " << typeid(newController).name() << "\n";
}

void NE::InputManager :: deleteControllers(void)
{
	for(std::vector<Input*>::const_iterator itController = m_controllers.begin() ; itController != m_controllers.end() ; ++itController)
	{
        delete (*itController);
	}

	m_controllers.clear();
}

NE::InputManager::ArrowsDirection NE::InputManager :: getDirectionsPressed()
{
	InputManager::ArrowsDirection directions = 0;

	for(std::vector<Input*>::const_iterator itController = m_controllers.begin() ; itController != m_controllers.end() ; ++itController)
	{
		directions |= (*itController)->getDirectionsPressed();
	}

	return directions;
}

NE::InputManager::Buttons NE::InputManager :: getButtonsPressed()
{
	int buttons = 0;

	for(std::vector<Input*>::const_iterator itController = m_controllers.begin() ; itController != m_controllers.end() ; ++itController)
	{
		buttons |= (*itController)->getButtonsState();
	}

	return buttons;
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
