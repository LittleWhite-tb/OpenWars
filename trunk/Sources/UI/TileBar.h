#ifdef EDITOR
#ifndef __TILEBAR_H__
#define __TILEBAR_H__

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

#include <vector>
#include <utility>

#include "../Game/Tile.h"

#include "../Engine/Controls/Keyboard.h"

#include "../Types/Vec2.h"
#include "../Types/Size2.h"

struct SDL_Surface;

namespace NE { class SpriteLoader; }
namespace NE { class SpriteFactory; }
namespace NE { class Renderer; }
namespace NE { class Sprite; }
class AnimatedSprite;

class View
{
protected:

	AnimatedSprite* pASprite;	/*!< The sprite to draw */
	
public:

	int positionX;				/*!< The position in the TileBar */

	View(AnimatedSprite* pASprite, const int positionX):pASprite(pASprite),positionX(positionX) {}
	virtual ~View() {}

	AnimatedSprite* getSprite(void) { return pASprite; }
};

class TileBar
{
	enum TileBarState
	{
		TBS_Opening,
		TBS_Opened,
		TBS_MoveLeft,
		TBS_MoveRight,
		TBS_Closing,
		TBS_Closed
	};

private:
	NE::Sprite* pBarSprite;						/*!< The surface for the bar */
	NE::Sprite* pBarCursor;						/*!< The surface for the cursor */
	AnimatedSprite* pBarArrows;				/*!< Up / Down arrows */

	int counterMovementAnim;				/*!< counter to know how much to move on the left or right */
	unsigned int positionY;					/*!< position of the bar on the y axis */
	unsigned int limit;						/*!< The limit of space needed by all the tiles to be displayed */
	USize2 windowSize;						/*!< The size of the window where the bar is */
	TileBarState state;						/*!< The actual animation state of the bar */

	unsigned int stepX;						/*!< Speed of the animation of the tile bar on the X axis */
	unsigned int stepY;						/*!< Speed of the animation of the tile bar on the Y axis */

	bool valid;								/*!< flag to know if all initialisation goes right */

	void moveLeft(const float scalingFactor);
	void moveRight(const float scalingFactor);
	void moveUp(void);
	void moveDown(void);

protected:
	std::vector<std::vector<View*> > viewList;	/*!< The tiles to be displayed in the TileBar */
	int currentX;				/*!< index of the actual Tile selected on the X axis */
	int currentY;				/*!< index of the actual Tile selected on the Y axis */

public:
	TileBar(NE::SpriteLoader* const pSL, NE::SpriteFactory* const pSF, std::vector<View *>& listTiles, const USize2& windowSize, const float scalingFactor);
	virtual ~TileBar(void);

	void open(void);
	void close(void);

	void move(const ArrowsDirection direction,const float scalingFactor);

	bool draw(const NE::Renderer& r, const unsigned int time, const float scalingFactor);

	void update(const unsigned int time, const float scalingFactor);

	bool isValid(void)const { return valid; }

	bool isOpened(void)const { if ( state != TBS_Closed && state != TBS_Closing ) return true; else return false; }
	bool isClosed(void)const { if ( state == TBS_Closed  ) return true; else return false; }
};

/*! \struct View Tile.h "Game/Tile.h"
 *  \brief View struct
 *
 * Used to give a structure usable in the TileBar 
 */

/*! \fn View::View(AnimatedSprite* pASprite, const int positionX)
 * Will fill the class with the params
 * \param pASprite the AnimatedSprite to dislay
 * \param positionX the position in the TileBar
 */

/*! \fn virtual View::~View()
 */

/*! \fn AnimatedSprite* View::getSprite(void)
 * \brief Get the sprite to display
 * \return the sprite to display
 */

/*! \class TileBar TileBar.h "UI/TileBar.h"
 *  \brief Display a bar with a list of sprites
 *
 *	The bar is compose of three parts:
 *		- The bar itself (auto generated surface, half transparent)
 *		- The cursor
 *		- The tiles (displayed in a line)
 *
 *	The bar have 4 animations:
 *		- Opening
 *		- Closing
 *		- Move the tile on the left
 *		- Move the tile on the right
 *
 *
 */

 /*! \fn void TileBar::moveLeft(void)
  * \brief Start to move the tile on the right (cursor move on the left)
  */

/*! \fn void TileBar::moveRight(void)
 * \brief Start to move the tile on the left (cursor move on the right)
 */

/*! \fn void TileBar::moveUp(void)
 * \brief Change the Y dimension of the TileBar 
 */

/*! \fn void TileBar::moveDown(void)
 * \brief Change the Y dimension of the TileBar 
 */

/*! \fn TileBar::TileBar(SpriteManager& sm, std::vector<View *>& listTiles, const USize2& windowSize)
 * Will create the surface for the Bar and load the bar cursor and Tiles
 * \param sm The SpriteManager to use to load the images
 * \param listTiles The list of tiles to display in the TileBar
 * \param windowSize the size of the window (used as reference to place the TileBar)
 */

/*! \fn virtual TileBar::~TileBar(void)
 */

/*! \fn void TileBar::open(void)
 * \brief Start the opening animation of the Bar
 */

/*! \fn void TileBar::close(void)
 * \brief Start closing animation
 */

/*! \fn void TileBar::move(const ArrowsDirection direction)
 * \brief Move the TileBar following the direction pressed
 * \param direction the direction to move to
 */

/*! \fn bool TileBar::draw(const NE::Renderer& r, const unsigned int time)
 * \brief Draw the Bar
 * \param r the NE::Renderer to use to draw the TileBar
 * \param time Time used for the animations
 * \return true if all goes right
 */

/*! \fn void TileBar::update(const unsigned int time)
 * \brief Update the states / do the animation
 * \param time the time for the animation well going
 */

/*! \fn bool TileBar::isValid(void)const
 * \brief Get if all the initialisation succeed
 * \return true if no problem reported
 */

/*! \fn bool TileBar::isOpened(void)const
 * \brief Get if the Bar is actually opened
 * \return true if the bar is opened
 */

/*! \fn bool TileBar::isClosed(void)const
 * \brief Get if the Bar is actually closed
 * \return true if the bar is closed
 */

#endif
#endif // EDITOR
