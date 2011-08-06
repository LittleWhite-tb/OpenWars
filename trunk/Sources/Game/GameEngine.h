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


	void loadTheme(const std::string& themeName);
	void loadThemeList(const std::string& listPath);

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

#endif