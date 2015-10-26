#ifndef __GAMESTATE_H__
#define __GAMESTATE_H__

#ifndef DOXYGEN_IGNORE_TAG
/**
OpenAWars is an open turn by turn strategic game similar to Advance Wars (c)
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

website: https://github.com/LittleWhite-tb/OpenWars
e-mail: lw.demoscene@gmail.com
**/
#endif

#include "NEngine/InputManager.h"

namespace NE { class NEngine; }
namespace NE { class Renderer; }

class GameState
{
private:

public:
	virtual ~GameState() {};

	virtual bool load(NE::NEngine* pNE)=0;
	virtual bool draw(NE::Renderer* pRenderer, unsigned int time)=0;
	virtual bool update(NE::InputManager::ArrowsDirection direction, NE::InputManager::Buttons buttons, unsigned int time)=0;
};

/*! \class GameState GameState.h "Game/GameState.h"
 *  \brief Game state
 *	The game is following various states as the game, menus, editor ...
 *	This class is the base of all the states
 */

/*! \fn GameState :: ~GameState()
 */

/*! \fn virtual bool GameState::load(NE::NEngine* pNE)=0
 *	\brief load the state in memory
 *	\param pNE a pointer to the NEngine
 *	\return true if all goes right
 */

/*! \fn virtual bool GameState::draw(NE::Renderer* pRenderer, unsigned int time)=0
 *	\brief draw the contents of the state on screen
 *	\param pRenderer a pointer to the Renderer
 *	\param time the actual time of game
 *	\return true if all goes right
 */

/*! \fn virtual bool GameState::update(NE::InputManager::ArrowsDirection direction, NE::InputManager::Buttons buttons, unsigned int time)=0
 *	\brief update the contents of the state
 *	\param direction the direction pressed
 *	\param buttons the buttons pressed
 *	\param time the actual time of game
 *	\return true if all goes right
 */

#endif
