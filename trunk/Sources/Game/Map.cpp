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

#include "Map.h"

#include <string>

#include <string>
#include <sstream>
#include <fstream>

#include "Tile.h"

#include "../Engine/Window.h"
#include "../Engine/Renderer.h"
#include "../Engine/ResourcesManager/SpriteManager.h"
#include "../Engine/AnimatedSprite.h"

#include "../Types/Vec2.h"

#include "../Utils/Logger.h"

Map :: Map(SpriteManager& sm, const std::string& fileName)
	:width(0),height(0),map(NULL),valid(false)
{
	valid = this->parser(sm,fileName);

	LDebug << "Map '" << fileName.c_str() << "' created";
}

Map :: ~Map(void)
{
	for ( unsigned int y = 0 ; y < this->height ; y++ )
	{
		for ( unsigned int x = 0 ; x < this->width ; x++ )
			delete map[y][x];

		delete[] map[y];
	}

	delete[] map;

	LDebug << "Map deleted";
}

bool Map :: parser(SpriteManager& sm, const std::string& fileName)
{
	std::ifstream file;
	std::string line;
	std::string theme = "";
	unsigned int lineCounter = 0;
	unsigned int mapLineCounter = 0;
	bool error = false;

	LDebug << "Map :: parser '" << fileName.c_str() << "'";

	file.open(fileName.c_str(),std::ios::in);
    if ( file.is_open() == false )
    {
		LWarning << "Failed to open: '" << fileName.c_str() << "'";
		return false;
	}

	while ( !file.eof() && !error )
    {
        std::getline(file,line);
		if ( line[0] != '#' && line.size() != 0 ) // If the line is not empty, or is not a comment
        {
            std::stringstream ss(line);

			if ( lineCounter == 0 )
			{
				ss >> theme;

				LDebug << "Theme: " << theme.c_str();
			}
			else if ( lineCounter == 1 )
			{
				ss >> this->width >> this->height;

				if ( this->width != 0 || this->height != 0 )	// If it looks correct (we can add a maximum size... to be safer)
				{
					map = new Tile**[this->height];
					if ( map == NULL )
					{
						LError << "Error to allocate memory for the map! (at height)";
						error = true;
					}
					else
					{
						for ( unsigned int y = 0 ; y < this->height ; y++ )
						{
							map[y] = new Tile*[this->width];
							if ( map[y] == NULL )
							{
								LError << "Error to allocate memory for the map! (at width (" << y << "))";
								error = true;
							}
						}
					}
				}
				else
				{
					LError << "Size of the map not valid (" << this->width << ";" << this->height << ")";
					error = true;
				}
			}
			else if ( lineCounter >= 2 && lineCounter < 2+this->height ) // For all lines representating the map
			{
				mapLineCounter++;

				// We are reading one line, by one
				for ( unsigned int x = 0 ; x < this->width ; x++ )
				{
					int tileType = -1;
					ss >> tileType;
					if ( tileType != -1 )
					{
						if ( tileType < TT_END_LIST )
						{
							map[lineCounter-2][x] = TileFactory(sm,theme,static_cast<TileType>(tileType));
						}
						else
						{
							LWarning << "Data in the map invalid (" << tileType << ")";
							error = true;
						}	
					}
					else
					{
						LError << "Fail to read the tile type @ " << x << ";" << lineCounter-2;
						error = true;
					}
				}
			}
            
            lineCounter++;
        }
    }

	if ( mapLineCounter != this->height )
	{
		LError << "The number of line declared in the size of the map doesn't correspond to the number of lines in the map data (" << mapLineCounter << ")";
		error = true;
	}

	file.close();

	return !error;
}

bool Map :: draw(Window& win, Renderer& r, const unsigned int time)
{
	IVec2 tilePos(0,0);

	LDebug << "Map :: draw";

	for ( unsigned int y = 0 ; y < this->height ; y++ )
	{
		tilePos.x = 0;
		for ( unsigned int x = 0 ; x < this->width ; x++ )
		{
			r.drawTile(win,*(map[y][x]->pAnimation),tilePos,time);
			tilePos.x += map[y][x]->pAnimation->getWidth();
		}

		// To put 0 here, can be a bit dangerous
		tilePos.y += map[y][0]->pAnimation->getWidth();
	}

	return true;
}