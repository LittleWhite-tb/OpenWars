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

#include <NEngine/NEngine.h>
#include <NEngine/Window.h>
#include <NEngine/Native/SDL/SDL_Engine.h>

#include "Game/GameEngine.h"
#include <NEngine/Types/Vec2.h>
#include <NEngine/Utils/Logger.h>

#include "GameOption.h"

#include "globals.h"

int main(int argc, char** argv)
{
    std::cout << "0" << std::endl;
    GameOption gameOptions(argc,argv);

    // Starting the native engine
    NE::NEngine* pNE = new NE::SDL_Engine();
    if ( pNE->init() == false )
    {
        return 1;
    }
    std::cout << "1" << std::endl;

    if ( pNE->getWindow()->createWindow(gameOptions.winSize,32,gameOptions.needFullscreen,"OpenAWars") )
    {
        std::cout << "3" << std::endl;
        GameEngine* pGEngine = new GameEngine(pNE,&gameOptions);
        if ( pGEngine == NULL )
        {
            std::cout << "4" << std::endl;
            LError << "Fail to allocate GameEngine";
        }
        else if ( pGEngine->init() )
        {
            std::cout << "5" << std::endl;
            if ( pGEngine->load() )
            {
                std::cout << "6" << std::endl;
                pGEngine->run();
            }
        }

        delete pGEngine;

        pNE->getWindow()->destroyWindow();
    }
    std::cout << "2" << std::endl;

    // Stopping the Native Engine
    pNE->stop();
    delete pNE;

    Logger::deleteLogger();

    return 0;
}
