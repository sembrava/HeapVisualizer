#include "visualizermodel.h"
#include "../../utils/utils.h"

VisualizerModel::VisualizerModel(QVariantList& tree, FileManager* fileManager, HeapAlgorithmVisualizer* visualizer, QObject* parent)
    : m_tree(tree)
    , m_fileManager(fileManager)
    , m_visualizer(visualizer)
    , m_sortedBoundIndex(m_tree.size() + 1)
    , QObject{parent}
{
    connect(m_visualizer, &HeapAlgorithmVisualizer::nodesHighlighted,      this, &VisualizerModel::onNodesHighlighted);
    connect(m_visualizer, &HeapAlgorithmVisualizer::nodesSwapped,          this, &VisualizerModel::onNodesSwapped);
    connect(m_visualizer, &HeapAlgorithmVisualizer::sortedBoundChanged,    this, &VisualizerModel::onSortedBoundChanged);
    connect(m_visualizer, &HeapAlgorithmVisualizer::visualizationReset,    this, &VisualizerModel::onVisualizationReset);
    connect(m_visualizer, &HeapAlgorithmVisualizer::visualizationFinished, this, &VisualizerModel::onVisualizationFinished);
    connect(m_visualizer, &HeapAlgorithmVisualizer::nodeExtracted,         this, &VisualizerModel::onNodeExtracted);
    connect(m_visualizer, &HeapAlgorithmVisualizer::rootKeyChanged,        this, &VisualizerModel::onRootKeyChanged);
    connect(m_visualizer, &HeapAlgorithmVisualizer::nodeRemoved,           this, &VisualizerModel::onNodeRemoved);
    connect(m_visualizer, &HeapAlgorithmVisualizer::nodeAdded,             this, &VisualizerModel::onNodeAdded);
    connect(m_visualizer, &HeapAlgorithmVisualizer::explanationChanged,    this, &VisualizerModel::onExplanationChanged);
}

VisualizerModel::~VisualizerModel()
{
    delete m_visualizer;
}

void VisualizerModel::stepForward()
{
    m_visualizer->stepForward();
}

void VisualizerModel::stepBackward()
{
    m_visualizer->stepBackward();
}

void VisualizerModel::onNodesSwapped(int greater, int smaller, const std::vector<int>& tree)
{
    m_tree = Utils::toQVariantList(tree);
    emit treeChanged();

    emit nodesSwapped(greater, smaller);
}

void VisualizerModel::onNodesHighlighted(int greater, int smaller, const std::vector<int>& tree)
{
    m_tree = Utils::toQVariantList(tree);
    emit treeChanged();

    emit nodesHighlighted(greater, smaller);
}

void VisualizerModel::onSortedBoundChanged(int newBound, const std::vector<int>& tree, const bool shrink)
{
    m_sortedBoundIndex = newBound;

    emit sortedBoundIndexChanged();

    if (shrink)
    {
        emit sortedBoundReverted(newBound - 1);

        return;
    }

    m_tree = Utils::toQVariantList(tree);
    emit treeChanged();

    emit sortedBoundHighlighted(newBound);
}

void VisualizerModel::onVisualizationReset(const std::vector<int>& tree)
{
    m_tree = Utils::toQVariantList(tree);
    emit treeChanged();

    emit visualizationReset();
}

void VisualizerModel::onVisualizationFinished()
{
    emit visualizationFinished();
}

void VisualizerModel::onNodeExtracted(int nodeKey)
{
    emit nodeExtracted(nodeKey);
}

void VisualizerModel::onRootKeyChanged(const std::vector<int>& tree)
{
    m_tree = Utils::toQVariantList(tree);
    emit treeChanged();

    emit rootKeyChanged();
}

void VisualizerModel::onNodeRemoved(const std::vector<int>& tree)
{
    m_tree = Utils::toQVariantList(tree);
    emit treeChanged();

    emit nodeRemoved();
}

void VisualizerModel::onNodeAdded(const std::vector<int>& tree)
{
    m_tree = Utils::toQVariantList(tree);
    emit treeChanged();

    emit nodeAdded();
}

void VisualizerModel::onExplanationChanged(const QString& explanation)
{
    emit explanationChanged(explanation);
}
