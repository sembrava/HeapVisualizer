#include "visualizermodel.h"

VisualizerModel::VisualizerModel(QVariantList& tree, FileManager* fileManager, HeapAlgorithmVisualizer* visualizer, QObject *parent)
    : m_tree(tree)
    , m_fileManager(fileManager)
    , m_visualizer(visualizer)
    , m_sortedBoundIndex(m_tree.size())
    , QObject{parent}
{
    connect(m_visualizer, &HeapAlgorithmVisualizer::nodesHighlighted,   this, &VisualizerModel::onNodesHighlighted);
    connect(m_visualizer, &HeapAlgorithmVisualizer::nodesSwapped,       this, &VisualizerModel::onNodesSwapped);
    connect(m_visualizer, &HeapAlgorithmVisualizer::sortedBoundChanged, this, &VisualizerModel::onSortedBoundChanged);
}

VisualizerModel::~VisualizerModel()
{
    delete m_visualizer;
}

void VisualizerModel::setNodeKey(int index, int key)
{
    m_tree[index] = key;

    emit treeChanged();
}

void VisualizerModel::stepForward()
{
    m_visualizer->stepForward();
}

void VisualizerModel::stepBackward()
{
    m_visualizer->stepBackward();
}

void VisualizerModel::onNodesSwapped(int greater, int smaller)
{
    emit nodesSwapped(greater, smaller);
}

void VisualizerModel::onNodesHighlighted(int greater, int smaller)
{
    emit nodesHighlighted(greater, smaller);
}

void VisualizerModel::onSortedBoundChanged(int newBound)
{
    m_sortedBoundIndex = newBound;

    emit sortedBoundHighlighted(newBound);
}
