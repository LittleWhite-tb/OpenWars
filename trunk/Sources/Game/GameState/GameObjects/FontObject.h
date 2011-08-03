#ifndef __FONTOBJECT_H__
#define __FONTOBJECT_H__

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

class Font;
class Params;

class FontObject
{
private:

    std::string internalName;
    Font* pFont;

    Params* pParams;

    static const std::string neededParameters[];

public:
    FontObject();
    FontObject(Params* const pParams, NE::SpriteLoader* pSL, const std::string& folderPath);
    ~FontObject();

    const std::string& getInternalName()const { return internalName; }
    Font* getFont()const { return pFont; }

    const Params* getParams()const { return pParams; }
};

/*! \class FontObject FontObject.h "Game/FontObject.h"
 *  \brief Font used by the Theme
 */

/*! \fn FontObject :: FontObject()
 */

/*! \fn FontObject :: FontObject(Params* const pParams, NE::SpriteLoader* pSL, const std::string& folderPath)
 *  Loads a FontObject from Params
 *  \param pParams the parameters list for the FontObject
 *  \param pSL the SpriteLoader to use to load the font sprite
 *  \param folderPath the folder where to load the file
 */

/*! \fn FontObject :: ~FontObject()
 */

/*! \fn const std::string& FontObject :: getInternalName()const
 *  \return
 */

/*! \fn Font* FontObject :: getFont()const
 *  \return
 */

/*! \fn const Params* FontObject :: getParams()const
 *  \return
 */

#endif
