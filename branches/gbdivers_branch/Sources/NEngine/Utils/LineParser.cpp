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

/**
The idea of this class is coming from another open project called "Back to roots"
http://sourceforge.net/projects/backtoroots/
and is under GPL copyright: Copyright (C) 2010 BEYLER Jean Christophe 
*/

#include "LineParser.h"
#include <fstream>
#include <string>
#include <sstream>
#include <cassert>
#include "Exceptions/FileNotOpenedException.h"
#include "Logger.h"

LineParser :: LineParser(const std::string& fileName)
:file(fileName.c_str(), std::ios::in), line(), lineNumber(0) // aie... si une exception est lancée ? pas catché ?
{
	if (!file)
	{
		LDebug << "LineParser fail to open: " << fileName.c_str();
		throw FileNotOpenedException(fileName);
	}

	readNextLine();

    #ifdef VERBOSE
	LDebug << "LineParser constructed: " << fileName.c_str();
	#endif
}

LineParser :: ~LineParser()
{
	file.close();

    #ifdef VERBOSE
	LDebug << "LineParser deleted";
	#endif
}

bool LineParser :: isEmptyLine()
{
	for(std::string::const_iterator itChar = line.begin() ; itChar != line.end() ; ++itChar )
	{
		if ( *itChar != ' ' && *itChar != '\r' )
			return false;
	}

	return true;
}

bool LineParser :: readNextLine()
{
    #ifdef VERBOSE
	LDebug << "LineParser readNextLine";
    #endif

	do
	{
		if ( file.eof() )
		{
			return false;
		}
		std::getline(file,line);
	// Test to avoid the empty lines and comments
	} while ((line.size() == 0 || line[0] == '#' || isEmptyLine()));

	// We read only one correct file
	lineNumber++;
	return true;
}

IVec2 LineParser :: getIVec2(void) const
{
	std::stringstream ss(line);
	IVec2 v;
	ss >> v.x >> v.y;
	return v;
}

USize2 LineParser :: getUSize2(void) const
{
	std::stringstream ss(line);
	USize2 s;
	ss >> s.width >> s.height;
	return s;
}

int LineParser :: getInt(void) const
{
	std::stringstream ss(line);
	int i;
	ss >> i;
	return i;
}

float LineParser :: getFloat(void) const
{
	std::stringstream ss(line);
	float f;
	ss >> f;
	return f;
}

bool LineParser :: getBool(void) const
{
	std::stringstream ss(line);
	int i;
	ss >> i;
	return (i!=0);
}
