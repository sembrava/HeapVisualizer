#ifndef INISETTINGSMANAGER_H
#define INISETTINGSMANAGER_H

#include "settingsmanager.h"

class IniSettingsManager : public SettingsManager
{
public:
    explicit IniSettingsManager(const std::string& path);

    Settings getSettings() override;

    void update(const std::string& key, const std::string& value) override;

private:
    const std::string m_path;
};

#endif // INISETTINGSMANAGER_H
