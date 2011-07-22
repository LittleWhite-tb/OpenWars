#ifndef __MAPINTEGRITYCHECKER_H__
#define __MAPINTEGRITYCHECKER_H__

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

#include <map>
#include <string>

#include "Types/Vec2.h"

class Map;
class Tile;
class UnitTemplate;

class MapIntegrityChecker
{
	typedef const Tile* (*checker) (const Map* pMap, const UVec2& position);

private:

protected:
	const Map* pMap;

	std::map<std::string, checker> coherencyCheckers;

public:
	MapIntegrityChecker(const Map* pMap):pMap(pMap) {}
	virtual ~MapIntegrityChecker() {}

	virtual void addChecker(const std::string& name)=0;

	const Tile* checkCoherency(const UVec2& position);

	virtual bool testTile(const UVec2& position, const Tile* pTile)=0;
	virtual bool testUnit(const UVec2& position, const UnitTemplate* pUnitTemplate)=0;
};

#endif
