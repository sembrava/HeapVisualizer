#ifndef HEAPSORTVISUALIZER_H
#define HEAPSORTVISUALIZER_H

#include <vector>

#include "heapalgorithmvisualizer.h"
#include "../snapshots/heapsortsnapshot.h"

class HeapSortVisualizer : public HeapAlgorithmVisualizer
{
public:
    explicit HeapSortVisualizer(std::vector<int>& array);

    void stepForward() override;

    void stepBackward() override;

private:
    std::vector<HeapSortSnapshot> m_snapshots;
    int m_currentSnapshotIndex;
};

#endif // HEAPSORTVISUALIZER_H
