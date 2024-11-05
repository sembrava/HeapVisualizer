#ifndef HEAPALGORITHMVISUALIZER_H
#define HEAPALGORITHMVISUALIZER_H

#include <QObject>

#define COMPARED_NODE_INDEXES_CHANGED_EXPLANATION(greater, smaller) \
    tr("The current node (%1) is compared with its greatest child (%2)").arg(smaller).arg(greater)

#define COMPARED_NODES_SWAPPED_EXPLANATION(greater, smaller) \
    tr("Since %2 is greater than %1, they are swapped").arg(greater).arg(smaller)

#define COMPARED_NODES_NOT_SWAPPED_EXPLANATION(greater, smaller) \
    tr("Since %1 is not greater than %2, they are not swapped").arg(greater).arg(smaller)

#define SORTED_BOUND_INDEX_CHANGED_EXPLANATION(key) \
    tr("%1 is in its correct position, so it can be marked as sorted").arg(key)

#define NODE_EXTRACTED_EXPLANATION(key) \
    tr("The largest value (%1) is copied").arg(key)

#define ROOT_KEY_CHANGED_EXPLANATION(rootKey, lastNodeKey) \
    tr("The root key (%1) is replaced with the key of the last node (%2)").arg(rootKey).arg(lastNodeKey)

#define NODE_REMOVED_EXPLANATION(key) \
    tr("The last node (%1) is removed").arg(key)

#define NODE_ADDED_EXPLANATION(key) \
    tr("The new node (%1) is inserted at the end of the tree").arg(key)

#define ROOT_AND_LAST_NODE_SWAPPED_EXPLANATION(root, lastNode) \
    tr("The root (%2) is swapped with the last unsorted node (%1)").arg(root).arg(lastNode)

#define HEAP_SORT_FINISHED_EXPLANATION \
    tr("All nodes are in their correct positions")

#define REMOVE_MAX_FINISHED_EXPLANATION \
    tr("The extracted key can be returned")

class HeapAlgorithmVisualizer : public QObject
{
    Q_OBJECT

public:
    virtual ~HeapAlgorithmVisualizer() = default;

    virtual void stepForward() = 0;

    virtual void stepBackward() = 0;

signals:
    void nodesHighlighted(int greater, int smaller, const std::vector<int>& tree);

    void nodesSwapped(int greater, int smaller, const std::vector<int>& tree);

    void sortedBoundChanged(int newBound, const std::vector<int>& tree, const bool shrink = false);

    void visualizationReset(const std::vector<int>& tree);

    void nodeExtracted(int nodeKey);

    void rootKeyChanged(const std::vector<int>& tree);

    void nodeRemoved(const std::vector<int>& tree);

    void nodeAdded();

    void explanationChanged(const QString& explanation);
};

#endif // HEAPALGORITHMVISUALIZER_H
