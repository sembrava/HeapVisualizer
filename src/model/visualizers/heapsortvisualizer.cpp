#include "heapsortvisualizer.h"
#include "../heapalgorithms.h"

HeapSortVisualizer::HeapSortVisualizer(std::vector<int>& array, const bool documentHeapification)
    : m_snapshots(HeapAlgorithms::heapSort(array, documentHeapification))
    , m_currentSnapshotIndex(0)
{}

void HeapSortVisualizer::stepForward()
{
    if (m_currentSnapshotIndex >= m_snapshots.size())
        return;

    const HeapSortSnapshot& currentSnapshot = m_snapshots[m_currentSnapshotIndex];
    const std::vector<int>& currentTree = currentSnapshot.getTree();

    if (m_currentSnapshotIndex == m_snapshots.size() - 1 && currentSnapshot.getSortedBoundIndex().has_value())
    {
        emit sortedBoundChanged(currentSnapshot.getSortedBoundIndex().value());

        // TODO: emit step forward disable or maybe expose current snapshot index to qml and disable dynamically
    }

    else if (m_currentSnapshotIndex == 0)
    {
        emit nodesHighlighted(
            currentSnapshot.getGreaterComparedNodeIndex(), currentSnapshot.getSmallerComparedNodeIndex()
        );

        emit explanationChanged(
            COMPARED_NODE_INDEXES_CHANGED_EXPLANATION(
                currentTree[currentSnapshot.getGreaterComparedNodeIndex()], currentTree[currentSnapshot.getSmallerComparedNodeIndex()]
            )
        );
    }

    else
    {
        const HeapSortSnapshot& previousSnapshot = m_snapshots[m_currentSnapshotIndex - 1];
        const std::vector<int>& previousTree = previousSnapshot.getTree();

        if (currentSnapshot.getSortedBoundIndex().has_value())
        {
            // sorted bound present, so it has changed

            emit sortedBoundChanged(currentSnapshot.getSortedBoundIndex().value());

            emit explanationChanged(SORTED_BOUND_INDEX_CHANGED_EXPLANATION(currentSnapshot.getSortedBoundIndex().value()));
        }

        else if (m_snapshots[m_currentSnapshotIndex + 1].getSortedBoundIndex().has_value())
        {
            // next snapshot increases the sorted bound, so this snapshot was a swap between root and last node

            emit nodesSwapped(
                currentSnapshot.getGreaterComparedNodeIndex(), currentSnapshot.getSmallerComparedNodeIndex()
            );

            emit explanationChanged(ROOT_AND_LAST_NODE_SWAPPED_EXPLANATION(currentTree[0], currentTree[currentTree.size() - 1]));
        }

        else
        {
            // no sorted bound, so a swap would be in the sink stage

            if (currentSnapshot.getGreaterComparedNodeIndex() != previousSnapshot.getGreaterComparedNodeIndex() ||
                currentSnapshot.getSmallerComparedNodeIndex() != previousSnapshot.getSmallerComparedNodeIndex())
            {
                // compared nodes differ from the previous snapshot, so we're comparing new nodes

                emit nodesHighlighted(
                    currentSnapshot.getGreaterComparedNodeIndex(), currentSnapshot.getSmallerComparedNodeIndex()
                );

                emit explanationChanged(
                    COMPARED_NODE_INDEXES_CHANGED_EXPLANATION(
                        currentTree[currentSnapshot.getGreaterComparedNodeIndex()], currentTree[currentSnapshot.getSmallerComparedNodeIndex()]
                    )
                );
            }

            else
            {
                // compared nodes are the same as the previous snapshot

                if (currentTree[currentSnapshot.getGreaterComparedNodeIndex()] == previousTree[previousSnapshot.getSmallerComparedNodeIndex()] &&
                    currentTree[currentSnapshot.getSmallerComparedNodeIndex()] == previousTree[previousSnapshot.getGreaterComparedNodeIndex()])
                {
                    // the values in the compared nodes are the opposite of the previous snapshot, so they've been swapped

                    emit nodesSwapped(
                        currentSnapshot.getGreaterComparedNodeIndex(), currentSnapshot.getSmallerComparedNodeIndex()
                    );

                    emit explanationChanged(
                        COMPARED_NODES_SWAPPED_EXPLANATION(
                            currentTree[currentSnapshot.getGreaterComparedNodeIndex()], currentTree[currentSnapshot.getSmallerComparedNodeIndex()]
                        )
                    );
                }
            }
        }
    }

    if (m_currentSnapshotIndex < m_snapshots.size())
        m_currentSnapshotIndex++;
}

void HeapSortVisualizer::stepBackward()
{
    const HeapSortSnapshot& currentSnapshot = m_snapshots[m_currentSnapshotIndex];

    m_currentSnapshotIndex--;
}
