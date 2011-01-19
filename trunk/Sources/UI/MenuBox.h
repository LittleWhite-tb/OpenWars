#ifndef __MENUBOX_H__
#define __MENUBOX_H__

#ifndef DOXYGEN_IGNORE_TAG
/**
OpenAWars is an open turn by turn strategic game ai, const float scalingFactorming to recreate the feeling of advance (famicon) wars (c)
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

#include <string>
#include <vector>

#include "../Engine/AnimatedSprite.h"
#include "../Engine/Controls/Keyboard.h"

#include "../Types/Vec2.h"

namespace NE { class SpriteLoader; }
namespace NE { class SpriteFactory; }
namespace NE { class Sprite; }
class FontManager;
namespace NE { class Renderer; }
class Font;

enum MenuEntry
{
    ME_Move,
    
	ME_EndTurn,
	ME_Quit,
};

struct MenuView
{
	std::string name;			/*!< name to display */
	MenuEntry entry;			/*!< id of the entry */
	AnimatedSprite* pASprite;	/*!< sprite to display */

	MenuView(const std::string& name, const MenuEntry entry, AnimatedSprite* const pASprite):name(name),entry(entry),pASprite(pASprite) {}
    ~MenuView() { delete pASprite; }
};

class MenuBox
{
private:
	NE::Sprite* pBackground;				/*!< background for the UI (generated on the fly by the constructor) */
	AnimatedSprite* pCursor;			/*!< cursor */
	Font* pFont;						/*!< font for the texts */

	unsigned int windowXPosition;		/*!< Window width */
	unsigned int actualPosition;		/*!< actual position of the cursor */

	std::vector<MenuView*> entries;    /*!< entries in the UI */

public:
	MenuBox(NE::SpriteLoader* const pSL, NE::SpriteFactory* const pSF, FontManager& fm, const std::string& cursorFileName, const std::string& fontFileName, std::vector<MenuView*> entries, const USize2& winSize);
	~MenuBox(void);

	bool draw(const NE::Renderer& r, const UVec2& cursorPosition, const unsigned int time);

	void update(const ArrowsDirection kd);

	MenuEntry getActualEntry(void) { return entries[actualPosition]->entry; }
    
    void setMenus(std::vector<MenuView*> newEntries) { entries = newEntries; }
};

/*! \class MenuBox MenuBox.h "UI/MenuBox.h"
 *  \brief User interface to display menus
 *
 * The MenuBox show a little box with multiple entries to let the user select actions
 * The background is constructed on the fly, so it needs special precaution.
 */

/*! \fn MenuBox::MenuBox(SpriteManager& sm, FontManager& fm, const std::string& cursorFileName, const std::string& fontFileName, std::vector<MenuView*> entries, const USize2& winSize)
 * \param sm The sprite manager to load the sprites
 * \param fm The font manager to load the fonts
 * \param cursorFileName the file to load for the cursor
 * \param fontFileName the font to load for the texts
 * \param winSize the size of the window (used as reference to place the MenuBox)
 * \param entries the entries to display in the UI
 */

/*! \fn MenuBox::~MenuBox(void)
 */

/*! \fn bool MenuBox::draw(const NE::Renderer& r, const UVec2& cursorPosition, const unsigned int time)
 * \brief Draw the construct box
 * \param r the NE::Renderer to use to draw the MenuBox
 * \param cursorPosition the position of the cursor (to place the UI)
 * \param time the actual time
 * \return true if all goes right
 */

/*! \fn void MenuBox::update(const ArrowsDirection kd)
 * \brief Update the construct box
 * Move the cursor following the keys pressed
 * \param kd the key direction pressed
 */

/*! \fn MenuEntry MenuBox::getActualEntry(void)
 * \brief Get the actual element selected
 * \return The MenuEntry of the element currently selected
 */

/*! \fn void MenuBox::setMenus(std::vector<MenuView*> newEntries)
 * \brief Change the menus in the box
 * \param newEntries the new entries to show
 */

/*! \struct MenuView MenuBox.h "UI/MenuBox.h"
 *  \brief MenuView struct
 *
 * Used to give a structure usable in the MenuBox to contain an entry
 */

/*! \fn MenuView::MenuView(const std::string& name, const MenuEntry entry, AnimatedSprite* const pASprite)
 * Note: The AnimatedSprite will be deleted by the parent UI
 * \param name the name to display for this entry
 * \param entry the id of the entry
 * \param pASprite the sprite to draw for this entry
 */

/*! \fn MenuView::~MenuView()
 */

#endif
