#ifndef GLOBALS_H
#define GLOBALS_H

#include <src/persistence/csvfilemanager.h>

FileManager* g_fileManager = new CsvFileManager("../../saves");

#endif // GLOBALS_H
