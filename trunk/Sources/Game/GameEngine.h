#ifndef __GAMEENGINE_H__
#define __GAMEENGINE_H__

#ifndef DOXYGEN_IGNORE_TAG
/**
OpenAWars is an open turn by turn strategic game aiming to recreate the feeling of advance (famicon) wars (c)
Copyright (C) 2010  Alexandre LAURENT

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

class Map;
class Cursor;
class Camera;

class ConstructBox;
class MenuBox;

class GameEngine : public Engine
{
	enum GameState
	{
		GS_VISU,
		GS_FACTORY,
		GS_PORT,
		GS_AIRPORT,
		GS_SELECT,
		GS_MENU
	};

private:

	Map* pMap;					/*!< The map to use */
	Cursor* pC;					/*!< The cursor */
	Camera* pCam;				/*!< The camera */

	// UI
	ConstructBox* pCBFactory;	/*!< Construct box for factories */
	ConstructBox* pCBPort;		/*!< Construct box for ports */
	ConstructBox* pCBAirport;	/*!< Construct box for airports */

	MenuBox* pMBMenu;				/*!< menu for the user */

	GameState gState;			/*!< Actual state of the game */

	//! Load the map, cursor, camera with the associated sprites
	/*!
		Will load all needed to set the engine. After you can run the engine.
		The engine has to be inited.
		\return true if all goes fine
	*/
	bool load(void);

public:

	//! Basic constructor
	/*!
	*/
	GameEngine();

	//! Basic destructor
	/*!
	*/
	~GameEngine();

	//! Init the Game Engine
	/*!
	  \param pWin the window to use for the game
	  \param rAPI the API to start for rendering
	  \return true if all goes right
	*/
	bool init(const Window* pWin, const RenderingAPI rAPI);
	
	//! load the Game Engine
	/*!
	  \param mapName the name of the map to load
	  \return true if all goes right
	*/
	bool load(const std::string& mapName);

	//! Start the game main loop
	/*!
		\return true if all goes fine
	*/
	bool run(void);
};

/*! \class GameEngine GameEngine.h "Game/GameEngine.h"
 *  \brief Engine for the game
 *
 * Manage all the game main loop by using states
 */

#endif