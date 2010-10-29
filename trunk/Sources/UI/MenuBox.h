#ifndef __MENUBOX_H__
#define __MENUBOX_H__

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

#include <string>
#include <vector>

#include "../Engine/AnimatedSprite.h"
#include "../Engine/Controls/Keyboard.h"

#include "../Types/Vec2.h"

class SpriteManager;
class FontManager;
class Renderer;
class Window;
class Sprite;
class Font;

enum MenuEntry
{
	ME_EndTurn,
	ME_Quit,
};

struct MenuView
{
	std::string name;			/*!< name to display */
	MenuEntry entry;			/*!< id of the entry */
	AnimatedSprite* pASprite;	/*!< sprite to display */

	//! Basic construct
	/*!
		Note: The AnimatedSprite will be deleted by the parent UI
	  \param name the name to display for this entry
	  \param entry the id of the entry
	  \param pASprite the sprite to draw for this entry
	*/
	MenuView(const std::string& name, const MenuEntry entry, AnimatedSprite* const pASprite):name(name),entry(entry),pASprite(pASprite) {}
};

class MenuBox
{
private:
	Sprite* pBackground;				/*!< background for the UI (generated on the fly by the constructor) */
	AnimatedSprite* pCursor;			/*!< cursor */
	Font* pFont;						/*!< font for the texts */

	unsigned int windowXPosition;		/*!< Window width */
	unsigned int actualPosition;		/*!< actual position of the cursor */

	std::vector<MenuView> entries;		/*!< entries in the UI */

	bool valid;							/*!< flag to know if the initialisation goes right */

public:
	//! Basic construct
	/*!
	  \param sm The sprite manager to load the sprites
	  \param fm The font manager to load the fonts
	  \param win the window where to draw the UI
	  \param cursorFileName the file to load for the cursor
	  \param fontFileName the font to load for the texts
	  \param entries the entries to display in the UI
	*/
	MenuBox(SpriteManager& sm, FontManager& fm, const Window& win, const std::string& cursorFileName, const std::string& fontFileName, const std::vector<MenuView>& entries);

	//! Basic destructor
	/*!
	*/
	~MenuBox(void);

	//! Draw the construct box
	/*!
	  \param r the renderer to use to draw the UI
	  \param cursorPosition the position of the cursor (to place the UI)
	  \param time the actual time
	  \return true if all goes right
	*/
	bool draw(const Renderer& r, const UVec2& cursorPosition, const unsigned int time);

	//! Update the construct box
	/*!
	  Move the cursor following the keys pressed
	  \param kd the key direction pressed
	*/
	void update(const ArrowsDirection kd);

	//! Get the actual element selected
	/*!
	  \return The MenuEntry of the element currently selected
	*/
	MenuEntry getActualEntry(void) { return entries[actualPosition].entry; }

	//! Get if the constructor goes right
	/*!
	  \return true if the initialisation goes right
	*/
	bool getValid()const { return valid; }
};

/*! \class MenuBox MenuBox.h "UI/MenuBox.h"
 *  \brief User interface to display menus
 *
 * The MenuBox show a little box with multiple entries to let the user select actions
 * The background is constructed on the fly, so it needs special precaution.
 */

/*! \struct MenuView MenuBox.h "UI/MenuBox.h"
 *  \brief MenuView struct
 *
 * Used to give a structure usable in the MenuBox to contain an entry
 */

#endif