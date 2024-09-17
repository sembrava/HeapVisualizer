#ifndef ADDNODESNAPSHOT_H
#define ADDNODESNAPSHOT_H

#include <vector>

class AddNodeSnapshot
{
public:
    explicit AddNodeSnapshot(const std::vector<int>& tree, int greaterComparedNodeIndex, int smallerComparedNodeIndex)
        : m_tree(tree)
        , m_greaterComparedNodeIndex(greaterComparedNodeIndex)
        , m_smallerComparedNodeIndex(smallerComparedNodeIndex)
    {}

    [[nodiscard]] const std::vector<int>& getTree() const { return m_tree; }

    [[nodiscard]] int getGreaterComparedNodeIndex() const { return m_greaterComparedNodeIndex; }

    [[nodiscard]] int getSmallerComparedNodeIndex() const { return m_smallerComparedNodeIndex; }

private:
    const std::vector<int> m_tree;
    const int m_greaterComparedNodeIndex;
    const int m_smallerComparedNodeIndex;
};

#endif // ADDNODESNAPSHOT_H
