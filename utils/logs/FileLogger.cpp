#include "FileLogger.h"

FileLogger::FileLogger(const std::string &filename) 
{
    file.open(filename);
}

std::ostream &FileLogger::stream()
{
    return file;
}

FileLogger::~FileLogger() {
    file.close();
}