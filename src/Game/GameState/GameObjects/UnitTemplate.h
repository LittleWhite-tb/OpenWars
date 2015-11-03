#ifndef __UNITTEMPLATE_H__
#define __UNITTEMPLATE_H__

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

#include <string>

#include "NEngine/Types/Vec2.h"

namespace NE { class SpriteLoader; }
namespace CE { class AnimatedSprite; }

class Params;

class UnitTemplate
{
private:

    std::string internalName;       /*!< */
    std::string name;               /*!< Name to display */
    unsigned int id;                /*!< */

    CE::AnimatedSprite* pSprite;        /*!< */
    CE::AnimatedSprite* pSpriteGreyed;        /*!< */
    UVec2 size;

    unsigned short int faction;     /*!< */

    unsigned int movement;          /*!< The movement possibility */
    unsigned int fuel;              /*!< The remaining fuel */
    unsigned int fuelConsumption;   /*!< The fuel consumption per day */
    unsigned int ammo;              /*!< The remaining ammo */

    unsigned int life;              /*!< The life */

    unsigned int price;             /*!< Price */

    Params* pParams;                /*!< Rest of the information for this unit */

    static const std::string neededParameters[];    /*!< List of parameters needed for the constructor */

public:
    UnitTemplate():pParams(NULL) {};
    UnitTemplate(Params* const pParams, NE::SpriteLoader* pSL, const std::string& folderPath);
    ~UnitTemplate();

    unsigned int getID()const { return id; }
        const std::string& getInternalName()const { return internalName; }
    const std::string& getName()const { return name; }

    CE::AnimatedSprite* getSprite()const { return pSprite; }
    CE::AnimatedSprite* getSpriteGreyed()const { return pSpriteGreyed; }

    unsigned short int getFaction()const { return faction; }

    unsigned int getMovement()const { return movement; }
    unsigned int getFuel()const { return fuel; }
    unsigned int getFuelConsumption()const { return fuelConsumption; }
    unsigned int getAmmo()const { return ammo; }
    unsigned int getLife()const { return life; }
    unsigned int getPrice()const { return price; }

    const Params* getParams()const { return pParams; }
};

/*! \class UnitTemplate UnitTemplate.h "Game/GameState/GameObjects/UnitTemplate.h"
 *  \brief UnitTemplate keeping all the information loaded for units
 */

/*! \fn UnitTemplate :: UnitTemplate()
 */

/*! \fn UnitTemplate :: UnitTemplate(Params* const pParams, NE::SpriteLoader* pSL, const std::string& folderPath)
 *  \param pParams the parameters where to get the information for this unit template
 *  \param pSL a pointer to the sprite loader to use
 *  \param folderPath the folder where to load data
 */

/*! \fn UnitTemplate :: ~UnitTemplate()
 */

/*! \fn unsigned int UnitTemplate :: getID()const
 *  \return
 */

/*! \fn const std::string& UnitTemplate :: getInternalName()const
 *  \return
 */

/*! \fn const std::string& UnitTemplate :: getName()const
 *  \return
 */

/*! \fn CE::AnimatedSprite* UnitTemplate :: getSprite()const
 *  \return
 */

/*! \fn unsigned short int UnitTemplate :: getFaction()const
 *  \return
 */

/*! \fn unsigned int UnitTemplate :: getMovement()const
 *  \return
 */

/*! \fn unsigned int UnitTemplate :: getFuel()const
 *  \return
 */

/*! \fn unsigned int UnitTemplate :: getFuelConsumption()const
 *  \return
 */

/*! \fn unsigned int UnitTemplate :: getAmmo()const
 *  \return
 */

/*! \fn unsigned int UnitTemplate :: getLife()const
 *  \return
 */

/*! \fn unsigned int UnitTemplate :: getPrice()const
 *  \return
 */

/*! \fn const Params* UnitTemplate :: getParams()const
 *  \return
 */

#endif
