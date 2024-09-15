#ifndef TREEFILEINFO_H
#define TREEFILEINFO_H

#include <vector>
#include <string>


class TreeFileInfo
{
public:
    TreeFileInfo(const std::string& name, const std::vector<int>& tree);

    const std::string& getName() const;

    const std::vector<int>& getTree() const;

private:
    const std::string m_name;
    const std::vector<int> m_tree;
};

#endif // TREEFILEINFO_H
