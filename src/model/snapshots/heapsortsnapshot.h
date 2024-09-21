#ifndef HEAPSORTSNAPSHOT_H
#define HEAPSORTSNAPSHOT_H

#include <vector>
#include <optional>

class HeapSortSnapshot
{
public:
    explicit HeapSortSnapshot(
        const std::vector<int>& tree,
        int greaterComparedNodeIndex,
        int smallerComparedNodeIndex,
        std::optional<int> sortedBoundIndex
    )
        : m_tree(tree)
        , m_greaterComparedNodeIndex(greaterComparedNodeIndex)
        , m_smallerComparedNodeIndex(smallerComparedNodeIndex)
        , m_sortedBoundIndex(sortedBoundIndex)
    {}

    [[nodiscard]] const std::vector<int>& getTree() const { return m_tree; }

    [[nodiscard]] int getGreaterComparedNodeIndex() const { return m_greaterComparedNodeIndex; }

    [[nodiscard]] int getSmallerComparedNodeIndex() const { return m_smallerComparedNodeIndex; }

    [[nodiscard]] std::optional<int> getSortedBoundIndex() const { return m_sortedBoundIndex; }

private:
    const std::vector<int> m_tree;
    const int m_greaterComparedNodeIndex;
    const int m_smallerComparedNodeIndex;
    const std::optional<int> m_sortedBoundIndex;
};

#endif // HEAPSORTSNAPSHOT_H
