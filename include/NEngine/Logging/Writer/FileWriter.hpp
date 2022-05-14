#ifndef FILEWRITER_HPP
#define FILEWRITER_HPP

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

#include "LoggerWriter.hpp"

#include <fstream>

namespace NE
{
    class FileWriter : public NE::LoggerWriter
    {
        private:

            static std::string logFileName;
            std::ofstream logFile;

        protected:

            /*! \brief Output the <i>message</i> to the file
             *  \param level priority level (unused here)
             *  \param message
             */
            void write(int level, const std::string& message)
            {
                logFile << message;
            }

        public:
            /*! */
            FileWriter();

            /*! */
            virtual ~FileWriter();

            /*! \brief Change the default file name
             *  Defining a new file name will not afftect the currently working loggers.<br>
             *  The change will be visible for the next created Logger using FileWriter.
             *  \param fileName the new name for the log file
             */
            static void setLogFile(const std::string& fileName) { FileWriter::logFileName = fileName; }
    };
}

/*! \class NE::FileWriter FileWriter.hpp Logging/Writer/FileWriter.hpp
 *  \brief Writer implementation outputting information on a file
 *
 *  The file can be set by the static function <a>setLogFile()</a>. Opening and closing of the file is done at the same time that the Logger construction and destruction.
 *  \sa Logger
 */

#endif
