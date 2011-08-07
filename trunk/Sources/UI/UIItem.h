#ifndef __UIITEM_H__
#define __UIITEM_H__

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

#include <string>

namespace NE { class SpriteLoader; }

class AnimatedSprite;
class Params;

class UIItem
{
private:

    std::string internalName;               /*!< Name to display */
    AnimatedSprite* pSprite;                /*!< */

    Params* pParams;                /*!< Rest of the information for this unit */

    static const std::string neededParameters[];    /*!< List of parameters needed for the constructor */

public:

    UIItem():pParams(NULL) {};
    UIItem(Params* const pParams, NE::SpriteLoader* pSL, const std::string& folderPath);
    ~UIItem();

    const std::string& getInternalName()const { return internalName; }

    AnimatedSprite* getSprite()const { return pSprite; }

    const Params* getParams()const { return pParams; }
};

/*! \class UIItem UIItem.h "Game/UIItem.h"
 *  \brief Item for the UserInterface used by the Theme
 */

/*! \fn UIItem :: UIItem()
 */

/*! \fn UIItem :: UIItem(Params* const pParams, NE::SpriteLoader* pSL, const std::string& folderPath)
 *  Loads a UIItem from Params
 *  \param pParams the parameters list for the FontObject
 *  \param pSL the SpriteLoader to use to load the font sprite
 *  \param folderPath the folder where to load the file
 */

/*! \fn UIItem :: ~UIItem()
 */

/*! \fn const std::string& UIItem :: getInternalName()const
 *  \return
 */

/*! \fn AnimatedSprite* UIItem :: getSprite()const
 *  \return
 */

/*! \fn const Params* UIItem :: getParams()const
 *  \return
 */

#endif
