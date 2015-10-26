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

#include "UnitTemplateFactionList.h"

#include "NEngine/NEngine.h"

#include "Game/GameState/GameObjects/UnitTemplate.h"

UnitTemplateFactionList :: ~UnitTemplateFactionList()
{
	for ( std::vector<UnitTemplate*>::iterator itPUnitTemplate = unitTemplates.begin() ; itPUnitTemplate != unitTemplates.end() ; ++itPUnitTemplate )
	{
		delete (*itPUnitTemplate);
	}

	unitTemplates.clear();
}

void UnitTemplateFactionList :: add(UnitTemplate* pUnitTemplate)
{
	unsigned int faction = pUnitTemplate->getFaction();
	if ( faction >= unitTemplates.size() )
	{
		unitTemplates.resize(faction+1);
	}

	unitTemplates[faction] = pUnitTemplate;
}

UnitTemplate* UnitTemplateFactionList ::  get(unsigned int faction)const
{
	if ( faction >= unitTemplates.size() )
	{
        NEWarning << "UnitTemplate :: trying to get a faction not in the database\n";
		return NULL;
	}

	return unitTemplates[faction];
}
