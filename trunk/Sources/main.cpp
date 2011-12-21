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
#include <sstream>
#include <cstring>

#include "NEngine/NEngine.h"
#include "NEngine/Window.h"
#include "NEngine/Native/SDL/SDL_Engine.h"
#include "NEngine/Types/Vec2.h"

#include "Game/GameEngine.h"

#include "GameOption.h"

#include "globals.h"

int main(int argc, char** argv)
{
    GameOption gameOptions(argc,argv);

    // Starting the native engine
    NE::NEngine* pNE = new NE::SDL_Engine();
    if ( pNE->init() == false )
    {
        return 1;
    }

    {
        if ( pNE->getWindow()->createWindow(gameOptions.winSize,32,gameOptions.needFullscreen,"OpenAWars") )
        {
            GameEngine* pGEngine = new GameEngine(pNE,&gameOptions);
            if ( pGEngine == NULL )
            {
                NE::NEngine::logger()->log(NE::LL_Error,"Fail to allocate GameEngine");
            }
            else if ( pGEngine->init() )
            {
                if ( pGEngine->load() )
                {
                    pGEngine->run();
                }
            }

            delete pGEngine;

            pNE->getWindow()->destroyWindow();
        }
    }

    // Stopping the Native Engine
    pNE->stop();
    delete pNE;

	NE::NEngine::setLogger(NULL);

    return 0;
}
