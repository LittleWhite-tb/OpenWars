#ifndef __THEME_H__
#define __THEME_H__

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
#include <map>

#include "Engine/Library.h"

#include "Game/Tile.h"
#include "Game/UnitTemplate.h"
#include "Game/UnitTemplateFactionList.h"
#include "UI/UIType.h"

namespace NE { class SpriteLoader; }

class Theme
{
private:

    std::string name;		/*!< */

	Library<Tile> tiles;			/*!< */
	Library<UnitTemplate> units;	/*!< */
	// Library<UIObject>

public:
	Theme() {}
    Theme(const std::string& name):name(name) {}
    ~Theme(void);

    bool load(NE::SpriteLoader* const pSL);

	bool containsTile(unsigned int id)const;
	bool containsTile(const std::string& tileName)const;
	const Tile* getTile(unsigned int id)const;
    const Tile* getTile(const std::string& tileName)const;
	void getTilesList(std::list< const Tile* >* pTilesList)const;

	bool containsUnit(unsigned int id)const;
	bool containsUnit(const std::string& unitName)const;
	const UnitTemplate* getUnit(unsigned int id)const;
	const UnitTemplate* getUnit(const std::string& unitName, const unsigned int faction)const;
	void getUnitsList(std::list< const UnitTemplateFactionList* >* pUnitsList)const;

    // AnimatedSprite* getUI(const UIType uType);

    const std::string& getName()const { return name; }
};

/*! \class Theme Theme.h "Game/Theme.h"
 *  \brief The Theme is a list of sprites needed to the game
 *	The sprites are separated in three groups:
 *
 *	- Tiles
 *	- Units
 *	- UI
 */

/*!	\fn Theme :: Theme()
 */

/*!	\fn Theme :: Theme(const std::string& name)
 *	\param name of the theme
 */

/*!	\fn Theme :: ~Theme()
 */

/*!	\fn bool Theme :: load(NE::SpriteLoader* const pSL)
 *	\brief load the theme from XML files, using the pSL SpriteLoader
 *	\param pSL pointer on the SpriteLoader to use
 *	\return true if all goes right; false if XML parsing failed
 */

/*!	\fn bool Theme :: containsTile(unsigned int id)const
 *	\brief Checks if the id is contained in the tiles library
 *	\param id
 *	\return true if the id is contained in the library
 */

/*!	\fn bool Theme :: containsTile(const std::string& tileName)const;
 *	\brief Checks if the tileName is contained in the tiles library
 *	\param tileName
 *	\return true if the tileName is contained in the library
 */

/*!	\fn const Tile* Theme :: getTile(unsigned int id)const;
 *	\brief Gets the tile corresponding to id
 *	\param id
 *	\return a tile pointer or NULL if not found
 */

/*!	\fn const Tile* Theme :: getTile(const std::string& tileName)const;
 *	\brief Gets the tile correspoding to tileName
 *	\param tileName
 *	\return a tile pointer
 */

/*!	\fn void Theme :: getTilesList(std::list< const Tile* >* pTilesList)const;
 *	\brief Gets the list of Tiles in the Theme
 *	\param pTilesList the list to fill
 */

/*!	\fn bool Theme :: containsUnit(unsigned int id)const;
 *	\brief Checks if the id is contained in the units library
 *	\param id
 *	\return true if the id is contained in the library
 */

/*!	\fn bool Theme :: containsUnit(const std::string& unitName)const;
 *	\brief Checks if the unitName is contained in the units library
 *	\param unitName
 *	\return true if the unitName is contained in the library
 */

/*!	\fn const UnitTemplate* Theme :: getUnit(unsigned int id)const;
 *	\brief Gets the unit corresponding to id
 *	\param id
 *	\return a unit pointer or NULL if not found
 */

/*!	\fn const UnitTemplate* Theme :: getUnit(const std::string& unitName, const unsigned int faction)const;
 *	\brief Gets the unit correspoding to unitName and in the faction
 *	\param unitName
 *	\param faction
 *	\return a unit pointer
 */

/*!	\fn void Theme :: getUnitsList(std::list< const UnitTemplateFactionList* >* pUnitsList)const;
 *	\brief Gets the list of Unit in the Theme
 *	\param pUnitsList the list to fill
 */

/*!	\fn const std::string& Theme :: getName()const
 *	\return
 */

#endif
