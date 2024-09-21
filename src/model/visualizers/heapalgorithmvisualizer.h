#ifndef HEAPALGORITHMVISUALIZER_H
#define HEAPALGORITHMVISUALIZER_H

#include <QObject>

class HeapAlgorithmVisualizer : public QObject
{
    Q_OBJECT

public:
    virtual void stepForward() = 0;

    virtual void stepBackward() = 0;

    virtual void generateSnapshots() = 0;

signals:
    void comparedNodeIndexesChanged(int greater, int smaller);

    void comparedNodesSwapped(int greater, int smaller);

    void sortedBoundIndexChanged(int bound);

    void nodeExtracted();

    void nodeRemoved();

    void nodeAdded();
};

#endif // HEAPALGORITHMVISUALIZER_H
