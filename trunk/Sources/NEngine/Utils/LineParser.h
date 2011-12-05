#ifndef OAW_LINEPARSER_H
#define OAW_LINEPARSER_H

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

/*! 
 *  \class      LineParser LineParser.h "Utils/LineParser.h"
 *  \brief      Class for parsing file line by line
 *  \details    With this class you can parse bool, int, float and IVec2
 *  \remark     Entity semantic (no copy constructor, no affectation opeator)
 *  \invariant  File is open and valid
 */
 
#include <fstream>
#include <string>
#include <NEngine/Types/Vec2.h>
#include <NEngine/Types/Size2.h>

class LineParser
{
public: // Constucteurs, copy and destructor

    /*!
     *  \fn     LineParser::LineParser(const std::string& fileName)
     *  \brief  Basic constructor
     *  \detail Open the file and read the first line
     *  \param  FileName the name of the file to open   
     *  \pre    Filename must exist
     */
	LineParser(const std::string& fileName);
	
	// destructor
	~LineParser();
	
private: // sémantique d'entité : http://cpp.developpez.com/faq/cpp/?page=classes#CLASS_entite
    LineParser(LineParser const&);
    LineParser operator= (LineParser const&);
	
public: // members functions

    /*! 
     *  \fn     bool LineParser::readNextLine()
     *  \brief  Read the next line
     *  \return false if we have reached the end of the line
     */
	bool readNextLine();

    /*! 
     *  \fn     const std::string& LineParser::getLine() const
     *  \brief  Get the actual line 
     *  \return The actual line
     */
	inline const std::string& getLine() const { return line; }

    /*! 
     *  \fn     unsigned int LineParser::getLineNumber() const
     *  \brief  Get the actual line number
     *  \return The actua line number
     */
	inline unsigned int getLineNumber() const { return lineNumber; }

    /*! 
     *  \fn bool LineParser::getBool(void) const
     *  \brief Read a boolean on the line
     *  \return the boolean on the line
     */
	bool getBool(void) const;
	
    /*! 
     *  \fn     int LineParser::getInt(void) const
     *  \brief  Read a int on the line
     *  \return The int on the line
     */
	int getInt(void) const;
	
    /*! 
     *  \fn     float LineParser::getFloat(void) const
     *  \brief  Read a float on the line
     *  \return The float on the line
     */
	float getFloat(void) const;
	
    /*! 
     *  \fn     IVec2 LineParser::getIVec2(void) const
     *  \brief  Read a IVec2 on the line
     *  \return The IVec2 on the line
     */
	IVec2 getIVec2(void) const;

    /*! 
     *  \fn     USize2 LineParser::getUSize2(void) const
     *  \brief  Read a USize2 on the line
     *  \return The USize2 on the line
     */
	USize2 getUSize2(void) const;
	
private:
	std::ifstream file;		    /*!< The file to parse */
	std::string line;		    /*!< The actual line to parse */
	unsigned int lineNumber;    /*!< Actual line number */

    // return true if the line is empty
	bool isEmptyLine();
};

#endif // OAW_LINEPARSER_H
