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

#include "Tile.h"

#include <cassert>

#include "Engine/Params.h"

#include "Engine/AnimatedSprite.h"

#include <NEngine/Utils/Logger.h>

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

        this->pSprite = new AnimatedSprite(pSL, folderPath + pParams->get("filename"),spriteSize,pParams->getAs<unsigned int>("animationTime",200));
        if ( this->pSprite == NULL )
        {
            LError << "Fail to allocate memory for AnimatedSprite for Tile";
            throw std::bad_alloc();
        }

        this->defence = pParams->getAs<unsigned int>("defence");
    }
    catch ( ParameterNotFoundParamsException )
    {
        LError << "The force list is not matching the requested parameters";
        throw MissingParameterException("unknown");
    }
}

Tile :: ~Tile()
{
    delete pSprite;
    delete pParams;
}
