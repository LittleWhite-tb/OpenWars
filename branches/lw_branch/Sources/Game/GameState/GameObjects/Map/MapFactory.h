#ifndef __MAPFACTORY_H__
#define __MAPFACTORY_H__

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

#include "Types/Size2.h"

class Map;
class Theme;

class MapFactory
{
private:

public:

    static Map* createEmptyMap(const Theme* pTheme, const USize2& size);
};

/*! \class MapFactory MapFactory.h "Game/GameState/GameObjects/Map/MapFactory.h"
 *  \brief Class to build a map from scratch
 */

/*! \fn static Map* MapFactory::createEmptyMap(const Theme* pTheme, const USize2& size)
 *  \brief build an empty map
 *  \param pTheme pointer to the theme to use
 *  \param size the size of the map
 *  \return returns a pointer on the Map or NULL if something failed.
 *  \throw std::bad_alloc when the machine does not have enough memory
 *  Tile at ID 0 of the Theme is used to fill the map
 */

#endif
