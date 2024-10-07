#ifndef VISUALIZERMODEL_H
#define VISUALIZERMODEL_H

#include <QObject>
#include <QVariant>
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

    Q_INVOKABLE void setNodeKey(int index, int key);

    Q_INVOKABLE void stepForward();

    Q_INVOKABLE void stepBackward();

    void onNodesSwapped(int greater, int smaller);

    void onNodesHighlighted(int greater, int smaller);

    void onSortedBoundChanged(int newBound);

    void onExplanationChanged(const QString& explanation);

signals:
    void treeChanged();

    void nodesSwapped(int greaterNodeIndex, int smallerNodeIndex);

    void nodesHighlighted(int greaterNodeIndex, int smallerNodeIndex);

    void sortedBoundHighlighted(int sortedBoundIndex);

    void sortedBoundIndexChanged();

    void explanationChanged(const QString& explanation);

private:
    QVariantList m_tree;
    FileManager* m_fileManager;
    HeapAlgorithmVisualizer* m_visualizer;
    int m_sortedBoundIndex;
};

#endif // VISUALIZERMODEL_H
