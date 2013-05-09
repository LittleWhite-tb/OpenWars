#ifndef __MAPMARKER_HPP__
#define __MAPMARKER_HPP__

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

#include <vector>

#include "NEngine/Types/Vec2.h"

namespace NE { class Renderer; }

class AnimatedSprite;
class Map;
class Camera;
class Unit;

class MapMarker
{
protected:

    const Map* pMap;

    AnimatedSprite* pMarkerSprite;

    std::vector<std::vector<int> > marks;

    virtual void setMarks(const UVec2& position, const Unit* pUnit)=0;
    void setMarksInRange(const UVec2& position, unsigned int minRange, unsigned int maxRange);

public:
    MapMarker(const Map* pMap, AnimatedSprite* pMarkerSprite);
    virtual ~MapMarker() {}

    virtual void clear();
    bool isMarked(const UVec2& position)const;
    void setMarksForUnitAt(const UVec2& position);

    bool draw(const NE::Renderer& r, const Camera& c, const unsigned int time);
};

#endif
