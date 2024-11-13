#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <string>

#include "settings.h"

class SettingsManager
{
public:
    virtual ~SettingsManager() = default;

    virtual Settings getSettings() = 0;

    virtual void update(const std::string& key, const std::string& value) = 0;
};

#endif // SETTINGSMANAGER_H
