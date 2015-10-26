#ifndef DOXYGEN_IGNORE_TAG
/**
OpenAWars is an open turn by turn strategic game ai, const float scalingFactorming to recreate the feeling of advance (famicon) wars (c)
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

#include "OfficerBox.h"

#include <sstream>

#include "Engine/Theme.h"
#include "Engine/AnimatedSprite.h"
#include "Engine/Font.h"
#include "Game/GameState/GameObjects/FontObject.h"
#include "Game/GameState/GameObjects/GameInfo.h"
#include "UI/UIItem.h"

#include "ow_globals.h"

OfficerBox :: OfficerBox(const Theme* pTheme, const USize2& windowSize)
	:pTheme(pTheme)
{
	leftPosition = 5;
	rightPosition = windowSize.width - 160;
	boxPosition.x = rightPosition;
	boxPosition.y = 10;
}

OfficerBox :: ~OfficerBox()
{
}

void OfficerBox :: putOnLeft()
{
	boxPosition.x = leftPosition;
}

void OfficerBox :: putOnRight()
{
	boxPosition.x = rightPosition;
}

bool OfficerBox :: draw(const NE::Renderer& r, const GameInfo& gameInfo, const unsigned int time)
{
	bool bResult = true;

	// The box
	bResult &= pTheme->getUIItem("andyOfficerBox")->getSprite()->draw(r,boxPosition,time);

	// The money text
	{
		IVec2 textPosition(boxPosition.x + 115, boxPosition.y + 13);
		unsigned int money = gameInfo.getFactionMoney();
		std::stringstream moneyStream;
		moneyStream << money;
		USize2 textSize = pTheme->getFontObject("classic")->getFont()->getStringSize(moneyStream.str());
		textPosition.x -= textSize.width;
		bResult &= pTheme->getFontObject("classic")->getFont()->draw(r,moneyStream.str(), textPosition);
	}

	return bResult;
}

void OfficerBox :: update(const UVec2& cursorPosition)
{
	if ( cursorPosition.x >= MAP_MIN_WIDTH-4 )
	{
		putOnLeft();
	}
	else if ( cursorPosition.x <= 3 )
	{
		putOnRight();
	}
}

