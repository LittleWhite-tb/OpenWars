#ifndef __LINEPARSER_H__
#define __LINEPARSER_H__

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

#include <fstream>
#include <string>

#include "NEngine/Types/Vec2.h"
#include "NEngine/Types/Size2.h"

class LineParser
{
private:
    std::ifstream file;     /*!< The file to parse */
    std::string line;       /*!< The actual line to parse */
    unsigned int lineNumber;    /*!< Actual line number */

    bool isEmptyLine();

public:

    LineParser(const std::string& fileName);
    ~LineParser();

    bool readNextLine();

    const std::string& getLine()const { return line; }

    unsigned int getLineNumber()const { return lineNumber; }

    bool getBool(void)const;
    int getInt(void)const;
    float getFloat(void)const;
    IVec2 getIVec2(void)const;
    USize2 getUSize2(void)const;
};

/*! \class LineParser LineParser.h "Utils/LineParser.h"
 *  \brief Class for parsing file line by line
 *
 * With this class you can parse:
 *      - bool
 *      - int
 *      - float
 *      - IVec2
 */

/*! \fn bool LineParser::isEmptyLine()
 * Check if the actual line is empty
 * \return true if the line is empty
 */

/*! \fn LineParser::LineParser(const std::string& fileName)
 * \brief Basic constructor
 * Open the file and read the first line
 * \param fileName the name of the file to open
 */

/*! \fn LineParser::~LineParser()
 */

/*! \fn bool LineParser::readNextLine()
 * \brief Read the next line
 * \return false if we have reached the end of the line
 */

/*! \fn const std::string& LineParser::getLine()const
 * \brief Get the actual line
 * \return the actual line
 */

/*! \fn unsigned int LineParser::getLineNumber()const
 * \brief Get the actual line number
 * \return the actua line number
 */

/*! \fn bool LineParser::getBool(void)const
 * \brief Read a boolean on the line
 * \return the boolean on the line
 */

/*! \fn int LineParser::getInt(void)const
 * \brief Read a int on the line
 * \return the int on the line
 */

/*! \fn float LineParser::getFloat(void)const
 * \brief Read a float on the line
 * \return the float on the line
 */

/*! \fn IVec2 LineParser::getIVec2(void)const
 * \brief Read a IVec2 on the line
 * \return the IVec2 on the line
 */

/*! \fn USize2 LineParser::getUSize2(void)const
 * \brief Read a USize2 on the line
 * \return the USize2 on the line
 */

#endif
