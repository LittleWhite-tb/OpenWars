#ifndef FILEWRITER_HPP
#define FILEWRITER_HPP

#include "LoggerWriter.hpp"

#include <fstream>

namespace NE
{
    class FileWriter : public LoggerWriter
    {
        private:

            static std::string logFileName;
            std::ofstream logFile;

        protected:

            void write(const NE::LoggerMessage& message);

        public:
            FileWriter();
            ~FileWriter();

            static void setLogFile(const std::string& fileName) { FileWriter::logFileName = fileName; }
    };
}

#endif
