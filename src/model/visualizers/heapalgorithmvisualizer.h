#ifndef HEAPALGORITHMVISUALIZER_H
#define HEAPALGORITHMVISUALIZER_H

#include <QObject>

#include "../../globals.h"

class HeapAlgorithmVisualizer : public QObject
{
    Q_OBJECT

public:
    virtual ~HeapAlgorithmVisualizer() = default;

    virtual void stepForward() = 0;

    virtual void stepBackward() = 0;

signals:
    void nodesHighlighted(int greater, int smaller, const std::vector<int>& tree);

    void nodesSwapped(int greater, int smaller, const std::vector<int>& tree);

    void sortedBoundChanged(int newBound, const std::vector<int>& tree, const bool shrink = false);

    void visualizationReset(const std::vector<int>& tree);

    void visualizationFinished();

    void nodeExtracted(int nodeKey);

    void rootKeyChanged(const std::vector<int>& tree);

    void nodeRemoved(const std::vector<int>& tree);

    void nodeAdded(const std::vector<int>& tree);

    void explanationChanged(const QString& explanation);

protected:
    static QString comparedNodeIndexesChangedExplanation(int greater, int smaller)
    {
        return QString::fromStdString(g_qmlGlobals.getLanguage() == "hu"
        ? "A jelenlegi csúcs kulcsát (" + std::to_string(smaller) + ") összehasonlítjuk a legnagyobb gyerekével (" + std::to_string(greater) + ")"
        : "The current key (" + std::to_string(smaller) + ") is compared with its greatest child (" + std::to_string(greater) + ")");
    }

    static QString comparedNodesSwappedExplanation(int greater, int smaller)
    {
        return QString::fromStdString(g_qmlGlobals.getLanguage() == "hu"
        ? "Mivel " + std::to_string(smaller) + " nagyobb, mint " + std::to_string(greater) + ", megcseréljük őket"
        : "Since " + std::to_string(smaller) + " is greater than " + std::to_string(greater) + ", they are swapped");
    }

    static QString sortedBoundIndexChangedExplanation(int key)
    {
        return QString::fromStdString(g_qmlGlobals.getLanguage() == "hu"
        ? std::to_string(key) + " a helyére került, ezért megjelölhetjük rendezettként"
        : std::to_string(key) + " is in its correct position, so it can be marked as sorted");
    }

    static QString rootAndLastNodeSwappedExplanation(int root, int lastNode)
    {
        return QString::fromStdString(g_qmlGlobals.getLanguage() == "hu"
        ? "A gyökér kulcsát (" + std::to_string(lastNode) + ") megcseréljük az utolsó rendezetlen csúcs kulcsával (" + std::to_string(root) + ")"
        : "The root key (" + std::to_string(lastNode) + ") is swapped with the key of the last unsorted node (" + std::to_string(root) + ")");
    }

    static QString heapSortFinishedExplanation()
    {
        return QString::fromStdString(g_qmlGlobals.getLanguage() == "hu"
        ? "Az összes kulcs a helyére került"
        : "All keys are in their correct positions");
    }

    static QString nodeExtractedExplanation(int key)
    {
        return QString::fromStdString(g_qmlGlobals.getLanguage() == "hu"
        ? "A legnagyobb kulcsot (" + std::to_string(key) + ") kimásoljuk"
        : "The largest key (" + std::to_string(key) + ") is copied");
    }

    static QString rootKeyChangedExplanation(int rootKey, int lastNodeKey)
    {
        return QString::fromStdString(g_qmlGlobals.getLanguage() == "hu"
        ? "A gyökér kulcsát (" + std::to_string(rootKey) + ") kicseréljuk az utolsó csúcs kulcsával (" + std::to_string(lastNodeKey) + ")"
        : "The root key (" + std::to_string(rootKey) + ") is replaced with the key of the last node (" + std::to_string(lastNodeKey) + ")");
    }

    static QString removeMaxFinishedExplanation()
    {
        return QString::fromStdString(g_qmlGlobals.getLanguage() == "hu"
        ? "A kimásolt kulcs lesz a visszaadott érték"
        : "The extracted key can be returned");
    }

    static QString nodeRemovedExplanation(int key)
    {
        return QString::fromStdString(g_qmlGlobals.getLanguage() == "hu"
        ? "Az utolsó csúcsot (" + std::to_string(key) + ") kitöröljük"
        : "The last node (" + std::to_string(key) + ") is removed");
    }

    static QString nodeAddedExplanation(int key)
    {
        return QString::fromStdString(g_qmlGlobals.getLanguage() == "hu"
        ? "Az új csúcsot (" + std::to_string(key) + ") beillesztjük a fa végére"
        : "The new node (" + std::to_string(key) + ") is inserted at the end of the tree");
    }

    static QString addNodeFinishedExplanation()
    {
        return QString::fromStdString(g_qmlGlobals.getLanguage() == "hu"
        ? "A beillesztett kulcs a helyére került"
        : "The inserted node has been moved to its correct position");
    }
};

#endif // HEAPALGORITHMVISUALIZER_H
