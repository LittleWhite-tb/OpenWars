#ifndef __MENUIGS_H__
#define __MENUIGS_H__

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

#include "InGameState.h"

#include "NEngine/InputManager.h"

#include "Types/Size2.h"

namespace NE { class Renderer; }
namespace NE { class SpriteFactory; }

class Map;
class Cursor;
class MenuBox;

class MenuIGS : public InGameState
{
private:

	MenuBox* pUIMenu;

public:
	MenuIGS(Map* pMap, const Camera* pCamera, Cursor* pCursor, GameInfo* pGameInfo, NE::SpriteFactory* const pSF, const USize2& winSize);
	~MenuIGS();

	bool draw(NE::Renderer* pRenderer, unsigned int time);
	IGState update(NE::InputManager::ArrowsDirection direction, NE::InputManager::Buttons buttons, unsigned int time);

};

#endif