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

        emit explanationChanged(SORTED_BOUND_INDEX_CHANGED_EXPLANATION(currentTree[currentSnapshot.getSortedBoundIndex().value()]));

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
            emit sortedBoundChanged(currentSnapshot.getSortedBoundIndex().value());

            emit explanationChanged(SORTED_BOUND_INDEX_CHANGED_EXPLANATION(currentTree[currentSnapshot.getSortedBoundIndex().value()]));
        }

        else if (m_snapshots[m_currentSnapshotIndex + 1].getSortedBoundIndex().has_value())
        {
            emit nodesSwapped(
                currentSnapshot.getGreaterComparedNodeIndex(), currentSnapshot.getSmallerComparedNodeIndex()
            );

            emit explanationChanged(
                ROOT_AND_LAST_NODE_SWAPPED_EXPLANATION(
                    currentTree[0], currentTree[m_snapshots[m_currentSnapshotIndex + 1].getSortedBoundIndex().value()]
                )
            );
        }

        else
        {
            if (currentSnapshot.getGreaterComparedNodeIndex() != previousSnapshot.getGreaterComparedNodeIndex() ||
                currentSnapshot.getSmallerComparedNodeIndex() != previousSnapshot.getSmallerComparedNodeIndex())
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
                if (currentTree[currentSnapshot.getGreaterComparedNodeIndex()] == previousTree[previousSnapshot.getSmallerComparedNodeIndex()] &&
                    currentTree[currentSnapshot.getSmallerComparedNodeIndex()] == previousTree[previousSnapshot.getGreaterComparedNodeIndex()])
                {
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

    if (m_currentSnapshotIndex < m_snapshots.size() - 1)
        m_currentSnapshotIndex++;
}

void HeapSortVisualizer::stepBackward()
{
    if (m_currentSnapshotIndex <= 0)
        return;

    if (m_currentSnapshotIndex < 2)
        m_currentSnapshotIndex--;

    else
        m_currentSnapshotIndex -= 2;

    stepForward();
}
