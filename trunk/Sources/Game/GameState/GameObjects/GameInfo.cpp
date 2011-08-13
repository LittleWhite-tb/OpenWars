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

#include "GameInfo.h"

#include <cassert>

GameInfo :: GameInfo(unsigned int nbFaction, unsigned int initialMoneyAmount)
	:factionMoney(nbFaction,Money(initialMoneyAmount)),currentFaction(0),numberFaction(nbFaction)
{
}

GameInfo :: GameInfo(unsigned int nbFaction, const std::vector<unsigned int>& initialMoneyAmount)
	:currentFaction(0),numberFaction(nbFaction)
{
	assert(nbFaction == initialMoneyAmount.size());

	for ( unsigned int i = 0 ; i < nbFaction ; i++ )
	{
		factionMoney.push_back(Money(initialMoneyAmount[i]));
	}
}

unsigned int GameInfo :: getCurrentFaction()const
{
	return currentFaction;
}

unsigned int GameInfo :: getNbFaction()const
{
	return numberFaction;
}

Money* GameInfo :: getFactionMoney()
{
	return &factionMoney[currentFaction%numberFaction];
}

unsigned int GameInfo :: getFactionMoney()const
{
	return getFactionMoney(currentFaction%numberFaction);
}

unsigned int GameInfo :: getFactionMoney(unsigned int faction)const
{
	return factionMoney[faction].getMoney();
}

unsigned int GameInfo :: getNumberTurn()const
{
	return currentFaction / numberFaction + 1;
}

void GameInfo :: nextFaction()
{
	currentFaction++;
}