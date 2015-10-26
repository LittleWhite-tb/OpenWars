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

#include "UIItem.h"

#include "NEngine/NEngine.h"
#include "NEngine/SpriteLoader.h"
#include "NEngine/Sprite.h"
#include "Engine/Params.h"
#include "Engine/AnimatedSprite.h"

const std::string UIItem::neededParameters[] = { "internalName", "filename" };

UIItem :: UIItem(Params* const pParams, NE::SpriteLoader* pSL, const std::string& folderPath)
    :pParams(pParams)
{
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
        const NE::Sprite* pSprite = pSL->loadSpriteFromFile(folderPath + pParams->get("filename"));   // Will throw an exception if a problem occured

        UVec2 spriteSize(pParams->getAs<unsigned int>("size_x",pSprite->getSize().width),
                         pParams->getAs<unsigned int>("size_y",pSprite->getSize().height));

        this->pSprite = new AnimatedSprite(pSprite,spriteSize,pParams->getAs<unsigned int>("animationTime",200));
        if ( this->pSprite == NULL )
        {
            NEError << "Fail to allocate memory for AnimatedSprite for UnitTemplate\n";
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

UIItem :: ~UIItem()
{
    delete pSprite;
    delete pParams;
}
