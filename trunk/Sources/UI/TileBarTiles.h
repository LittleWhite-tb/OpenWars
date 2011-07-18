#ifdef EDITOR
#ifndef __TILEBARTILES_H__
#define __TILEBARTILES_H__

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

#include "TileBar.h"

#include "Game/Tile.h"

namespace NE { class SpriteLoader; }
namespace NE { class SpriteFactory; }

class Theme;
class AnimatedSprite;

class TileView : public View
{	
private:
	const Tile* pTile;							/*!< The type of the Tile */					

public:
	TileView(const Tile* const pTile, unsigned int positionX):View(pTile->getSprite(),positionX),pTile(pTile) {}

	const Tile* getTile()const { return pTile; }
};

class TileBarTiles : public TileBar
{
private:

public:
	TileBarTiles(NE::SpriteFactory* const pSF, const Theme* pTheme, std::vector<TileView*>& listTiles, const USize2& windowSize);

	const Tile* getSelected(void)const;
};

/*! \struct TileView TileBarTiles.h "Game/TileBarTiles.h"
 *  \brief TileView struct
 *
 * Used to give a structure usable in the TileBar to contain Tile
 */

/*! \fn TileView::TileView(const Tile* const pTile, unsigned int positionX)
 * \brief Will fill the class with the params
 * \param pTile the Tile to keep
 * \param positionX the position in the TileBar
 */

/*! \fn const Tile* TileView::getTile()const
 * \brief Return the Tile kept
 * \return the pointer of the Tile
 */

/*! \class TileBarTiles TileBarTiles.h "UI/TileBarTiles.h"
 *  \brief Display a bar with a list of Tiles
 *
 *	Specialisation for the TileBar to display tiles
 *
 */

/*! \fn TileBarTiles::TileBarTiles(NE::SpriteLoader* const pSL, NE::SpriteFactory* const pSF, std::vector<TileView*>& listTiles, const USize2& windowSize)
 * Create a TileBar with tiles
 * \param pSL the SpriteLoader to load the sprites used by the map
 * \param pSF the SpriteFactory to create some Sprite
 * \param listTiles The list of tiles to display in the TileBar
 * \param windowSize the size of the window (used as reference to place the TileBar)
 */

/*! \fn const Tile* TileBarTiles::getSelected(void)const
 * \brief Get the Tile selected
 * \return the pointer of the Tile selected in the Bar
 */

#endif
#endif
