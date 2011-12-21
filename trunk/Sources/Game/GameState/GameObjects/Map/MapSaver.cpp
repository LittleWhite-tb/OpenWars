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

#include <fstream>

#include "NEngine/NEngine.h"

#include "MapSaver.h"

#include "Map.h"

bool MapSaver :: saveMapToFile(const std::string& fileName, const Map& map)
{
	std::ofstream file;
	const std::vector < std::vector < const Tile* > >& tilesMap = map.constTilesMap();
	const std::vector < std::vector < Unit > >& unitsMap = map.constUnitsMap();

    NE::NEngine::logger()->log(NE::LL_Debug,"Map :: save -> '%s'",fileName.c_str());

	file.open(fileName.c_str(),std::ios::out);
    if ( file.is_open() == false )
    {
        NE::NEngine::logger()->log(NE::LL_Warning,"Failed to open: '%s'",fileName.c_str());
		return false;
	}

	// Adding some comments for all curious opening the map with text editor
	file << "# Map created with the OpenAWars Editor" << std::endl;
	file << "# DO NOT EDIT !!!" << std::endl;

	// Now we can start to save the data

	// Name of the theme
	file << map.getTheme()->getName() << std::endl;

	// The size 'width height'
	file << map.getWidth() << " " << map.getHeight() << std::endl;

	// The tiles data
	file << "# Tiles" << std::endl;
	// For each lines
	for ( unsigned int y = 0 ; y < map.getHeight() ; y++ )
	{
		// For each columns
		for ( unsigned int x = 0 ; x < map.getWidth() ; x++ )
		{
			if ( x!=0 )
			{
				file << " ";
			}
			file << tilesMap[y][x]->getID();
		}

		file << std::endl;
	}

	// The units data
	file << "# Units" << std::endl;
	// For each lines
	for ( unsigned int y = 0 ; y < map.getHeight() ; y++ )
	{
		// For each columns
		for ( unsigned int x = 0 ; x < map.getWidth() ; x++ )
		{
			if ( x!=0 )
			{
				file << " ";
			}
			if ( unitsMap[y][x].state != US_NO_UNIT )
			{
				file << unitsMap[y][x].getID();
			}
			else
			{
				file << -1;
			}
		}

		file << std::endl;
	}

	file.close();

	return true;
}