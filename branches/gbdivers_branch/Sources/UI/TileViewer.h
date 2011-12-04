#ifndef __TILEVIEWER_H__
#define __TILEVIEWER_H__

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

#include "Game/GameState/GameObjects/Tile.h"

#include "Types/Size2.h"
#include "Types/Vec2.h"

namespace NE { class Sprite; }
namespace NE { class Renderer; }

class Theme;
class AnimatedSprite;
class Font;

class Tile;
class UnitTemplate;

class TileViewer
{
private:

	Font* pFont;				/*!< the font to use */
	AnimatedSprite* pBackground;		/*!< the sprite for the background */
	AnimatedSprite* pTileSprite;	/*!< the tile to display in the UI */

	std::string title;				/*!< the title to display */
	std::string tileName;			/*!< the name for the tile to display */

	USize2 windowSize;				/*!< The window size */
	IVec2 position;					/*!< the UI position */

public:
	TileViewer(const Theme* pTheme, const USize2& windowSize);
	~TileViewer();

	void setTile(const Tile* pTile);
	void setTile(const UnitTemplate* pUnitTemplate);

	void setTitle(const std::string& title) { this->title = title; }

	void putOnLeft(void);
	void putOnRight(void);

	bool draw(const NE::Renderer& r, const unsigned int time);
};

/*! \class TileViewer TileViewer.h "UI/TileViewer.h"
 *  \brief viewer for Tile for the editor to indicate which tile is selected
 */

/*! \fn TileViewer::TileViewer(const Theme* pTheme, const USize2& windowSize)
 * \param pTheme pointer to the theme to use
 * \param windowSize the size of the window (used as reference to place the viewer)
 */

/*! \fn TileViewer::~TileViewer(void)
 */

/*! \fn void TileViewer::setTile(const Tile* pTile)
 * \brief Set a new tile to show
 * \param pTile pointer on the tile to show
 */

/*! \fn void TileViewer::setTile(const UnitTemplate* pUnitTemplate)
 * \brief Set a new unit to show
 * \param pUnitTemplate pointer to the Unit to show
 */

/*!	\fn void TileViewer :: setTitle(const std::string& title)
 *	\brief set a new title
 *	\param title the new title to display
 */

/*! \fn void TileViewer::putOnLeft(void)
 * \brief Set the UI on the left of the screen
 */

/*! \fn void TileViewer::putOnRight(void)
 * \brief Set the UI on the right of the screen
 */

/*! \fn bool TileViewer::draw(const NE::Renderer& r, const unsigned int time)
 *	\brief draw the UI
 *	\param r the NE::Renderer to use to draw the viewer
 *	\param time the actual time in the game
 *	\return true if all goes right
 */

#endif
