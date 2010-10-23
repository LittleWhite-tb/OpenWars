#ifndef __CONSTRUCTBOX_H__
#define __CONSTRUCTBOX_H__

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
#include <string>

#include "../Game/Unit.h"

#include "../Engine/Controls/Keyboard.h"

#include "../Types/Vec2.h"

class SpriteManager;
class FontManager;
class Renderer;
class Window;

class Sprite;
class AnimatedSprite;
class Font;

struct ConstructUnitView
{
	UnitType unitType;				/*!< Unit type */
	AnimatedSprite* pUnitSprite;	/*!< sprite for the unit */
	std::string unitName;			/*!< name of the unit */
	unsigned int unitPrice;			/*!< price of the unit */

	//! Basic constructor
	/*!
	  \param unitType type of the unit
	  \param pUnitSprite sprite to use for the unit
	  \param unitName name of the unit
	  \param unitPrice price of the unit
	*/
	ConstructUnitView(const UnitType unitType, AnimatedSprite* const pUnitSprite, const std::string& unitName, const unsigned int unitPrice)
		:unitType(unitType),pUnitSprite(pUnitSprite),unitName(unitName),unitPrice(unitPrice) {}
};

class ConstructBox
{
private:

	Sprite* pBackgroundUI;							/*!< sprite for the background */
	Sprite* pCursor;								/*!< sprite for the cursor */
	Sprite* pUpArrow;								/*!< sprite for the up arrow */
	Sprite* pDownArrow;								/*!< sprite for the down arrow */

	Font* pFont;									/*!< Font used for the texts */
	Font* pFontGrey;								/*!< Font used for the texts when no enough money (in grey)*/

	UVec2 windowSize;								/*!< Size of the window where to draw the UI */

	std::vector<ConstructUnitView> unitsList;		/*!< list of units */
	unsigned int actualPosition;					/*!< actual position of the cursor */
	unsigned int offsetCursorPosition;				/*!< offset for the list of units */

public:
	//! Basic constructor
	/*!
	  \param sm the sprite manager to load the sprites
	  \param fm the font manager to load the fonts
	  \param win the window to draw in
	  \param backgroundFileName the path to the sprite to load for the background
	  \param cursorFileName the path to the sprite to load for the cursor
	  \param upArrowFileName the path to the sprite to load for the up arrow
	  \param downArrowFileName the path to the sprite to load for the down arrow
	  \param fontFileName the path to the font to load for the texts
	  \param unitsList the list of units to display
	*/
	ConstructBox(SpriteManager& sm, FontManager& fm, const Window& win, const std::string& backgroundFileName, const std::string& cursorFileName, const std::string& upArrowFileName,
		const std::string& downArrowFileName, const std::string& fontFileName, const std::vector<ConstructUnitView>& unitsList);
	
	//! Basic destructor
	/*!
	*/
	~ConstructBox(void);


	//! Draw the construct box
	/*!
	  \param r the renderer to use to draw the UI
	  \param moneyAvailable the money that the user have
	  \return true if all goes right
	*/
	bool draw(const Renderer& r, const unsigned int moneyAvailable);

	//! Update the construct box
	/*!
	  Move the cursor following the keys pressed
	  \param kd the key direction pressed
	*/
	void update(const ArrowsDirection kd);

	//! Get the unit type currently selected
	/*!
	  \return The unit type of the unit currently selected
	*/
	UnitType getUnitSelected(void)const;
};

/*! \class ConstructBox ConstructBox.h "UI/ConstructBox.h"
 *  \brief User interface for the ordering unit production
 *
 * The ContructBox show a list of unit with name and price that we can build
 */

/*! \struct ConstructUnitView ConstructBox.h "Game/ConstructBox.h"
 *  \brief ConstructUnitView struct
 *
 * Used to give a structure usable in the ConstructBox to contain Unit
 */

#endif