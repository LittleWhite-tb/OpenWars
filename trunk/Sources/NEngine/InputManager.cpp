#include "InputManager.h"
#include "Input.h"
#include <typeinfo>
#include <NEngine/Utils/Logger.h>

NE::InputManager :: InputManager()
{
	LDebug << "Input Manager inited";
}

NE::InputManager :: ~InputManager(void)
{
	this->deleteControllers();

	LDebug << "Input Manager destructed";
}

void NE::InputManager :: registerController(Input* newController)
{
	m_controllers.push_back(newController);

	LDebug << "Registered -> " << typeid(newController).name();
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
