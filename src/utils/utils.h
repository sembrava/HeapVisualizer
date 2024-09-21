#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>

namespace Utils
{
    std::vector<std::string> split(const std::string& string, char delimiter);

    [[nodiscard]] constexpr int getParent(const int child)
    {
        return (child - 1) / 2;
    }

    [[nodiscard]] constexpr int getLeftChild(const int parent)
    {
        return parent * 2 + 1;
    }

    [[nodiscard]] constexpr int getRightChild(const int parent)
    {
        return parent * 2 + 2;
    }

    void swap(int& first, int& second);
}

#endif // UTILS_H
