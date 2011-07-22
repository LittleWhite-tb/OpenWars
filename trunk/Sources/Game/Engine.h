#ifndef __ENGINE_H__
#define __ENGINE_H__

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

class VTime;

class Map;
class Camera;

class Engine
{
private:

	virtual bool load()=0;

protected:
	NE::NEngine* pNE;            /*!< Native engine to use in the Engine */
	Library<Theme> themeLibrary;				/*!< Sprites Theme */

	Map* pMap;
	Camera* pCam;				/*!< The camera */

	VTime* pVT;					/*!< The virtual time for synchronisation */

public:
	Engine(NE::NEngine* const pNE);
	virtual ~Engine(void);

	virtual bool init(void);

	void loadTheme(const std::string& themeName);
	void loadThemeList(const std::string& listPath);
	bool load(const std::string& mapName);

	virtual bool run(void)=0;
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

/*! \class Engine Engine.h "Engine/Engine.h"
 *  \brief Basic base for the engines
 *
 *	Contains a Window, a Renderer, a Keyboard handler, a VTime handler.
 *	The engine should at least implement a init and a run function.
 */

/*! \fn Engine::Engine(NE::NEngine* const pNE);
 * \param pNE pointer of the Native Engine to user
 */

/*! \fn virtual Engine::~Engine(void)
 */

/*! \fn virtual bool Engine::init()
 * \brief Init the engine by constructing all elements (Renderer, SpriteManager, FontManager,...)
 * \return true if all goes fine
 */

/*! \fn virtual bool Engine::load(const std::string& mapName)=0
 * \brief Load the map from a file
 * \param mapName the name of the file to load
 * \return true if all goes fine
 */

/*! \fn void Engine::loadTheme(const std::string& themeName)
 * \brief Load the theme called themeName
 * \param themeName
 * Can throw EngineException if something goes wrong
 */

/*! \fn virtual bool Engine::loadThemeList(const std::string& listPath);
 * \brief Load the themes from a XML list
 * \param listPath name of the file to read, containing the list of themes
 * Can throw EngineException if something goes wrong
 */

/*! \fn virtual bool Engine::run(void)=0
 * \brief Start the main loop
 * \return true if all goes fine
 */

/*! \class EngineException EngineException.h "Game/Engine.h"
 *  \brief Exception related to engine failure
 */

/*! \fn EngineException::EngineException(const std::string& userMessage)
 * Create a message of the format: "Game Engine failed: 'USER_MESSAGE'"
 * \param userMessage the message from user to display
 */

/*! \fn virtual const char* EngineException::what()const throw()
 * \return the error message
 */

#endif
