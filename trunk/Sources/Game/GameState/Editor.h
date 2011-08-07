#ifndef __EDITOR_H__
#define __EDITOR_H__

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

#include "Game/GameState.h"

#include "NEngine/InputManager.h"

#include "Game/GameState/GameObjects/Unit.h"

#include "UI/TileBar.h"

#include "Types/Size2.h"
#include "Types/Vec2.h"

namespace NE { class NEngine; }
namespace NE { class Renderer; }

class TileViewer;

class Map;
class Camera;
class EditingCursor;

class Editor : public GameState
{
private:
	
	Map* pMap;
	Camera* pCamera;
	EditingCursor* pEC;			/*!< The cursor */	

	TileBar<const Tile*>* pBuildingTB;			/*!< The tile bar for buildings */
	TileBar<const UnitTemplate*>* pUnitTB;		/*!< The tile bar for units*/
	TileViewer* pTileViewer;	/*!< The tile viewer */
	bool isUnitSelected;

public:
	Editor();
	~Editor();

	bool load(NE::NEngine* pNE);
	bool loadMap(const Library<Theme>* const pThemes, const std::string& mapName);
	bool loadMap(const Theme* const pTheme, const USize2& mapSize);

	bool draw(NE::Renderer* pRenderer, unsigned int time);
	bool update(NE::InputManager::ArrowsDirection direction, NE::InputManager::Buttons buttons, unsigned int time);

	void saveMap(const std::string& fileName);

	// bool setTile(const UVec2& position, const UnitType unitType);
};

/*! \class Editor Editor.h "Engine/GameState/Editor.h"
 *  \brief Editor state displaying an editor to create a map
 */

/*! \fn Editor::Editor()
 */

/*! \fn Editor::~Editor(void)
 */

/*! \fn bool Editor::loadMap(const Library<Theme>* const pThemes, const std::string& mapName)
 * \brief Load a map
 * \param pThemes a pointer to the library of themes available
 * \param mapName the name of the map to laod
 * \return true if all goes fine
 */

/*! \fn bool Editor::loadMap(const Theme* const pTheme, const UVec2& mapSize)
 * \brief Load an empty map
 * \param pTheme the theme to use for this new map
 * \param mapSize The size of the empty map
 * \return true if all goes fine
 */

/*! \fn void Editor::saveMap(const std::string& fileName)
 * \brief Save the map in a file
 * \param fileName the file where to save the map
 * \return true if all goes fine
 */

#endif
