#ifndef ADDNODEVISUALIZER_H
#define ADDNODEVISUALIZER_H

#include "heapalgorithmvisualizer.h"

#include <src/model/snapshots/addnodesnapshot.h>

class AddNodeVisualizer : public HeapAlgorithmVisualizer
{
public:
    explicit AddNodeVisualizer(std::vector<int>& array, int newNodeKey);

    void stepForward() override;

    void stepBackward() override;

private:
    std::vector<AddNodeSnapshot> m_snapshots;
    int m_currentSnapshotIndex;
};

#endif // ADDNODEVISUALIZER_H
