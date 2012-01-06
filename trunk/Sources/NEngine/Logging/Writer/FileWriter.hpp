#ifndef FILEWRITER_HPP
#define FILEWRITER_HPP

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
