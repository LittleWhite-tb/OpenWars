#include "FileWriter.hpp"

#include <iostream>

std::string NE::FileWriter::logFileName = "log.txt";

NE::FileWriter::FileWriter()
    :logFile(logFileName.c_str())
{
    if ( !logFile.is_open() )
    {
        throw std::exception();
    }
}

NE::FileWriter::~FileWriter()
{
    logFile.close();
}

void NE::FileWriter::write(const NE::LoggerMessage& message)
{
    logFile << message.formatedMessage << std::endl;
}
