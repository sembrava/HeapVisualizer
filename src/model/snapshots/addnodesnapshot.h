#ifndef ADDNODESNAPSHOT_H
#define ADDNODESNAPSHOT_H

#include <vector>
#include <optional>

class AddNodeSnapshot
{
public:
    explicit AddNodeSnapshot(const std::vector<int>& tree, std::optional<int> greaterComparedNodeIndex, std::optional<int> smallerComparedNodeIndex)
        : m_tree(tree)
        , m_greaterComparedNodeIndex(greaterComparedNodeIndex)
        , m_smallerComparedNodeIndex(smallerComparedNodeIndex)
    {}

    [[nodiscard]] const std::vector<int>& getTree() const { return m_tree; }

    [[nodiscard]] std::optional<int> getGreaterComparedNodeIndex() const { return m_greaterComparedNodeIndex; }

    [[nodiscard]] std::optional<int> getSmallerComparedNodeIndex() const { return m_smallerComparedNodeIndex; }

private:
    const std::vector<int> m_tree;
    const std::optional<int> m_greaterComparedNodeIndex;
    const std::optional<int> m_smallerComparedNodeIndex;
};

#endif // ADDNODESNAPSHOT_H
