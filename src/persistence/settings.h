#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>

class Settings
{
public:
    explicit Settings(const std::string& language, const std::string& theme) : m_language(language), m_theme(theme) {}

    [[nodiscard]] std::string getLanguage() const { return m_language; }

    [[nodiscard]] std::string getTheme() const { return m_theme; }

private:
    const std::string m_language;
    const std::string m_theme;
};

#endif // SETTINGS_H
