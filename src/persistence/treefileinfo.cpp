#include "treefileinfo.h"

TreeFileInfo::TreeFileInfo(const std::string& name, const std::vector<int>& tree)
    : m_name(name)
    , m_tree(tree)
{}

const std::string& TreeFileInfo::getName() const
{
    return m_name;
}

const std::vector<int>& TreeFileInfo::getTree() const
{
    return m_tree;
}
