#ifndef __MONEY_H__
#define __MONEY_H__

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

class Map;
class UnitTemplate;

class Money
{
private:
    unsigned int money;

public:
    Money(unsigned int money):money(money) {}

    unsigned int getMoney()const { return money; }

    unsigned int getCapital(const Map* pMap, unsigned int faction)const;
    void collectCapital(const Map* pMap, unsigned int faction);
    bool buy(const UnitTemplate* pUnit);
};

#endif
