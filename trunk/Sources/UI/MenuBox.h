#ifndef __MENUBOX_H__
#define __MENUBOX_H__

#ifndef DOXYGEN_IGNORE_TAG
/**
OpenAWars is an open turn by turn strategic game ai, const float scalingFactorming to recreate the feeling of advance (famicon) wars (c)
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
#include <vector>

#include "../NEngine/InputManager.h"

#include "../Engine/AnimatedSprite.h"

#include "../Types/Vec2.h"

namespace NE { class SpriteLoader; }
namespace NE { class SpriteFactory; }
namespace NE { class Sprite; }
namespace NE { class Renderer; }
class Font;
class Theme;

class MenuBox
{
	struct MenuItem
	{
		std::string actionName;			/*!< id of the entry */
		std::string displayName;			/*!< name to display */
		AnimatedSprite* pASprite;	/*!< sprite to display */

		MenuItem(const std::string& actionName, AnimatedSprite* const pASprite, const std::string& displayName)
			:actionName(actionName),displayName(displayName),pASprite(pASprite) {}
	};

private:


	NE::Sprite* pBackground;				/*!< background for the UI (generated on the fly by the constructor) */
	AnimatedSprite* pCursor;			/*!< cursor */
	Font* pFont;						/*!< font for the texts */

	unsigned int windowXPosition;		/*!< Window width */
	unsigned int actualPosition;		/*!< actual position of the cursor */

	std::vector<MenuItem> entries;    /*!< entries in the UI */

public:
	MenuBox(NE::SpriteFactory* const pSF, const Theme* pTheme, const USize2& winSize);

	void add(const std::string& actionName, AnimatedSprite* const pSprite, const std::string& displayName);

	bool draw(const NE::Renderer& r, const UVec2& cursorPosition, const unsigned int time);

	void update(const NE::InputManager::ArrowsDirection kd);

	const std::string& getSelectedActionName(void) { return entries[actualPosition].actionName; }
};

/*! \class MenuBox MenuBox.h "UI/MenuBox.h"
 *  \brief User interface to display menus
 *
 * The MenuBox show a little box with multiple entries to let the user select actions
 * The background is constructed on the fly, so it needs special precaution.
 */

/*! \fn MenuBox::MenuBox(NE::SpriteFactory* const pSF, const Theme* pTheme, const USize2& winSize)
 * \param pSF The SpriteFactory to load the sprites
 *	\param pTheme a pointer to the Theme to use
 * \param winSize the size of the window (used as reference to place the MenuBox)
 */

/*!	\fn void MenuBox::add(const std::string& actionName, AnimatedSprite* const pSprite, const std::string& displayName)
 *	\brief add an entry in the menu
 *	\param actionName the name of the action
 *	\param pSprite a pointer to the sprite to display with this entry
 *	\param displayName the name to display
 */

/*! \fn bool MenuBox::draw(const NE::Renderer& r, const UVec2& cursorPosition, const unsigned int time)
 * \brief Draw the construct box
 * \param r the NE::Renderer to use to draw the MenuBox
 * \param cursorPosition the position of the cursor (to place the UI)
 * \param time the actual time
 * \return true if all goes right
 */

/*! \fn void MenuBox::update(const NE::InputManager::ArrowsDirection kd)
 * \brief Update the construct box
 * Move the cursor following the keys pressed
 * \param kd the key direction pressed
 */

/*! \fn const std::string& MenuBox::getSelectedActionName(void)
 * \brief Get the actually selected action name
 * \return The action name actually selected
 */

/*! \struct MenuBox::MenuItem MenuBox.h "UI/MenuBox.h"
 *  \brief MenuItem struct
 *
 * Used to give a structure usable in the MenuBox to contain an entry
 */

/*! \fn MenuBox::MenuItem::MenuItem(const std::string& actionName, AnimatedSprite* const pASprite, const std::string& displayName)
 * \param actionName the name of the action
 * \param pASprite a pointer to the sprite to display
 * \param displayName the name to display
 */

#endif
