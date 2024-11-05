function isMaxHeap(array) {
    for (let i = 0; i < array.length; i++) {
        const leftChild = 2 * i + 1;
        const rightChild = 2 * i + 2;

        if (leftChild < array.length && array[i] < array[leftChild]) {
            return false;
        }

        if (rightChild < array.length && array[i] < array[rightChild]) {
            return false;
        }
    }
    return true;
}

function heapify(array) {
    for (let i = Math.floor(array.length / 2) - 1; i >= 0; i--) {
        sink(array, i, array.length);
    }
}

function sink(array, i, max) {
    let largest = i;
    const leftChild = 2 * i + 1;
    const rightChild = 2 * i + 2;

    if (leftChild < max && array[leftChild] > array[largest]) {
        largest = leftChild;
    }

    if (rightChild < max && array[rightChild] > array[largest]) {
        largest = rightChild;
    }

    if (largest !== i) {
        [array[i], array[largest]] = [array[largest], array[i]];
        sink(array, largest, max);
    }
}
