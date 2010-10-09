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

struct SDL_Surface;

class SpriteManager;
class Renderer;
class Window;
class Sprite;
class AnimatedSprite;

class View
{
protected:

	AnimatedSprite* pASprite;	/*!< The sprite to draw */
	
public:

	int positionX;				/*!< The position in the TileBar */

	//! Constructor for the View
	/*!
		Will fill the class with the params
		\param pASprite the AnimatedSprite to dislay
		\param positionX the position in the TileBar
	*/
	View(AnimatedSprite* pASprite, const int positionX):pASprite(pASprite),positionX(positionX) {}

	//! Basic destructor
	/*!
	*/
	virtual ~View() {}

	//! Get the sprite to display
	/*!
		\return the sprite to display
	*/
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
	Sprite* pBarSprite;						/*<! The surface for the bar */
	Sprite* pBarCursor;						/*<! The surface for the cursor */
	AnimatedSprite* pBarArrows;				/*<! Up / Down arrows */

	int counterMovementAnim;				/*<! counter to know how much to move on the left or right */
	unsigned int positionY;					/*<! position of the bar on the y axis */
	unsigned int limit;						/*<! The limit of space needed by all the tiles to be displayed */
	UVec2 windowSize;						/*<! The size of the window where the bar is */
	TileBarState state;						/*<! The actual animation state of the bar */

	bool valid;								/*<! flag to know if all initialisation goes right */


	//! Start to move the tile on the right (cursor move on the left)
	/*!
	*/
	void moveLeft(void);

	//! Start to move the tile on the left (cursor move on the right)
	/*!
	*/
	void moveRight(void);

	//! Change the Y dimension of the TileBar 
	/*!
	*/
	void moveUp(void);

	//! Change the Y dimension of the TileBar 
	/*!
	*/
	void moveDown(void);

protected:

	//!The tiles to be displayed in the TileBar
    /*!
    */
	std::vector<std::vector<View*> > viewList;

	//!index of the actual Tile selected on the X axis
    /*!
    */
	int currentX;	

	//! index of the actual Tile selected on the Y axis
    /*!
    */
	int currentY;

public:
	//! Basic constructor
	/*!
	  Will create the surface for the Bar and load the bar cursor and Tiles
	  \param sm The SpriteManager to use to load the images
	  \param win The window where the bar will be
	  \param listTiles The list of tiles to display in the TileBar
	*/
	TileBar(SpriteManager& sm, const Window& win, std::vector<View *>& listTiles);

	//! Basic destructor
	/*!
	*/
	virtual ~TileBar(void);

	//! Start the opening animation of the Bar
	/*!
	*/
	void open(void);

	//! Start closing animation
	/*!
	*/
	void close(void);

	//! Move the TileBar following the direction pressed
	/*!
	  \param direction the direction to move to
	*/
	void move(const ArrowsDirection direction);

	//! Draw the Bar
	/*!
	  \param r the Renderer to use
	  \param time Time used for the animations
	*/
	bool draw(const Renderer& r, const unsigned int time);

	//! Update the states / do the animation
	/*!
	  \param time the time for the animation well going
	*/
	void update(const unsigned int time);

	//! Get if all the initialisation succeed
	/*!
	  \return true if no problem reported
	*/
	bool isValid(void)const { return valid; }

	//! Get if the Bar is actually opened
	/*!
	  \return true if the bar is opened
	*/
	bool isOpened(void)const { if ( state != TBS_Closed && state != TBS_Closing ) return true; else return false; }

	//! Get if the Bar is actually closed
	/*!
	  \return true if the bar is closed
	*/
	bool isClosed(void)const { if ( state == TBS_Closed  ) return true; else return false; }
};

/*! \struct View Tile.h "Game/Tile.h"
 *  \brief View struct
 *
 * Used to give a structure usable in the TileBar 
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

#endif
#endif // EDITOR