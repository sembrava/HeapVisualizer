#include <QLocale>
#include <QSettings>

#include "inisettingsmanager.h"
#include "settings.h"

IniSettingsManager::IniSettingsManager(const std::string& path)
    : m_path(path)
{}

Settings IniSettingsManager::getSettings()
{
    QSettings settings(QString::fromStdString(m_path + "/config.ini"), QSettings::IniFormat);

    if (!settings.contains("language"))
        settings.setValue("language", QLocale::system().name() == "hu_HU" ? "hu" : "en");

    if (!settings.contains("theme"))
        settings.setValue("theme", QSettings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", QSettings::NativeFormat).value("AppsUseLightTheme", 1).toInt() == 1 ? "light" : "dark");

    return Settings(settings.value("language", "en").toString().toStdString(), settings.value("theme", "light").toString().toStdString());
}

void IniSettingsManager::update(const std::string& key, const std::string& value)
{
    if (key != "language" && key != "theme")
        return;

    if (key == "language" && (value != "en" && value != "hu"))
        return;

    if (key == "theme" && (value != "light" && value != "dark"))
        return;

    QSettings settings(QString::fromStdString(m_path + "/config.ini"), QSettings::IniFormat);

    settings.setValue(QString::fromStdString(key), QString::fromStdString(value));

    settings.sync();
}
