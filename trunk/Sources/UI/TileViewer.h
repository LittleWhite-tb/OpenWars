#ifdef EDITOR
#ifndef __TILEVIEWER_H__
#define __TILEVIEWER_H__

#ifndef DOXYGEN_IGNORE_TAG
/**
OpenAWars is an open turn by turn strategic game aiming to recreate the feeling of advance (famicon) wars (c)
Copyright (C) 2010  Alexandre LAURENT

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

#include "../Game/Tile.h"

#include "../Types/Vec2.h"

class SpriteManager;
class FontManager;
class Renderer;
class Font;
class Sprite;
class AnimatedSprite;

class TileViewer
{
private:

	Font* pFont;				/*!< the font to use */
	Sprite* pBackground;		/*!< the sprite for the background */
	 AnimatedSprite* pTileSprite;	/*!< the tile to display in the UI */

	std::string title;				/*!< the title to display */
	std::string tileName;			/*!< the name for the tile to display */

	USize2 windowSize;				/*!< The window size */
	IVec2 position;					/*!< the UI position */

public:
	TileViewer(SpriteManager& sm, FontManager& fm, const std::string& fileNameBackground, const std::string& fileNameFont,  const USize2& windowSize);
	~TileViewer(void);

	void setTile(AnimatedSprite* const pTileSprite, const std::string tileName) { this->pTileSprite = pTileSprite; this->tileName = tileName; }

	void setTitle(const std::string& title) { this->title = title; }

	void putOnLeft(void);
	void putOnRight(void);

	bool draw(const Renderer& r);
};

/*! \class TileViewer TileViewer.h "Engine/TileViewer.h"
 *  \brief viewer for Tile for the editor to indicate which tile is selected
 *
 *	We can:
 *		- Change the title
 *		- Change the positio ( on left or right of the screen )
 *		- Change the tile
 */

/*! \fn TileViewer::TileViewer(SpriteManager& sm, FontManager& fm, const std::string& fileNameBackground, const std::string& fileNameFont)
 * Will load the font and the background
 * \param sm The SpriteManager to use to load the background
 * \param fm The FontManager to use to load the font
 * \param fileNameBackground The file for the background
 * \param fileNameFont The file for the font
 */

/*! \fn TileViewer::~TileViewer(void)
 */

/*! \fn void TileViewer::setTile(AnimatedSprite* const pTileSprite, const std::string tileName)
 * \brief Set the tile to display
 * \param pTileSprite the new sprite to display
 * \param tileName the name of the tile to display
 */

/*! \fn void TileViewer::setTitle(const std::string& title)
 * \brief Set a new title to display
 * \param title the new title
 */

/*! \fn void TileViewer::putOnLeft(void)
 * \brief Set the UI on the left of the screen
 */

/*! \fn void TileViewer::putOnRight(void)
 * \brief Set the UI on the right of the screen
 */

/*! \fn bool TileViewer::draw()
 * draw the UI
 * \return true if all goes right
 */

#endif
#endif
