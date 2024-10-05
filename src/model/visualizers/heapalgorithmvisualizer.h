#ifndef HEAPALGORITHMVISUALIZER_H
#define HEAPALGORITHMVISUALIZER_H

#include <QObject>

#define COMPARED_NODE_INDEXES_CHANGED_EXPLANATION(greater, smaller) \
    tr("The current node (%1) is compared with its greatest child (%2").arg(smaller).arg(greater)

#define COMPARED_NODES_SWAPPED_EXPLANATION(greater, smaller) \
    tr("Since %1 is greater than %2, they are swapped").arg(greater).arg(smaller)

#define COMPARED_NODES_NOT_SWAPPED_EXPLANATION(greater, smaller) \
    tr("Since %1 is not greater than %2, they are not swapped").arg(greater).arg(smaller)

#define SORTED_BOUND_INDEX_CHANGED_EXPLANATION(key) \
    tr("%1 is in its correct position, so it can be marked as sorted").arg(key)

#define NODE_EXTRACTED_EXPLANATION(key) \
    tr("The largest value (%1) is extracted").arg(key)

#define NODE_REMOVED_EXPLANATION(key) \
    tr("The last node (%1) is removed").arg(key)

#define NODE_ADDED_EXPLANATION(key) \
    tr("The new node (%1) is inserted at the end of the tree").arg(key)

#define ROOT_AND_LAST_NODE_SWAPPED_EXPLANATION(root, lastNode) \
    tr("The root (%1) is swapped with the last node (%2)").arg(root).arg(lastNode)

class HeapAlgorithmVisualizer : public QObject
{
    Q_OBJECT

public:
    virtual void stepForward() = 0;

    virtual void stepBackward() = 0;

signals:
    void nodesHighlighted(int greater, int smaller);

    void nodesSwapped(int greater, int smaller);

    void sortedBoundChanged(int newBound);

    void nodeExtracted();

    void nodeRemoved();

    void nodeAdded();

    void explanationChanged(const QString& explanation);
};

#endif // HEAPALGORITHMVISUALIZER_H
