#ifndef __LINEPARSER_H__
#define __LINEPARSER_H__

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
/**
The idea of this class is coming from another open project called "Back to roots"
http://sourceforge.net/projects/backtoroots/
and is under GPL copyright: Copyright (C) 2010 BEYLER Jean Christophe 
*/

#include <fstream>
#include <string>

#include "../Types/Vec2.h"

class LineParser
{
private:
	std::ifstream file;		/*!< The file to parse */
	std::string line;		/*!< The actual line to parse */
	unsigned int lineNumber;	/*!< Actual line number */

	//! Check if the actual line is empty
	/*!
	  \return true if the line is empty
	*/
	bool isEmptyLine();

public:

	//! Basic constructor
	/*!
	  Open the file and read the first line
	  \param fileName the name of the file to open
	*/
	LineParser(std::string& fileName);

	//! Basic destructor
	/*!
	  close the file
	*/
	~LineParser();

	//! Read the next line
	/*!
	  \return false if we have reached the end of the line
	*/
	bool readNextLine();

	//! Get the actual line 
	/*!
	  \return the actual line
	*/
	const std::string& getLine()const { return line; }

	//! Get the actual line number
	/*!
	  \return the actua line number
	*/
	unsigned int getLineNumber()const { return lineNumber; }

	//! Read a boolean on the line
	/*!
	  \return the boolean on the line
	*/
	bool getBool(void)const;

	//! Read a int on the line
	/*!
	  \return the int on the line
	*/
	int getInt(void)const;

	//! Read a float on the line
	/*!
	  \return the float on the line
	*/
	float getFloat(void)const;

	//! Read a IVec2 on the line
	/*!
	  \return the IVec2 on the line
	*/
	IVec2 getIVec2(void)const;
};

/*! \class LineParser LineParser.h "Utils/LineParser.h"
 *  \brief Class for parsing file line by line
 *
 * With this class you can parse:
 *		- bool
 *		- int
 *		- float
 *		- IVec2
 */

#endif