#ifndef TREEFILEINFO_H
#define TREEFILEINFO_H

#include <vector>
#include <string>


class TreeFileInfo
{
public:
    explicit TreeFileInfo(const std::string& name, const std::vector<int>& tree)
        : m_name(name)
        , m_tree(tree)
    {}

    [[nodiscard]] const std::string& getName() const { return m_name; }

    [[nodiscard]] const std::vector<int>& getTree() const { return m_tree; }

private:
    const std::string m_name;
    const std::vector<int> m_tree;
};

#endif // TREEFILEINFO_H
