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

#include "Tile.h"

#include <cassert>

#include "NEngine/NEngine.h"
#include "NEngine/Exceptions/FileNotFoundException.h"

#include "CEngine/AnimatedSprite.h"

#include "Engine/Params.h"

const std::string Tile::neededParameters[] = { "tile-id", "tile-menu", "internalName", "name", "filename", "size_x", "size_y", "defence" };

Tile :: Tile(Params* const pParams, NE::SpriteLoader* pSL, const std::string& folderPath)
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
        this->internalName = pParams->get("internalName");
        this->name = pParams->get("name");
        this->id = pParams->getAs<unsigned int>("tile-id");
        this->menuEntry = pParams->getAs<short int>("tile-menu");

        UVec2 spriteSize(pParams->getAs<unsigned int>("size_x"),
                         pParams->getAs<unsigned int>("size_y"));

		try
		{
			this->pSprite = new CE::AnimatedSprite(pSL, folderPath + pParams->get("filename"),spriteSize,pParams->getAs<unsigned int>("animationTime",200));
		}
		catch ( FileNotFoundException& fnfe) // Should be handle as smart ptr
		{
			delete pParams;
			throw fnfe;
		}

        if ( this->pSprite == NULL )
        {
            NEError << "Fail to allocate memory for AnimatedSprite for Tile\n";
            throw std::bad_alloc();
        }

        this->defence = pParams->getAs<unsigned int>("defence");
    }
    catch ( ParameterNotFoundParamsException& )
    {
        NEError << "The force list is not matching the requested parameters\n";
        throw MissingParameterException("unknown");
    }
}

Tile :: ~Tile()
{
    delete pSprite;
    delete pParams;
}
