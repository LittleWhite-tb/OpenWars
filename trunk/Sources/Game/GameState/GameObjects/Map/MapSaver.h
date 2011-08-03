#ifndef __MAPSAVER_H__
#define __MAPSAVER_H__

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

class Map;

class MapSaver
{
public:
    static bool saveMapToFile(const std::string& fileName, const Map& map);
};

/*! \class MapSaver MapSaver.h "Game/Map/MapSaver.h"
 *  \brief Class to save a map in a file
 */

/*! \fn static bool MapSaver::saveMapToFile(const std::string& fileName, const Map& map)
 *  \brief save the map in a file
 *  \param fileName the name of the file where to write the map
 *  \param map the map to save
 *  \return true if all goes right ; false if the file could not be open
 */

#endif
