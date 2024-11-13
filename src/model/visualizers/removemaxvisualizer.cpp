#include "removemaxvisualizer.h"

#include <src/model/heapalgorithms.h>

RemoveMaxVisualizer::RemoveMaxVisualizer(std::vector<int>& array)
    : m_snapshots(HeapAlgorithms::removeMax(array))
    , m_currentSnapshotIndex(-1)
{}

void RemoveMaxVisualizer::stepForward()
{
    if (m_currentSnapshotIndex > static_cast<int>(m_snapshots.size() - 1))
        return;

    m_currentSnapshotIndex++;

    if (m_currentSnapshotIndex == m_snapshots.size())
    {
        emit explanationChanged(removeMaxFinishedExplanation());

        emit visualizationFinished();

        return;
    }

    const RemoveMaxSnapshot& currentSnapshot = m_snapshots[m_currentSnapshotIndex];
    const std::vector<int>& currentTree = currentSnapshot.getTree();

    if (m_currentSnapshotIndex == 0)
    {
        emit nodeExtracted(m_snapshots[0].getExtractedNodeKey());

        emit explanationChanged(nodeExtractedExplanation(m_snapshots[0].getExtractedNodeKey()));
    }

    else if (m_currentSnapshotIndex == 1)
    {
        emit rootKeyChanged(currentTree);

        emit explanationChanged(rootKeyChangedExplanation(m_snapshots[m_currentSnapshotIndex - 1].getTree()[0], currentTree[currentTree.size() - 1]));
    }

    else
    {
        const RemoveMaxSnapshot& previousSnapshot = m_snapshots[m_currentSnapshotIndex - 1];
        const std::vector<int>& previousTree = previousSnapshot.getTree();

        if (currentSnapshot.getTree().size() < previousSnapshot.getTree().size())
        {
            emit nodeRemoved(currentTree);

            emit explanationChanged(nodeRemovedExplanation(previousTree[previousTree.size() - 1]));
        }

        else if (currentSnapshot.getGreaterComparedNodeIndex().has_value() && currentSnapshot.getSmallerComparedNodeIndex().has_value() &&
                 !previousSnapshot.getGreaterComparedNodeIndex().has_value() && !previousSnapshot.getGreaterComparedNodeIndex().has_value())
        {
            emit nodesHighlighted(
                currentSnapshot.getGreaterComparedNodeIndex().value(), currentSnapshot.getSmallerComparedNodeIndex().value(), currentTree
            );

            emit explanationChanged(
                comparedNodeIndexesChangedExplanation(
                    currentTree[currentSnapshot.getGreaterComparedNodeIndex().value()], currentTree[currentSnapshot.getSmallerComparedNodeIndex().value()]
                )
            );
        }

        else if (currentSnapshot.getGreaterComparedNodeIndex().has_value() && currentSnapshot.getSmallerComparedNodeIndex().has_value() &&
                 previousSnapshot.getGreaterComparedNodeIndex().has_value() && previousSnapshot.getGreaterComparedNodeIndex().has_value())
        {
            if (currentSnapshot.getGreaterComparedNodeIndex().value() != previousSnapshot.getGreaterComparedNodeIndex().value() ||
                currentSnapshot.getSmallerComparedNodeIndex().value() != previousSnapshot.getSmallerComparedNodeIndex().value())
            {
                emit nodesHighlighted(
                    currentSnapshot.getGreaterComparedNodeIndex().value(), currentSnapshot.getSmallerComparedNodeIndex().value(), currentTree
                );

                emit explanationChanged(
                    comparedNodeIndexesChangedExplanation(
                        currentTree[currentSnapshot.getGreaterComparedNodeIndex().value()], currentTree[currentSnapshot.getSmallerComparedNodeIndex().value()]
                    )
                );
            }

            else
            {
                if (currentTree[currentSnapshot.getGreaterComparedNodeIndex().value()] == previousTree[previousSnapshot.getSmallerComparedNodeIndex().value()] &&
                    currentTree[currentSnapshot.getSmallerComparedNodeIndex().value()] == previousTree[previousSnapshot.getGreaterComparedNodeIndex().value()])
                {
                    emit nodesSwapped(
                        currentSnapshot.getGreaterComparedNodeIndex().value(), currentSnapshot.getSmallerComparedNodeIndex().value(), currentTree
                    );

                    emit explanationChanged(
                        comparedNodesSwappedExplanation(
                            currentTree[currentSnapshot.getGreaterComparedNodeIndex().value()], currentTree[currentSnapshot.getSmallerComparedNodeIndex().value()]
                        )
                    );
                }
            }
        }
    }
}

void RemoveMaxVisualizer::stepBackward()
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

    m_currentSnapshotIndex -= 2;

    stepForward();
}
