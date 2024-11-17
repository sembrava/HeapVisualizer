#ifndef SETTINGSMODEL_H
#define SETTINGSMODEL_H

#include <QObject>

#include "../../persistence/settingsmanager.h"

class SettingsModel : public QObject
{
    Q_OBJECT
public:
    explicit SettingsModel(SettingsManager* settingsManager, QObject *parent = nullptr);

    Q_INVOKABLE void setLanguage(const QString& language);

    Q_INVOKABLE void setTheme(const QString& theme);

private:
    SettingsManager* m_settingsManager;
};

#endif // SETTINGSMODEL_H
