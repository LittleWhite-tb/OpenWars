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

#include "VTime.h"

#include "NEngine/NEngine.h"
#include "NEngine/Time.h"

VTime :: VTime(NE::Time* const pNativeTime, const unsigned int nbFPS, const unsigned int updateNbFPS)
:pNativeTime(pNativeTime),time(0),lastDrawTime(0),lastUpdateTime(0),msSecondsBetweenTwoFrame(1000/nbFPS),msSecondsBetweenTwoUpdate(1000/updateNbFPS)
{
}

void VTime :: update(void) 
{ 
	time++;
	lastDrawTime = pNativeTime->getTime();
}

void VTime :: waitNextFrame()
{
	static bool isFirst = true;

	int timeEllapsed = pNativeTime->getTime() - lastDrawTime;
	int timeToWait = msSecondsBetweenTwoFrame - timeEllapsed;

	if ( timeToWait < 6 )
	{
		if ( !isFirst )
		{
            NE::NEngine::logger().log(NE::LL_Warning,"The game is too slow");
		}
		else
		{
			isFirst = false;
		}
	}
	else
	{
		pNativeTime->delay(timeToWait);
	}

	this->update();
}

bool VTime :: canUpdate(void)
{
	int timeEllapsed = pNativeTime->getTime() - lastUpdateTime;

	if ( static_cast<int>(msSecondsBetweenTwoUpdate) < timeEllapsed )
	{
		lastUpdateTime = pNativeTime->getTime();
		return true;
	}
	else
	{
		return false;
	}
}
