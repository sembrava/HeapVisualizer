#include "heapalgorithms.h"

#include <stdexcept>

std::vector<HeapSortSnapshot> HeapAlgorithms::heapSort(std::vector<int>& array)
{
    std::vector<HeapSortSnapshot> snapshots;

    if (array.empty())
        return snapshots;

    for (int i = Utils::getParent(array.size() - 1); i >= 0; i--)
        sink(snapshots, array, i, array.size() - 1, std::nullopt);

    for (int i = array.size() - 1; i > 0; i--)
    {
        Utils::swap(array[0], array[i]);

        createSnapshot(snapshots, array, i, 0, std::nullopt);
        createSnapshot(snapshots, array, i, 0, i);

        sink(snapshots, array, 0, i - 1, std::nullopt);
    }

    createSnapshot(snapshots, array, 0, 0, 0);

    return snapshots;
}

std::vector<RemoveMaxSnapshot> HeapAlgorithms::removeMax(std::vector<int>& array)
{
    std::vector<RemoveMaxSnapshot> snapshots;

    if (array.empty())
        return snapshots;

    const int max = array[0];

    createSnapshot(snapshots, array, std::nullopt, std::nullopt, max);

    array[0] = array[array.size() - 1];

    createSnapshot(snapshots, array, std::nullopt, std::nullopt, max);

    array.pop_back();

    createSnapshot(snapshots, array, std::nullopt, std::nullopt, max);

    sink(snapshots, array, 0, array.size() - 1, max);

    return snapshots;
}

std::vector<AddNodeSnapshot> HeapAlgorithms::addNode(std::vector<int>& array, const int newNodeKey)
{
    std::vector<AddNodeSnapshot> snapshots;

    array.push_back(newNodeKey);

    createSnapshot(snapshots, array, std::nullopt, std::nullopt);

    int greaterIndex = array.size() - 1;
    int smallerIndex = Utils::getParent(greaterIndex);

    while (smallerIndex >= 0 && array[smallerIndex] < array[greaterIndex] && smallerIndex != greaterIndex)
    {
        createSnapshot(snapshots, array, greaterIndex, smallerIndex);

        Utils::swap(array[smallerIndex], array[greaterIndex]);

        createSnapshot(snapshots, array, greaterIndex, smallerIndex);

        greaterIndex = smallerIndex;
        smallerIndex = Utils::getParent(greaterIndex);
    }

    if (smallerIndex != greaterIndex)
        createSnapshot(snapshots, array, greaterIndex, smallerIndex);

    return snapshots;
}
