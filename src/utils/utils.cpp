#include <sstream>
#include <QStandardPaths>
#include <QDir>

#include "utils.h"

std::vector<std::string> Utils::split(const std::string& string, char delimiter)
{
    std::vector<std::string> tokens;
    std::istringstream tokenStream(string);
    std::string token;

    while (std::getline(tokenStream, token, delimiter))
        tokens.push_back(token);

    return tokens;
}

void Utils::swap(int& first, int& second)
{
    const int temp = first;
    first = second;
    second = temp;
}

QVariantList Utils::toQVariantList(const std::vector<int>& array)
{
    QVariantList result;

    for (const int element : array)
        result.push_back(QVariant::fromValue(element));

    return result;
}

QString Utils::getAppDataPath()
{
    return QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/HeapVisualizer";
}

std::string Utils::getSaveDirectoryPath()
{
    const QString path = Utils::getAppDataPath() + "/saves";

    QDir().mkpath(path);

    return path.toStdString();
}

std::string Utils::getSettingsPath()
{
    const QString path = Utils::getAppDataPath();

    QDir().mkpath(path);

    return path.toStdString();
}
