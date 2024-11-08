#ifndef VISUALIZERMODEL_H
#define VISUALIZERMODEL_H

#include <QObject>
#include <QVariant>
#include <vector>

#include <src/persistence/filemanager.h>
#include <src/model/visualizers/heapalgorithmvisualizer.h>

class VisualizerModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QVariantList tree READ getTree NOTIFY treeChanged)
    Q_PROPERTY(int sortedBoundIndex READ getSortedBoundIndex NOTIFY sortedBoundIndexChanged)

public:
    explicit VisualizerModel(QVariantList& tree, FileManager* fileManager, HeapAlgorithmVisualizer* visualizer, QObject* parent = nullptr);

    ~VisualizerModel();

    QVariantList getTree() const { return m_tree; }

    int getSortedBoundIndex() const { return m_sortedBoundIndex; }

    Q_INVOKABLE void stepForward();

    Q_INVOKABLE void stepBackward();

    void onNodesSwapped(int greater, int smaller, const std::vector<int>& tree);

    void onNodesHighlighted(int greater, int smaller, const std::vector<int>& tree);

    void onSortedBoundChanged(int newBound, const std::vector<int>& tree, const bool shrink);

    void onVisualizationReset(const std::vector<int>& tree);

    void onVisualizationFinished();

    void onNodeExtracted(int nodeKey);

    void onRootKeyChanged(const std::vector<int>& tree);

    void onNodeRemoved(const std::vector<int>& tree);

    void onNodeAdded(const std::vector<int>& tree);

    void onExplanationChanged(const QString& explanation);

signals:
    void treeChanged();

    void nodesSwapped(int greaterNodeIndex, int smallerNodeIndex);

    void nodesHighlighted(int greaterNodeIndex, int smallerNodeIndex);

    void sortedBoundHighlighted(int sortedBoundIndex);

    void sortedBoundIndexChanged();

    void sortedBoundReverted(int newBound);

    void visualizationReset();

    void visualizationFinished();

    void nodeExtracted(int nodeKey);

    void rootKeyChanged();

    void nodeRemoved();

    void nodeAdded();

    void explanationChanged(const QString& explanation);

private:
    QVariantList m_tree;
    FileManager* m_fileManager;
    HeapAlgorithmVisualizer* m_visualizer;
    int m_sortedBoundIndex;
};

#endif // VISUALIZERMODEL_H
