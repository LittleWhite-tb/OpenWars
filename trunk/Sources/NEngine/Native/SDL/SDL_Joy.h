#ifndef __JOYSTICK_H__
#define __JOYSTICK_H__

#include <SDL/SDL.h>

#include "../../InputManager.h"
#include "../../Input.h"

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

#endif
