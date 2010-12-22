#ifdef EDITOR
#ifndef __EDITINGCURSOR_H__
#define __EDITINGCURSOR_H__

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

#include "Cursor.h"

#include <string>

#include "../NEngine/NETypes.h"
#include "../Types/Vec2.h"

class SpriteManager;
class Renderer;
class AnimatedSprite;
class Map;
class Camera;

class EditingCursor : public Cursor
{
private:

	AnimatedSprite* pWrongCursorSprite;			/*!< The sprites for the wrong state */

	bool isWrong;								/*!< The state of the cursor */

public:
	EditingCursor(SpriteManager& sm, const std::string& fileNameCursor, const std::string& fileNameWrongCursor, const Map* const pMap, const UVec2& initialPosition);
	~EditingCursor(void);

	bool getIsWrong(void)const { return isWrong; }
	void setIsWrong(const bool isWrong) { this->isWrong = isWrong; }

	virtual bool draw(const Camera& c, const unsigned int time)const;
};

/*! \class EditingCursor EditingCursor.h "Game/EditingCursor.h"
 *  \brief Manage the EditingCursor on the Map
 *
 * The EditingCursor implements the feature to change the sprite to draw when isWrong is true
 * In this state the user will know that he can't put the tile on the map
 */

/*! \fn EditingCursor::EditingCursor(SpriteManager& sm, const std::string& fileNameCursor, const std::string& fileNameWrongCursor, const Map* const pMap, const UVec2& initialPosition)
 * \param sm The SpriteManager to use to load the sprites
 * \param fileNameCursor the name of the file to load for the cursor sprite (normal mode)
 * \param fileNameWrongCursor the name of the file to load for the wrong cursor sprite
 * \param pMap A pointer on the Map to use
 * \param initialPosition The initial position of the cursor
 */

/*! \fn EditingCursor::~EditingCursor(void)
 */

/*! \fn bool EditingCursor::getIsWrong(void)const
 * \brief Get if the cursor is in the wrong state
 * \return the true if the cursor is set as wrong
 */

/*! \fn void EditingCursor::setIsWrong(const bool isWrong)
 * \brief Set the cursor state
 * \param isWrong true if the cursor has to be wrong
 */

#endif
#endif