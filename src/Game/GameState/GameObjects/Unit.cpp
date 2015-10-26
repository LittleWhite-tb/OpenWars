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

#include "Unit.h"

#include "Engine/Params.h"

#include "UnitTemplate.h"

Unit :: Unit(const UnitTemplate* pUTemplate)
    :pUnitTemplate(pUTemplate),
     faction(pUTemplate->getFaction()),
     fuel(pUTemplate->getFuel()),ammo(pUTemplate->getAmmo()),life(pUTemplate->getLife()),state(US_ACTIVE)
{
}

unsigned int Unit :: getPossibleMovementLength()const
{
	unsigned int movementLength = this->getTemplate()->getParams()->getAs<unsigned int>("movement",0);
	if ( movementLength > this->fuel  )
	{
		movementLength = this->fuel;
	}

	return movementLength;
}
