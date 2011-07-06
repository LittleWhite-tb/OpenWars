#ifndef __GAMEENGINE_H__
#define __GAMEENGINE_H__

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

#include "Engine.h"

#include <vector>

#include "../Types/Vec2.h"

class MapGame;
class Cursor;
class Camera;

struct MenuView;
class MenuBox;
class ConstructBox;

class GameEngine : public Engine
{
	enum GameState
	{
		GS_VISU,
		GS_FACTORY,
		GS_PORT,
		GS_AIRPORT,
		GS_SELECT,
		GS_MENU,
        
        GS_MOVE
	};

private:

	MapGame* pMap;				/*!< The map to use */
	Cursor* pC;					/*!< The cursor */
	Camera* pCam;				/*!< The camera */

	// UI
	ConstructBox* pCBFactory;	/*!< Construct box for factories */
	ConstructBox* pCBPort;		/*!< Construct box for ports */
	ConstructBox* pCBAirport;	/*!< Construct box for airports */
    
    std::vector<MenuView*> menuEntries;  /*!< Entries in the menu */
    std::vector<MenuView*> unitMenuEntries; /*!< Entries for unit selection */

	MenuBox* pMBMenu;				/*!< menu for the user */

	GameState gState;			/*!< Actual state of the game */
    UVec2 selectedUnitPosition; /*!< Position of the unit selected (the one to move or to control) */

	bool m_userQuit;			/*!< If the user wants to quit, this variable will be true */


	bool load(void);

public:
	GameEngine(NE::NEngine* const pNE);
	~GameEngine();

	bool init(void);

	bool load(const std::string& mapName);

	bool run(void);
};

/*! \class GameEngine GameEngine.h "Game/GameEngine.h"
 *  \brief Engine for the game
 *
 * Manage all the game main loop by using states
 */

/*! \fn bool GameEngine::load(void)
 * \brief Load the map, cursor, camera with the associated sprites
 * Will load all needed to set the engine. After you can run the engine.
 * The engine has to be inited.
 * \return true if all goes fine
 */

/*! \fn GameEngine::GameEngine(NE::NEngine* const pNE)
 * \param pNE pointer of the Native Engine to user
 */

/*! \fn GameEngine::~GameEngine()
 */

/*! \fn bool GameEngine::init()
 * \brief Init the Game Engine
 * \return true if all goes right
 */

/*! \fn bool GameEngine::load(const std::string& mapName)
 * \brief load the Game Engine
 * \param mapName the name of the map to load
 * \return true if all goes right
 */

/*! \fn bool GameEngine::run(void)
 * \brief Start the game main loop
 * \return true if all goes fine
 */

#endif
