#ifndef __MAPDRAWER_H__
#define __MAPDRAWER_H__

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

namespace NE { class Renderer; }
class Map;
class Camera;

class MapDrawer
{
private:

	static bool drawTerrain(const NE::Renderer& r, const Map* pMap, const Camera& c, const unsigned int time);
	static bool drawUnits(const NE::Renderer& r, const Map* pMap, const Camera& c, const unsigned int time);

public:

	static bool draw(const NE::Renderer& r, const Map* pMap, const Camera& c, const unsigned int time);
};

/*! \class MapDrawer MapDrawer.h "Game/GameState/GameObjects/Map/MapDrawer.h"
 *  \brief Class to draw the map on screen
 */

/*! \fn static bool MapDrawer::drawTerrain(const NE::Renderer& r, const Map* pMap, const Camera& c, const unsigned int time)
 *  \brief draw the terrain of the map
 *  \param r the renderer to use
 *  \param pMap a pointer to the map to use
 *	\param c the camera describing the viewport
 *	\param time the current time of the game
 *  \return true if all goes right
 */

/*! \fn static bool MapDrawer::drawUnits(const NE::Renderer& r, const Map* pMap, const Camera& c, const unsigned int time)
 *  \brief draw the units of the map
 *  \param r the renderer to use
 *  \param pMap a pointer to the map to use
 *	\param c the camera describing the viewport
 *	\param time the current time of the game
 *  \return true if all goes right
 */

/*! \fn static bool MapDrawer::draw(const NE::Renderer& r, const Map* pMap, const Camera& c, const unsigned int time)
 *  \brief draw a map
 *  \param r the renderer to use
 *  \param pMap a pointer to the map to use
 *	\param c the camera describing the viewport
 *	\param time the current time of the game
 *  \return true if all goes right
 */

#endif