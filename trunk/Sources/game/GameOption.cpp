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

#include "GameOption.h"

#include "ArgumentParser.h"

#include <NEngine/Types/Size2.h>

#include <NEngine/Utils/Logger.h>

#include "globals.h"

GameOption :: GameOption(int argc, char** argv)
	:winSize(480,320),needFullscreen(false),
	 loadMapName(MAP_PATH + "maw.map"),
	 editorMode(false),
	 saveMapName("save.map"),mapSize(15,15),themeName("classic")
{
	ArgumentParser argParser(argc,argv);

	try
	{
		if ( argParser.isPresent("","--width") )
		{	
			winSize.width = argParser.getAs<unsigned int>("","--width");
		}
		if ( argParser.isPresent("","--height") )
		{	
			winSize.height = argParser.getAs<unsigned int>("","--height");
		}
		if ( argParser.isPresent("","--fullscreen") )
		{	
			needFullscreen = true;
		}
		if ( argParser.isPresent("","--load") )
		{	
			loadMapName = argParser.getArgument("","--load");
		}
		if ( argParser.isPresent("","--editor") )
		{	
			editorMode = true;
		}
		if ( argParser.isPresent("","--save") )
		{	
			saveMapName = argParser.getArgument("","--save");
		}
		if ( argParser.isPresent("","--mapWidth") )
		{	
			mapSize.width = argParser.getAs<unsigned int>("","--mapWidth");
		}
		if ( argParser.isPresent("","--mapHeight") )
		{	
			mapSize.height = argParser.getAs<unsigned int>("","--mapHeight");
		}
		if ( argParser.isPresent("","--theme") )
		{	
			themeName = argParser.getArgument("","--theme");
		}
	}
	catch (MissingOptionException& moe)
	{
		LWarning << moe.what();
	}
}
