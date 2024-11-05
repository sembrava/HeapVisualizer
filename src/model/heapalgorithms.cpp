#include "heapalgorithms.h"

#include <stdexcept>

std::vector<HeapSortSnapshot> HeapAlgorithms::heapSort(std::vector<int>& array, const bool documentHeapification)
{
    if (array.empty())
        throw std::invalid_argument("The provided array is empty");

    std::vector<HeapSortSnapshot> snapshots;

    for (int i = Utils::getParent(array.size() - 1); i >= 0; i--)
        sink(snapshots, array, i, array.size() - 1, std::nullopt);

    if (!documentHeapification)
        snapshots.clear();

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
    if (array.empty())
        throw std::invalid_argument("The provided tree is empty");

    std::vector<RemoveMaxSnapshot> snapshots;

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
    if (array.empty())
        throw std::invalid_argument("The provided tree is empty");

    std::vector<AddNodeSnapshot> snapshots;

    array.push_back(newNodeKey);

    createSnapshot(snapshots, array, std::nullopt, std::nullopt);

    int greaterIndex = array.size() - 1;
    int smallerIndex = Utils::getParent(greaterIndex);

    while (smallerIndex >= 0)
    {
        createSnapshot(snapshots, array, greaterIndex, smallerIndex);

        if (array[smallerIndex] < array[greaterIndex])
        {
            Utils::swap(array[smallerIndex], array[greaterIndex]);

            createSnapshot(snapshots, array, greaterIndex, smallerIndex);
        }

        else break;
    }

    createSnapshot(snapshots, array, greaterIndex, smallerIndex);

    return snapshots;
}
