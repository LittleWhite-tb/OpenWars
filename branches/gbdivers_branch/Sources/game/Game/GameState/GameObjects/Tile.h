#ifndef __TILE_H__
#define __TILE_H__

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

struct SDL_Surface;

#include <string>

#include <NEngine/Types/Vec2.h>

namespace NE { class SpriteLoader; }

class AnimatedSprite;
class Params;

class Tile
{
private:

    std::string internalName;
    std::string name;
    unsigned int id;
    short int menuEntry;

    AnimatedSprite* pSprite;
    UVec2 size;

    unsigned int defence;

    Params* pParams;        /*!< All others parameters that can be optional */

    static const std::string neededParameters[];

    Tile(const Tile& tile) { (void)tile; }
    Tile& operator=(const Tile& tile) { (void)tile; return *this; }

public:

    Tile():pParams(NULL) {};
    Tile(Params* const pParams, NE::SpriteLoader* pSL, const std::string& folderPath);
    ~Tile();

    bool operator==(const Tile& tile)const
    {
        return tile.getInternalName() == this->internalName;
    }

    const std::string& getInternalName()const { return internalName; }
    const std::string& getName()const { return name; }
    unsigned int getID()const { return id; }
    short int getMenuEntry()const { return menuEntry; }
    AnimatedSprite* getSprite()const { return pSprite; }
    const UVec2& getSize()const { return size; }
    unsigned int getDefence()const { return defence; }

    const Params* getParams()const { return pParams; }
};

/*! \class Tile Tile.h "Game/GameState/GameObjects/Tile.h"
 *  \brief Tile information
 */

/*! \fn Tile :: Tile()
 */

/*! \fn Tile :: Tile(Params* const pParams, NE::SpriteLoader* pSL, const std::string& folderPath)
 *  \param pParams the information to create the Tile
 *  \param pSL pointer to the SpriteLoader to use
 *  \param folderPath path where to load the sprites
 */

/*! \fn Tile :: ~Tile()
 */

/*! \fn bool Tile :: operator==(const Tile& tile)const
 *  \brief fast tile check using the internal name
 */

/*! \fn const std::string& Tile :: getInternalName()const
 *  \return
 */

/*! \fn const std::string& Tile :: getName()const
 *  \return
 */

/*! \fn unsigned int Tile :: getID()const
 *  \return
 */

/*! \fn short int Tile :: getMenuEntry()const
 *  \return
 */

/*! \fn AnimatedSprite* Tile :: getSprite()const
 *  \return
 */

/*! \fn const UVec2& Tile :: getSize()const
 *  \return
 */

/*! \fn const unsigned int Tile :: getDefence()const
 *  \return
 */

/*! \fn const Params* const Tile :: getParams()const
 *  \return
 */

#endif
