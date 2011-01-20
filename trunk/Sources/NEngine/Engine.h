#ifndef __NE_ENGINE_H__
#define __NE_ENGINE_H__

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

#include <string>

namespace NE
{
	class Window;
	class Renderer;
	class Input;
	class Time;

	class Sprite;
	class SpriteLoader;
	class SpriteFactory;
    
	class Engine
	{
	protected:
		Window* pWin;					/*!< Window used by the Engine */
		Renderer* pRenderer;			/*!< Renderer used by the Engine */
		Input* pInput;					/*!< Input used by the Engine */
		Time* pTime;					/*!< Time used by the Engine */

		SpriteLoader* pSpriteLoader;	/*!< SpriteLoader used by the Engine */
		SpriteFactory* pSpriteFactory;	/*!< SpriteFactory used by the Engine */
        
	public:
		Engine(void) {}
		virtual ~Engine(void) {}

		virtual bool init(void)=0;
		virtual bool stop(void)=0;

		Window* getWindow(void) { return pWin; }
		// void setWindow(Window* const pWin) { this->pWin = pWin; }

        SpriteLoader* getSpriteLoader(void) { return pSpriteLoader; }
        SpriteFactory* getSpriteFactory(void) { return pSpriteFactory; }

		Renderer* getRenderer(void) { return pRenderer; }
		// void setRenderer(Renderer* const pRenderer) { this->pRenderer = pRenderer; }

		Input* getInput(void) { return pInput; }
		// void setInput(Input* const pInput) { this->pInput = pInput; }

		Time* getTime(void) { return pTime; }
		// void setTime(Time* const pTime) { this->pTime = pTime; }
	};
}

/*! \class NE::Engine Engine.h "NEngine/Engine.h"
 *  \brief Engine interface
 *
 * The Engine class gives an interface to implement new platform specific engine used by the game.
 * The Engine generally contains a Window, a Renderer, a SpriteLoader but also Input and Time.
 */

/*! \fn NE::Engine::Engine(void)
 */

/*! \fn virtual NE::Engine::~Engine(void)
 */

/*! \fn virtual bool NE::Engine::init(void)=0
 * \brief Start the engine (and all sub API used)
 * \return true if all goes right
 */

/*! \fn virtual bool NE::Engine::stop(void)=0
 * \brief Stop the engine (and all sub API used)
 * \return true if all goes right
 */

/*! \fn Window* NE::Engine::getWindow(void)
 * \brief Get the Window used by the Engine
 * \return a pointer to the Window
 */

/*! \fn virtual NE::SpriteLoader* NE::Engine::getSpriteLoader(void)
 * \brief Get the SpriteLoader
 * \return a pointer to the SpriteLoader
 */
 
 /*! \fn virtual NE::SpriteFactory* NE::Engine::getSpriteFactory(void)
 * \brief Get the SpriteFactory
 * \return a pointer to the SpriteFactory
 */

/*! \fn Renderer* NE::Engine::getRenderer(void)
 * \brief Get the Renderer used by the Engine
 * \return a pointer to the Renderer
 */

/*! \fn Input* NE::Engine::getInput(void)
 * \brief Get the Input used by the Engine
 * \return a pointer to the Input
 */

/*! \fn Time* NE::Engine::getTime(void)
 * \brief Get the Time used by the Engine
 * \return a pointer to the Time
 */

#endif
