#include <sstream>

#include "utils.h"

std::vector<std::string> Utils::split(const std::string& string, char delimiter)
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

constexpr int Utils::getParent(const int child) noexcept
{
    return (child - 1) / 2;
}


constexpr int Utils::getLeftChild(const int parent) noexcept
{
    return parent * 2 + 1;
}

constexpr int Utils::getRightChild(const int parent) noexcept
{
    return parent * 2 + 2;
}

void Utils::swap(int &x, int &y) noexcept
{
    const int temp = x;
    x = y;
    y = temp;
}
