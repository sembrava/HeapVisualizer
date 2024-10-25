#include <sstream>

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
