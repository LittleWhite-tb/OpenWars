#ifdef EDITOR
#ifndef __EDITORENGINE_H__
#define __EDITORENGINE_H__

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

#include "Engine.h"

#include "Unit.h"

#include "../Types/Vec2.h"

class FontManager;

class TileBarTiles;
class TileBarUnits;
class TileViewer;

class Camera;
class EditingCursor;
class MapEditor;

class VTime;

class EditorEngine : public Engine
{
private:
	TileBarTiles* pBuildingTB;	/*!< The tile bar for buildings */
	TileBarUnits* pUnitTB;		/*!< The tile bar for units*/
	TileViewer* pTileViewer;	/*!< The tile viewer */

	MapEditor* pMap;			/*!< The map to use */
	EditingCursor* pEC;			/*!< The cursor */	
	Camera* pCam;				/*!< The camera */

	bool load(void);

public:
	EditorEngine(NE::NEngine* const pNE);
	~EditorEngine();

	bool load(const UVec2& mapSize);
	bool load(const std::string& mapName);

	bool run(void);

	void saveMap(const std::string& fileName);

	// bool setTile(const UVec2& position, const UnitType unitType);
};

/*! \class EditorEngine EditorEngine.h "Engine/EditorEngine.h"
 *  \brief Engine of the whole editor
 *
 * Will be inited ; loaded ; and then run following the predefined game loop:
 *		- draw
 *		- if it has to be updated (see VTime class documentation)
 *		- update
 *		- wait for next frame (see VTime class documentation)
 */

/*! \fn bool EditorEngine::load(void)
 * \brief Load the map, cursor, camera with the associated sprites
 * Will load all needed to set the engine. After you can run the engine.
 * The engine has to be inited.
 * \return true if all goes fine
 */

/*! \fn EditorEngine::EditorEngine(NE::NEngine* const pNE)
 * \param pNE pointer of the Native Engine to user
 */

/*! \fn EditorEngine::~EditorEngine(void)
 */

/*! \fn bool EditorEngine::init()
 * \brief Init the engine by constructing all elements (Renderer, SpriteManager, FontManager,...)
 * \return true if all goes fine
 */

/*! \fn bool EditorEngine::load(const std::string& themeName, const UVec2& mapSize)
 * \brief Load an empty map
 * \param themeName the name of the theme to load
 * \param mapSize The size of the empty map
 * \return true if all goes fine
 */

/*! \fn bool EditorEngine::load(const std::string& mapName);
 * \brief Load the map from a file
 * \param mapName the name of the file to load
 * \return true if all goes fine
 */

/*! \fn bool EditorEngine::run(void)
 * \brief Start the editor main loop
 * \return true if all goes fine
 */

/*! \fn void EditorEngine::saveMap(const std::string& fileName)
 * \brief Save the map in a file
 * \param fileName the file where to save the map
 * \return true if all goes fine
 */

/*! \fn bool EditorEngine::setTile(const UVec2& position, const UnitType unitType);
 * \brief Set the Unit at the position
 * Will overwrite the Unit previously contained on the map by the new one.
 * The new Unit is selected following the internal logic of the editor.
 * The unit is automatically enabled in the editor
 * \param position the position where to change the tile
 * \param unitType the type of the new unit
 * \return true if all goes right
 */

#endif
#endif
