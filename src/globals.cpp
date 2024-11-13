#include "globals.h"
#include "utils/utils.h"
#include "persistence/csvfilemanager.h"
#include "persistence/inisettingsmanager.h"

FileManager* g_fileManager = new CsvFileManager(Utils::getSaveDirectoryPath());

SettingsManager* g_settingsManager = new IniSettingsManager(Utils::getSettingsPath());

QmlGlobals g_qmlGlobals;
