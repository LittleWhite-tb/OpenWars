#ifndef __NE_NENGINE_H__
#define __NE_NENGINE_H__

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

#include "Logging/Logger.hpp"
#include "NEngine/Logging/Filter/LoggerFilter.hpp"
#include "NEngine/Logging/Formater/LoggerFormater.hpp"
#include "NEngine/Logging/Writer/LoggerWriter.hpp"

namespace NE
{
	class Window;
	class Renderer;
	class InputManager;
	class Time;

	class Sprite;
	class SpriteLoader;
	class SpriteFactory;
    
	class NEngine
	{
    private:

		static NE::Logger<NE::LoggerFilter,NE::LoggerFormater,NE::LoggerWriter>* m_pLogger;

	protected:
		Window* pWin;					/*!< Window used by the Engine */
		Renderer* pRenderer;			/*!< Renderer used by the Engine */
		InputManager* pInputManager;	/*!< InputManager used by the Engine */
		Time* pTime;					/*!< Time used by the Engine */

		SpriteLoader* pSpriteLoader;	/*!< SpriteLoader used by the Engine */
		SpriteFactory* pSpriteFactory;	/*!< SpriteFactory used by the Engine */

        virtual bool initAPI(void)=0;
		virtual bool stopAPI(void)=0;
        
	public:
		NEngine(void) {}
		virtual ~NEngine(void) {}

		bool init(void);
		bool stop(void);

		Window* getWindow(void) { return pWin; }
		// void setWindow(Window* const pWin) { this->pWin = pWin; }

        SpriteLoader* getSpriteLoader(void) { return pSpriteLoader; }
        SpriteFactory* getSpriteFactory(void) { return pSpriteFactory; }

		Renderer* getRenderer(void) { return pRenderer; }
		// void setRenderer(Renderer* const pRenderer) { this->pRenderer = pRenderer; }

		InputManager* getInputManager(void) { return pInputManager; }
		// void setInput(Input* const pInput) { this->pInput = pInput; }

		Time* getTime(void) { return pTime; }
		// void setTime(Time* const pTime) { this->pTime = pTime; }

        static NE::Logger<NE::LoggerFilter,NE::LoggerFormater,NE::LoggerWriter>& logger() { return *m_pLogger; }
		static void setLogger(NE::Logger<NE::LoggerFilter,NE::LoggerFormater,NE::LoggerWriter>* pNewLogger);
	};
}


#define NEDebug LDebug(NE::NEngine::logger())                            /*!< shortcut to send debug messages to the NEngine logger */
#define NEWarning LWarning(NE::NEngine::logger())                        /*!< shortcut to send warning messages to the NEngine logger */
#define NEError LError(NE::NEngine::logger())                            /*!< shortcut to send error messages to the NEngine logger */
#define NELog(level) Log(NE::NEngine::logger(),level)                    /*!< shortcut to send log message with specified importancy level to the NEngine logger */

/*! \class NE::NEngine NEngine.h "NEngine/Engine.h"
 *  \brief NEngine interface
 *
 * The Engine class gives an interface to implement new platform specific engine used by the game.
 * The Engine generally contains a Window, a Renderer, a SpriteLoader but also Input and Time.
 */

/*! \fn NE::NEngine::NEngine(void)
 */

/*! \fn virtual NE::NEngine::~NEngine(void)
 */
 
/*! \fn virtual bool NE::NEngine::initAPI(void)=0
 * Init the API (internal)
 * \return true if all goes right
 */
 
 /*! \fn virtual bool NE::NEngine::stopAPI(void)=0
 * Stop the API (internal)
 * \return true if all goes right
 */

/*! \fn virtual bool NE::NEngine::init(void)=0
 * \brief Start the engine (and all sub API used)
 * \return true if all goes right
 */

/*! \fn virtual bool NE::NEngine::stop(void)=0
 * \brief Stop the engine (and all sub API used)
 * \return true if all goes right
 */

/*! \fn Window* NE::NEngine::getWindow(void)
 * \brief Get the Window used by the Engine
 * \return a pointer to the Window
 */

/*! \fn virtual NE::SpriteLoader* NE::NEngine::getSpriteLoader(void)
 * \brief Get the SpriteLoader
 * \return a pointer to the SpriteLoader
 */
 
 /*! \fn virtual NE::SpriteFactory* NE::NEngine::getSpriteFactory(void)
 * \brief Get the SpriteFactory
 * \return a pointer to the SpriteFactory
 */

/*! \fn Renderer* NE::NEngine::getRenderer(void)
 * \brief Get the Renderer used by the Engine
 * \return a pointer to the Renderer
 */

/*! \fn Input* NE::NEngine::getInputManager(void)
 * \brief Get the InputManager used by the Engine
 * \return a pointer to the InputManager
 */

/*! \fn Time* NE::NEngine::getTime(void)
 * \brief Get the Time used by the Engine
 * \return a pointer to the Time
 */

#endif
