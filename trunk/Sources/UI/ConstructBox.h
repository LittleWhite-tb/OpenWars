#ifndef __CONSTRUCTBOX_H__
#define __CONSTRUCTBOX_H__

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

#include <vector>
#include <string>

#include "NEngine/InputManager.h"

#include "Game/GameState/GameObjects/Unit.h"

#include "Types/Size2.h"

namespace NE { class Renderer; }

class Theme;
class AnimatedSprite;
class Font;
class UnitTemplateFactionList;

class ConstructBox
{
private:

	AnimatedSprite* pBackgroundUI;							/*!< sprite for the background */
	AnimatedSprite* pCursor;								/*!< sprite for the cursor */
	AnimatedSprite* pUpArrow;								/*!< sprite for the up arrow */
	AnimatedSprite* pDownArrow;								/*!< sprite for the down arrow */

	Font* pFont;									/*!< Font used for the texts */
	Font* pFontGrey;								/*!< Font used for the texts when no enough money (in grey)*/

	USize2 windowSize;								/*!< Size of the window where to draw the UI */

	std::vector<const UnitTemplateFactionList*> unitsList;		/*!< list of units */
	unsigned int actualPosition;					/*!< actual position of the cursor */
	unsigned int offsetCursorPosition;				/*!< offset for the list of units */

public:
	ConstructBox(const Theme* pTheme, const USize2& windowSize);
	~ConstructBox(void);

	void add(const UnitTemplateFactionList* pListUnitTemplate);

	bool draw(const NE::Renderer& r, const unsigned int faction, const unsigned int moneyAvailable, unsigned int time);

	void update(const NE::InputManager::ArrowsDirection kd);

	const UnitTemplate* getUnitSelected(const unsigned int faction)const;
};

/*! \class ConstructBox ConstructBox.h "UI/ConstructBox.h"
 *  \brief User interface to select a unit in a list (to buy it)
 */

/*! \fn ConstructBox::ConstructBox(const Theme* pTheme, const USize2& windowSize)
 * \param pTheme a pointer to the Theme to use
 * \param windowSize the size of the window (used to place the ConstructBox)
 */

/*! \fn ConstructBox::~ConstructBox(void)
 */

/*! \fn void ConstructBox::add(const UnitTemplateFactionList* pListUnitTemplate)
 *	\brief add a new unit in the list of unit that we can construct
 *	\param pListUnitTemplate the pointer to the new unit to add
 */

/*! \fn bool ConstructBox::draw(const NE::Renderer& r, const unsigned int faction, const unsigned int moneyAvailable, unsigned int time)
 * \brief Draw the construct box
 * \param r the NE::Renderer used to draw
 *	\param faction the faction to display
 * \param moneyAvailable the money that the user have
 * \param time the actual time in the game
 * \return true if all goes right
 */

/*! \fn void ConstructBox::update(const NE::InputManager::ArrowsDirection kd)
 * \brief Update the construct box
 * Move the cursor following the keys pressed
 * \param kd the key direction pressed
 */

/*! \fn UnitTemplate ConstructBox::getUnitSelected(const unsigned int faction)const
 * \brief Get the unit type currently selected
 *	\param faction the faction of the unit to return
 * \return a pointer to the unit actually selected
 */

#endif
