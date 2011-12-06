#ifndef __GAMEOPTION_H__
#define __GAMEOPTION_H__

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

#include "NEngine/Types/Size2.h"

struct GameOption
{
    USize2 winSize;             /*!< The size of the window to create */
    bool needFullscreen;        /*!< True if the fullscreen needs to be enabled */

    std::string loadMapName;    /*!< The name of the map to load */

    bool editorMode;            /*!< True if the game should be started in editor mode */
    std::string saveMapName;    /*!< The name of the map to save (editor mode only) */
    USize2 mapSize;             /*!< The size of the map to create (editor mode only) */

    std::string themeName;      /*!< The theme name to use (editor mode only) */


    GameOption(int argc, char** argv);
};

/*! \struct GameOption GameOption.h "GameOption.h"
 *  \brief Container for the game options
 */

/*! \fn GameOption :: GameOption(int argc, char** argv)
 *  \brief Collect from the command line the game options (using an ArgumentParser)
 *  \param argc the number of argument in the command line
 *  \param argv the arguments in the command line
 *  \sa ArgumentParser
 */


#endif
