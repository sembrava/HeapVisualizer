#ifndef HEAPSORTSNAPSHOT_H
#define HEAPSORTSNAPSHOT_H

#include <QList>

class HeapSortSnapshot
{
public:
    explicit HeapSortSnapshot(const QList<int>& tree, int greaterComparedNodeIndex, int smallerComparedNodeIndex, int sortedBoundIndex)
        : m_tree(tree)
        , m_greaterComparedNodeIndex(greaterComparedNodeIndex)
        , m_smallerComparedNodeIndex(smallerComparedNodeIndex)
        , m_sortedBoundIndex(sortedBoundIndex)
    {}

    [[nodiscard]] const QList<int>& getTree() const { return m_tree; }

    [[nodiscard]] int getGreaterComparedNodeIndex() const { return m_greaterComparedNodeIndex; }

    [[nodiscard]] int getSmallerComparedNodeIndex() const { return m_smallerComparedNodeIndex; }

    [[nodiscard]] int getSortedBoundIndex() const { return m_sortedBoundIndex; }

private:
    const QList<int> m_tree;
    const int m_greaterComparedNodeIndex;
    const int m_smallerComparedNodeIndex;
    const int m_sortedBoundIndex;
};

#endif // HEAPSORTSNAPSHOT_H
