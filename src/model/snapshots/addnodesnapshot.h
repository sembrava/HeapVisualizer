#ifndef ADDNODESNAPSHOT_H
#define ADDNODESNAPSHOT_H

#include <QList>

class HeapSortSnapshot
{
public:
    explicit HeapSortSnapshot(const QList<int>& tree, int greaterComparedNodeIndex, int smallerComparedNodeIndex)
        : m_tree(tree)
        , m_greaterComparedNodeIndex(greaterComparedNodeIndex)
        , m_smallerComparedNodeIndex(smallerComparedNodeIndex)
    {}

    [[nodiscard]] const QList<int>& getTree() const { return m_tree; }

    [[nodiscard]] int getGreaterComparedNodeIndex() const { return m_greaterComparedNodeIndex; }

    [[nodiscard]] int getSmallerComparedNodeIndex() const { return m_smallerComparedNodeIndex; }

private:
    const QList<int> m_tree;
    const int m_greaterComparedNodeIndex;
    const int m_smallerComparedNodeIndex;
};

#endif // ADDNODESNAPSHOT_H
