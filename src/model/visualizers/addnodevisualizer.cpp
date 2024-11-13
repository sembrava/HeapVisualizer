#include "addnodevisualizer.h"
#include "../heapalgorithms.h"

AddNodeVisualizer::AddNodeVisualizer(std::vector<int>& array, int newNodeKey)
    : m_snapshots(HeapAlgorithms::addNode(array, newNodeKey))
    , m_currentSnapshotIndex(-1)
{}

void AddNodeVisualizer::stepForward()
{
    if (m_currentSnapshotIndex > static_cast<int>(m_snapshots.size() - 1))
        return;

    m_currentSnapshotIndex++;

    if (m_currentSnapshotIndex == m_snapshots.size())
    {
        emit explanationChanged(addNodeFinishedExplanation());

        emit visualizationFinished();

        return;
    }

    const AddNodeSnapshot& currentSnapshot = m_snapshots[m_currentSnapshotIndex];
    const std::vector<int>& currentTree = currentSnapshot.getTree();

    if (m_currentSnapshotIndex == 0)
    {
        emit nodeAdded(currentTree);

        emit explanationChanged(nodeAddedExplanation(currentTree[currentTree.size() - 1]));
    }

    else
    {
        const AddNodeSnapshot& previousSnapshot = m_snapshots[m_currentSnapshotIndex - 1];
        const std::vector<int>& previousTree = previousSnapshot.getTree();

        if (currentSnapshot.getGreaterComparedNodeIndex().has_value() && currentSnapshot.getSmallerComparedNodeIndex().has_value() &&
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

void AddNodeVisualizer::stepBackward()
{
    if (m_currentSnapshotIndex < 0)
        return;

    if (m_currentSnapshotIndex == 0)
    {
        m_currentSnapshotIndex = -1;

        std::vector<int> inputTree = m_snapshots[0].getTree();

        inputTree.pop_back();

        emit visualizationReset(inputTree);
        emit explanationChanged("");

        return;
    }

    m_currentSnapshotIndex -= 2;

    stepForward();
}
