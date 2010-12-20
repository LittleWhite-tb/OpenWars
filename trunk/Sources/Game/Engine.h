#ifndef __ENGINE_H__
#define __ENGINE_H__

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

#include "../Engine/Renderer.h"

#include "../NEngine/NETypes.h"

class SpriteManager;
class FontManager;

class VTime;
class Keyboard;

class Engine
{
protected:
	Window* pWin;			/*!< The window to use for the editor (created outside the engine) */
	Renderer* pRenderer;		/*!< The renderer for the editor */

	SpriteManager* pSM;			/*!< The sprite manager for the editor */
	FontManager* pFM;			/*!< The font manager for the editor */

	VTime* pVT;					/*!< The virtual time for synchronisation */

	Keyboard* pKB;				/*!< The keyboard for user access */

public:
	Engine(void);
	virtual ~Engine(void);

	virtual bool init(Window* pWin, const RenderingAPI rAPI);

	virtual bool load(const std::string& mapName)=0;

	virtual bool run(void)=0;
};

/*! \class Engine Engine.h "Engine/Engine.h"
 *  \brief Basic base for the engines
 *
 *	Contains a Window, a Renderer, a Keyboard handler, a VTime handler.
 *	The engine should at least implement a init and a run function.
 */

/*! \fn Engine::Engine(void);
 */

/*! \fn virtual Engine::~Engine(void)
 */

/*! \fn virtual bool Engine::init(const Window* pWin, const RenderingAPI rAPI)
 * \brief Init the engine by constructing all elements (Renderer, SpriteManager, FontManager,...)
 * \param pWin The window to use with for the editor
 * \param rAPI The rendering API to use
 * \return true if all goes fine
 */

/*! \fn virtual bool Engine::load(const std::string& mapName)=0
 * \brief Load the map from a file
 * \param mapName the name of the file to load
 * \return true if all goes fine
 */

/*! \fn virtual bool Engine::run(void)=0
 * \brief Start the main loop
 * \return true if all goes fine
 */

#endif