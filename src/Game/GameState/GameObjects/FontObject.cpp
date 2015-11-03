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

#include "FontObject.h"

#include "NEngine/NEngine.h"
#include "NEngine/SpriteLoader.h"
#include "CEngine/Font.h"

#include "Engine/Params.h"

#include <cassert>

const std::string FontObject::neededParameters[] = { "font-startingLetter", "internalName", "filename", "charSize_x", "charSize_y" };

FontObject :: FontObject(Params* const pParams, NE::SpriteLoader* pSL, const std::string& folderPath)
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

        UVec2 letterSize(pParams->getAs<unsigned int>("charSize_x"),
                         pParams->getAs<unsigned int>("charSize_y"));

        this->pFont = new CE::Font(
                                pSL->loadSpriteFromFile(folderPath + pParams->get("filename")),
                                letterSize,
                                pParams->getAs<char>("font-startingLetter"));
        if ( this->pFont == NULL )
        {
            NEError << "Fail to allocate memory for Font for FontObject\n";
            throw std::bad_alloc();
        }
    }
    catch ( ParameterNotFoundParamsException& pnfpe)
    {
        NEError << "The force list is not matching the requested parameters\n";
        NEError << "Parameter '" << pnfpe.what() << "' not found\n";
        throw MissingParameterException("unknown");
    }
}

FontObject :: ~FontObject()
{
    delete pFont;
    delete pParams;
}
