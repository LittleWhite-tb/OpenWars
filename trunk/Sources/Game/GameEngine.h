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

#include <string>

#include "Engine/Library.h"
#include "Engine/Theme.h"

namespace NE { class NEngine; }

struct GameOption;
class GameState;

class GameEngine
{
private:
	NE::NEngine* pNE;
	const GameOption* pGameOptions;

	Library<Theme> themeLibrary;				/*!< Sprites Theme */

	GameState* pGame;

	// Time management
    unsigned fpsNumber;           /*!< the number of fps (update each second)*/
    unsigned fpsCounter;          /*!< the frame counter */
    unsigned fpsLastUpdateTime;   /*!< the last update time of the fps number */

	unsigned lastUpdateTime;      /*!< the last update time of the loop */


    bool bIsRunning;               /*!< if false, the game loop stops */

protected:

	bool render();
	bool update();

public:
	GameEngine(NE::NEngine* pNE, const GameOption* pGameOptions);
	~GameEngine();

	bool init(void);

    bool load(void);

    void run(void);

    bool isRunning()const { return bIsRunning; }
};

class EngineException : public std::exception
{
private:
	std::string message;	/*!< error message to display */

public:
	EngineException(const std::string& userMessage):message(std::string("Game Engine failed: '") + userMessage + std::string("'")) {}
    virtual ~EngineException(void)throw() {}

	virtual const char* what() const throw()
	{
		return message.c_str();
	}
};

/*! \class GameEngine GameEngine.h "Game/GameEngine.h"
 *  \brief The game engine, managing the state, the library of themes and the main loop
 */

/*! \fn GameEngine :: GameEngine(NE::NEngine* pNE, const GameOption* pGameOptions)
 *	\param pNE a pointer to the NEngine
 *	\param pGameOptions a pointer to the options for the game
 */

/*!	\fn GameEngine :: ~GameEngine()
 */

/*!	\fn bool GameEngine :: render()
 *	\brief Display the game
 *	\return true if all goes right
 */

/*!	\fn bool GameEngine :: update()
 *	\brief Update the game
 *	\return true if all goes right
 */

/*!	\fn bool GameEngine :: init(void)
 *	\return true if all goes right
 */

/*!	\fn bool GameEngine :: load(void)
 *	\brief load all the data for the game
 *	\return true if all goes right
 */

/*!	\fn void GameEngine :: run(void);
 *	\brief Enter the main loop
 *	Will exit the main loop if the user press escape or click on the red cross or if an error occured
 */

/*!	\fn bool GameEngine :: isRunning()const
 *	\return true if the GameEngine is running
 */



/*! \class EngineException GameEngine.h "Game/GameEngine.h"
 *  \brief Exception thrown when the GameEngine failed
 */

/*! \fn EngineException::EngineException(const std::string& userMessage)
 *	\brief Create a message of the format: "Game Engine failed: ' + userMessage + '"
 *	\param userMessage the message from the user to display
 */

/*! \fn virtual const char* EngineException::what()const throw()
 * \return the error message
 */

#endif