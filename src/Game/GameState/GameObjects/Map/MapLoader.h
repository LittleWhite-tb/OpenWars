#ifndef __MAPLOADER_H__
#define __MAPLOADER_H__

#ifndef DOXYGEN_IGNORE_TAG
/**
OpenAWars is an open turn by turn strategic game similar to Advance Wars (c)
Copyright (C) 2010-2015  Alexandre LAURENT

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

website: https://github.com/LittleWhite-tb/OpenWars
e-mail: lw.demoscene@gmail.com
**/
#endif

#include <string>

#include "Engine/Library.h"
#include "Engine/Theme.h"

class Map;


class MapLoader
{
public:
    static Map* loadMapFromFile(const Library<Theme>* const pThemes, const std::string& fileName);
};

/*! \class MapLoader MapLoader.h "Game/GameState/GameObjects/Map/MapLoader.h"
 *  \brief Class to load a map from a file
 *  the class does not keep the maps in memory (caching) since we would like to modify them during the game time
 */

/*! \fn static Map* MapLoader::loadMapFromFile(const Library<Theme>* const pThemes, const std::string& fileName);
 *  \brief load the map from a file
 *  \param pThemes the Library of themes usable for the map
 *  \param fileName the name of the file to load
 *  \return returns a pointer to the map. Can be NULL if the loading failed.
 *  \throw std::bad_alloc if there is no enough memory to load the Map
 */

#endif
