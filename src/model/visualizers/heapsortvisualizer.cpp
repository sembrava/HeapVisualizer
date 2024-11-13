#include "heapsortvisualizer.h"
#include "../heapalgorithms.h"

HeapSortVisualizer::HeapSortVisualizer(std::vector<int>& array, const bool documentHeapification)
    : m_snapshots(HeapAlgorithms::heapSort(array, documentHeapification))
    , m_currentSnapshotIndex(-1)
{}

void HeapSortVisualizer::stepForward()
{
    if (m_currentSnapshotIndex > static_cast<int>(m_snapshots.size() - 1))
        return;

    m_currentSnapshotIndex++;

    if (m_currentSnapshotIndex == m_snapshots.size())
    {
        emit explanationChanged(heapSortFinishedExplanation());

        return;
    }

    const HeapSortSnapshot& currentSnapshot = m_snapshots[m_currentSnapshotIndex];
    const std::vector<int>& currentTree = currentSnapshot.getTree();

    if (m_currentSnapshotIndex == m_snapshots.size() - 1 && currentSnapshot.getSortedBoundIndex().has_value())
    {
        emit sortedBoundChanged(currentSnapshot.getSortedBoundIndex().value(), currentTree);

        emit explanationChanged(sortedBoundIndexChangedExplanation(currentTree[currentSnapshot.getSortedBoundIndex().value()]));

        // TODO: emit step forward disable or maybe expose current snapshot index to qml and disable dynamically
    }

    else if (m_currentSnapshotIndex == 0)
    {
        emit nodesHighlighted(
            currentSnapshot.getGreaterComparedNodeIndex(), currentSnapshot.getSmallerComparedNodeIndex(), currentTree
        );

        emit explanationChanged(
            comparedNodeIndexesChangedExplanation(
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
            emit sortedBoundChanged(currentSnapshot.getSortedBoundIndex().value(), currentTree);

            emit explanationChanged(sortedBoundIndexChangedExplanation(currentTree[currentSnapshot.getSortedBoundIndex().value()]));
        }

        else if (m_snapshots[m_currentSnapshotIndex + 1].getSortedBoundIndex().has_value())
        {
            emit nodesSwapped(
                currentSnapshot.getGreaterComparedNodeIndex(), currentSnapshot.getSmallerComparedNodeIndex(), currentTree
            );

            emit explanationChanged(
                rootAndLastNodeSwappedExplanation(
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
                    currentSnapshot.getGreaterComparedNodeIndex(), currentSnapshot.getSmallerComparedNodeIndex(), currentTree
                );

                emit explanationChanged(
                    comparedNodeIndexesChangedExplanation(
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
                        currentSnapshot.getGreaterComparedNodeIndex(), currentSnapshot.getSmallerComparedNodeIndex(), currentTree
                    );

                    emit explanationChanged(
                        comparedNodesSwappedExplanation(
                            currentTree[currentSnapshot.getGreaterComparedNodeIndex()], currentTree[currentSnapshot.getSmallerComparedNodeIndex()]
                        )
                    );
                }
            }
        }
    }
}

void HeapSortVisualizer::stepBackward()
{
    if (m_currentSnapshotIndex < 0)
        return;

    if (m_currentSnapshotIndex == 0)
    {
        m_currentSnapshotIndex = -1;

        emit visualizationReset(m_snapshots[0].getTree());
        emit explanationChanged("");

        return;
    }

    if (m_currentSnapshotIndex < m_snapshots.size() && m_snapshots[m_currentSnapshotIndex].getSortedBoundIndex().has_value())
        emit sortedBoundChanged(m_snapshots[m_currentSnapshotIndex].getSortedBoundIndex().value() + 1, m_snapshots[m_currentSnapshotIndex].getTree(), true);

    m_currentSnapshotIndex -= 2;

    stepForward();
}
