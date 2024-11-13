#ifndef GLOBALS_H
#define GLOBALS_H

#include "persistence/filemanager.h"
#include "persistence/settingsmanager.h"
#include "view/ui/qmlglobals.h"

extern FileManager* g_fileManager;

extern SettingsManager* g_settingsManager;

extern QmlGlobals g_qmlGlobals;

#endif // GLOBALS_H
