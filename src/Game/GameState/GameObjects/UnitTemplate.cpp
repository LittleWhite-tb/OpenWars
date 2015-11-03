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

#include "UnitTemplate.h"

#include <cassert>

#include "NEngine/NEngine.h"

#include "CEngine/AnimatedSprite.h"

#include "Engine/Params.h"

const std::string UnitTemplate::neededParameters[] = { "unit-id", "unit-classId", "unit-faction",
                                                        "internalName", "name", "sprite_filename", "sprite_greyed", "size_x", "size_y",
                                                        "movement", "fuel", "fuelConsumption", "life", "price" };

UnitTemplate :: UnitTemplate(Params* const pParams, NE::SpriteLoader* pSL, const std::string& folderPath)
    :pParams(pParams)
{
    assert(pParams);
    assert(pSL);

    // Check if the important nodes are present
    for ( unsigned int i = 0 ; i < sizeof(neededParameters) / sizeof(std::string) ; i++ )
    {
        if ( !pParams->exists(neededParameters[i]) )
        {
            throw MissingParameterException(neededParameters[i]);
        }
    }

    try
    {
        this->id = pParams->getAs<unsigned int>("unit-id");
        this->faction = pParams->getAs<short int>("unit-faction");

        this->internalName = pParams->get("internalName");
        this->name = pParams->get("name");

        UVec2 spriteSize(pParams->getAs<unsigned int>("size_x"),
                         pParams->getAs<unsigned int>("size_y"));

        this->pSprite = new CE::AnimatedSprite(pSL, folderPath + pParams->get("sprite_filename"),spriteSize,pParams->getAs<unsigned int>("animationTime",200));
        if ( this->pSprite == NULL )
        {
            NEError << "Fail to allocate memory for AnimatedSprite for UnitTemplate\n";
            throw std::bad_alloc();
        }

        this->pSpriteGreyed = new CE::AnimatedSprite(pSL, folderPath + pParams->get("sprite_greyed"),spriteSize,pParams->getAs<unsigned int>("animationTime",200));
        if ( this->pSpriteGreyed == NULL )
        {
            NEError << "Fail to allocate memory for greyed AnimatedSprite for UnitTemplate\n";
            throw std::bad_alloc();
        }

        this->size.x = pParams->getAs<unsigned int>("size_x");
        this->size.y = pParams->getAs<unsigned int>("size_y");

        this->movement = pParams->getAs<unsigned int>("movement");
        this->fuel = pParams->getAs<unsigned int>("fuel");
        this->fuelConsumption = pParams->getAs<unsigned int>("fuelConsumption");
        this->ammo = pParams->getAs<unsigned int>("ammo",0);
        this->life = pParams->getAs<unsigned int>("life",10);
        this->price = pParams->getAs<unsigned int>("price");
    }
    catch ( ParameterNotFoundParamsException& pnfpe)
    {
        NEError << "The force list is not matching the requested parameters\n";
        NEError << "Parameter '" << pnfpe.what() << "' not found\n";
        throw MissingParameterException("unknown");
    }
}

UnitTemplate :: ~UnitTemplate()
{
	delete pSpriteGreyed;
    delete pSprite;
    delete pParams;
}
