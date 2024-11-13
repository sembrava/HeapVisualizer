#include "settingsmodel.h"
#include "../../globals.h"

SettingsModel::SettingsModel(SettingsManager* settingsManager, QObject* parent)
    : m_settingsManager(settingsManager)
    , QObject(parent)
{}

SettingsModel::~SettingsModel()
{
    delete m_settingsManager;
}

void SettingsModel::setLanguage(const QString& language)
{
    g_qmlGlobals.setLanguage(language);

    m_settingsManager->update("language", language.toStdString());
}

void SettingsModel::setTheme(const QString& theme)
{
    g_qmlGlobals.setIsLightTheme(theme == "light");

    m_settingsManager->update("theme", theme.toStdString());
}
