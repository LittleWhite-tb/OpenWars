#ifndef __OFFICERBOX_H__
#define __OFFICERBOX_H__

#ifndef DOXYGEN_IGNORE_TAG
/**
OpenAWars is an open turn by turn strategic game ai, const float scalingFactorming to recreate the feeling of advance (famicon) wars (c)
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

#include "Types/Vec2.h"
#include "Types/Size2.h"

namespace NE { class Renderer; }

class Theme;
class AnimatedSprite;
class Font;

class GameInfo;

class OfficerBox
{
private:

	IVec2 boxPosition;
	unsigned int leftPosition;
	unsigned int rightPosition;

	const Theme* pTheme;

public:
	OfficerBox(const Theme* pTheme, const USize2& windowSize);
	~OfficerBox();

	void putOnLeft();
	void putOnRight();

	bool draw(const NE::Renderer& r, const GameInfo& gameInfo, const unsigned int time);
	void update(const UVec2& cursorPosition);
};

#endif