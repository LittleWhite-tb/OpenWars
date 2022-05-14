#ifndef __FILENOTFOUNDEXCEPTION_H__
#define __FILENOTFOUNDEXCEPTION_H__

#ifndef DOXYGEN_IGNORE_TAG
/**
NEngine: Native Engine abstracts multimedia libraries such as SDL, SFML, Allegro
Copyright (C) 2010-2015  Alexandre LAURENT

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

website: https://github.com/LittleWhite-tb/NEngine
e-mail: lw.demoscene@gmail.com
**/
#endif

#include "NEngine/Exception.h"

class FileNotFoundException : public Exception
{

public:
	FileNotFoundException(const std::string& fileName):Exception(std::string("File not found: '") + fileName + std::string("'")) {}
    virtual ~FileNotFoundException(void)throw() {}
};

/*! \class FileNotFoundException FileNotFoundException.h "Utils/Exceptions/FileNotFoundException.h"
 *  \brief Exception to throw when file is not found
 */

/*! \fn FileNotFoundException::FileNotFoundException(const std::string& fileName)
 * Create a message of the format: "Failed to open 'USER_MESSAGE'"
 * \param fileName name of the file not found
 */

/*! \fn virtual const char* FileNotFoundException::what()const throw()
 * \return the error message
 */

#endif
