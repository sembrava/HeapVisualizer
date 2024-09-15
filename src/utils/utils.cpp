#include <sstream>

#include "utils.h"

std::vector<std::string> Utils::split(const std::string &string, char delimiter)
{
    std::vector<std::string> tokens;
    std::istringstream tokenStream(string);
    std::string token;

    while (std::getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }

    return tokens;
}
