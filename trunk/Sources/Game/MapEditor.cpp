#ifdef EDITOR

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

#include "MapEditor.h"

#include <fstream>

#include <cassert>

#include "../Engine/Sprite.h"
#include "Tile.h"

#include "../Utils/Logger.h"

#include "../globals.h"

MapEditor :: MapEditor(SpriteManager& sm, const UVec2& size)
	:Map()
{
	width = size.x;
	height = size.y;
	valid = true;	// By default the map is valid, but maybe just after, we will fail, so invalidate it
	m_theme = "classic"; // By default the theme is the classical one

	map = new Tile**[this->height];
	if ( map == NULL )
	{
		LError << "Error to allocate memory for the map! (at height)";
		valid = false;
	}
	else
	{
		for ( unsigned int y = 0 ; y < this->height ; y++ )
		{
			map[y] = new Tile*[this->width];
			if ( map[y] == NULL )
			{
				LError << "Error to allocate memory for the map! (at width (" << y << "))";
				valid = false;
			}
		}
	}

	for ( unsigned int y = 0 ; y < this->height ; y++ )
	{
		for ( unsigned int x = 0 ; x < this->width ; x++ )
		{
			Tile* pTile = NULL;

			pTile = TileFactory(sm,m_theme,TT_Plain);
			if ( pTile != NULL )
			{
				map[y][x] = pTile;
			}
			else
			{
				this->valid = false;
			}
		}
	}

	// Load the background tile
	backgroundTile = new Sprite(sm,GFX_TILES_PATH+m_theme+std::string("/plain.png"),true);

	LDebug << "MapEditor created " << size;
}

bool MapEditor :: setTile(SpriteManager& sm, const UVec2& position, const TileType tileType)
{
	Tile* pTile = NULL;

	// Extra protections
	assert(position.x < this->width);
	assert(position.y < this->height);

	LDebug << "Map :: setTile " << position << " Tile: " << tileType;

	// Deletion of the old Tile
	delete map[position.y][position.x];

	// Creation ( and replacement ) with the new Tile
	pTile = TileFactory(sm,m_theme,tileType);
	if ( pTile != NULL )
	{
		map[position.y][position.x] = pTile;
	}
	else
	{
		this->valid = false;
		return false;
	}

	return true;
}

bool MapEditor :: save(const std::string& fileName)
{
	std::ofstream file;

	LDebug << "Map :: save -> '" << fileName.c_str() << "'";

	file.open(fileName.c_str(),std::ios::out);
    if ( file.is_open() == false )
    {
		LWarning << "Failed to open: '" << fileName.c_str() << "'";
		return false;
	}

	// Adding some comments for all curious opening the map with text editor
	file << "# Map created with the OpenAWars Editor" << std::endl;
	file << "# DO NOT EDIT !!!" << std::endl;

	// Now we can start to save the data

	// Name of the theme
	file << m_theme << std::endl;

	// The size 'width height'
	file << this->width << " " << this->height << std::endl;

	// The tiles data

	// For each lines
	for ( unsigned int y = 0 ; y < this->height ; y++ )
	{
		// For each columns
		for ( unsigned int x = 0 ; x < this->width ; x++ )
		{
			if ( x!=0 )
			{
				file << " ";
			}
			file << map[y][x]->tileType;
		}

		file << std::endl;
	}

	file.close();

	return true;
}

#endif