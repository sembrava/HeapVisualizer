#ifndef REMOVEMAXSNAPSHOT_H
#define REMOVEMAXSNAPSHOT_H

#include <vector>

class RemoveMaxSnapshot
{
    explicit RemoveMaxSnapshot(const std::vector<int>& tree, int greaterComparedNodeIndex, int smallerComparedNodeIndex, int extractedNodeKey)
        : m_tree(tree)
        , m_greaterComparedNodeIndex(greaterComparedNodeIndex)
        , m_smallerComparedNodeIndex(smallerComparedNodeIndex)
        , m_extractedNodeKey(extractedNodeKey)
    {}

    [[nodiscard]] const std::vector<int>& getTree() const { return m_tree; }

    [[nodiscard]] int getGreaterComparedNodeIndex() const { return m_greaterComparedNodeIndex; }

    [[nodiscard]] int getSmallerComparedNodeIndex() const { return m_smallerComparedNodeIndex; }

    [[nodiscard]] int getExtractedNodeKey() const { return m_extractedNodeKey; }

private:
    const std::vector<int> m_tree;
    const int m_greaterComparedNodeIndex;
    const int m_smallerComparedNodeIndex;
    const int m_extractedNodeKey;
};

#endif // REMOVEMAXSNAPSHOT_H
