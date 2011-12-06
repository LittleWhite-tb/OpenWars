#ifndef __GAME_H__
#define __GAME_H__

#ifndef DOXYGEN_IGNORE_TAG
/**
OpenAWars is an open turn by turn strategic game aiming to recreate the feeling of advance (famicon) wars (c)
Copyright (C) 2010-2011  Alexandre LAURENT

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

#include <map>
#include <string>

#include "Game/GameState.h"

#include "NEngine/InputManager.h"

#include "Engine/Library.h"
#include "Engine/Theme.h"

#include "Game/GameState/GameObjects/GameInfo.h"
#include "Game/GameState/InGameStates/InGameState.h"

namespace NE { class NEngine; }
namespace NE { class Renderer; }

class Map;
class Camera;
class Cursor;

class Game : public GameState
{
private:

	Map* pMap;
	Camera* pCamera;
	Cursor* pCursor;					/*!< The cursor */
	GameInfo gameInfo;

	IGState igState;
	std::map<IGState, InGameState*> states;

public:
	Game();
	~Game();

	bool load(NE::NEngine* pNE);
	bool loadMap(const Library<Theme>* const pThemes, const std::string& name);
	
	bool draw(NE::Renderer* pRenderer, unsigned int time);
	bool update(NE::InputManager::ArrowsDirection direction, NE::InputManager::Buttons buttons, unsigned int time);
};

/*! \class Game Game.h "Game/GameState/Game.h"
 *  \brief Game state displaying the game
 */

/*! \enum Game::GState Game.h "Game/GameState/Game.h"
 *	\brief enum to know in which state the game is
 */

/*! \fn Game::Game()
 */

/*! \fn Game::~Game()
 */

/*! \fn bool Game::loadMap(const Library<Theme>* const pThemes, const std::string& name)
 * \brief load a map in the game
 *	\param pThemes the library of themes available (one will be used by the Map)
 * \param name the name of the map to load
 * \return true if all goes right
 */

#endif
