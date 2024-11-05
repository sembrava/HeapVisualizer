#ifndef REMOVEMAXVISUALIZER_H
#define REMOVEMAXVISUALIZER_H

#include "heapalgorithmvisualizer.h"

#include <src/model/snapshots/removemaxsnapshot.h>

class RemoveMaxVisualizer : public HeapAlgorithmVisualizer
{
public:
    explicit RemoveMaxVisualizer(std::vector<int>& array);

    void stepForward() override;

    void stepBackward() override;

private:
    std::vector<RemoveMaxSnapshot> m_snapshots;
    int m_currentSnapshotIndex;
};

#endif // REMOVEMAXVISUALIZER_H
