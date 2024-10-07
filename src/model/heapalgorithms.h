#ifndef HEAPALGORITHMS_H
#define HEAPALGORITHMS_H

#include <vector>

#include "snapshots/heapsortsnapshot.h"
#include "snapshots/removemaxsnapshot.h"
#include "snapshots/addnodesnapshot.h"
#include "../utils/utils.h"

/**
 * @brief Provides methods for basic heap algorithms that also capture their state during execution
 * to be used for the visualization.
 */
class HeapAlgorithms
{
public:
    /**
     * @brief Standard heap sort implementation. A snapshot of the array state and additional
     * metadata needed for the visualization is captured during the execution of the algorithm. Only
     * works with arrays with a size greater than 0.
     *
     * @param array The array to be sorted.
     * @param documentHeapification If false, snapshots captured during the heapification stage of
     * the algorithm will be discarded. This can be useful if we don't want to visualize this stage.
     * @return An array of the captured snaphsots.
     * @throws std::invalid_argument If the given array is empty.
     */
    static std::vector<HeapSortSnapshot> heapSort(std::vector<int>& array, const bool documentHeapification);

    /**
     * @brief Removes the largest element in the array, which is always at index 0 and restores the
     * heap property. A snapshot of the array state and additional metadata needed for the
     * visualization is captured during the execution of the algorithm. Only works with arrays with
     * a size greater than 0.
     *
     * @param array The array on which the algorithm will be performed.
     * @return An array of the captured snapshots.
     * @throws std::invalid_argument If the given array is empty.
     */
    static std::vector<RemoveMaxSnapshot> removeMax(std::vector<int>& array);

    /**
     * @brief Appends a new element to the end of the array and restores the heap property. A
     * snapshot of the array state and additional metadata needed for the visualization is captured
     * during the execution of the algorithm. Only works with arrays with a size greater than 0.
     *
     * @param array The array to which the element will be appended.
     * @param newNodeKey The value of the new element.
     * @return An array of the captured snapshots.
     * @throws std::invalid_argument If the given array is empty.
     */
    static std::vector<AddNodeSnapshot> addNode(std::vector<int>& array, const int newNodeKey);

private:
    /**
     * @brief A helper method that swaps the currently inspected element with its greatest child
     * until it is greater than both of its children.
     *
     * @param snapshots An array of algorithm states that is used in the visualization.
     * @param array The array on which the algorithm will be performed.
     * @param startIndex The index of the element that should be sinked.
     * @param greaterBoundIndex The index at which the algorithm will definitely stop. This is used
     * to avoid index overflow errors and mutation of the already sorted portion of the array in a
     * heap sort.
     * @param args Additional arguments needed for creating snapshots.
     */
    template <typename TSnapshot, typename... TArgs>
    static void sink(std::vector<TSnapshot>& snapshots, std::vector<int>& array, const int startIndex, const int greaterBoundIndex, TArgs&&... args)
    {
        int smallerIndex = startIndex;
        int greaterIndex = Utils::getLeftChild(startIndex);

        while (greaterIndex <= greaterBoundIndex)
        {
            if (greaterIndex + 1 <= greaterBoundIndex && array[greaterIndex + 1] > array[greaterIndex])
                greaterIndex++;

            createSnapshot(snapshots, array, greaterIndex, smallerIndex, std::forward<TArgs>(args)...);

            if (array[smallerIndex] < array[greaterIndex])
            {
                Utils::swap(array[smallerIndex], array[greaterIndex]);

                createSnapshot(snapshots, array, greaterIndex, smallerIndex, std::forward<TArgs>(args)...);

                smallerIndex = greaterIndex;
                greaterIndex = Utils::getLeftChild(greaterIndex);
            }

            else break;
        }
    }

    /**
     * @brief Creates a new snapshot and appends it to the given array of snapshots.
     *
     * @param snapshots The array of snapshots to which the newly created snapshot should be appended.
     * @param args The arguments needed for the creation of the snapshot.
     */
    template <typename TSnapshot, typename... TArgs>
    static void createSnapshot(std::vector<TSnapshot>& snapshots, TArgs... args)
    {
        snapshots.emplace_back(std::forward<TArgs>(args)...);
    }
};

#endif // HEAPALGORITHMS_H
