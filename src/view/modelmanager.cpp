#include <QQmlEngine>
#include <vector>
#include <QVariant>

#include <src/model/visualizers/removemaxvisualizer.h>

#include "src/model/visualizers/addnodevisualizer.h"
#include "src/model/visualizers/heapsortvisualizer.h"
#include "modelmanager.h"
#include "models/homemodel.h"
#include "models/editormodel.h"
#include "models/visualizermodel.h"
#include "models/settingsmodel.h"
#include "../globals.h"

ModelManager::ModelManager(QObject *parent)
    : QObject{parent}
{}

QObject* ModelManager::createHomePageModel()
{
    return configureModel(new HomeModel(g_fileManager));
}

QObject* ModelManager::createEditorPageModel(QVariantList tree)
{
    QVariantList treeCopy;

    for (const QVariant& node : tree)
    {
        treeCopy.push_back(node.toInt());
    }

    return configureModel(new EditorModel(treeCopy, g_fileManager));
}

QObject* ModelManager::createVisualizerPageModel(QVariantList tree, const QString& algorithmName, const int newNodeKey)
{
    std::vector<int> vectorTree;

    for (const QVariant& node : tree)
    {
        vectorTree.push_back(qvariant_cast<int>(node));
    }

    HeapAlgorithmVisualizer* visualizer = nullptr;

    if (algorithmName == "heapSort")
        visualizer = new HeapSortVisualizer(vectorTree);

    else if (algorithmName == "removeMax")
        visualizer = new RemoveMaxVisualizer(vectorTree);

    else if (algorithmName == "insertNode")
        visualizer = new AddNodeVisualizer(vectorTree, newNodeKey);

    return configureModel(new VisualizerModel(tree, visualizer));
}

QObject *ModelManager::createSettingsPageModel()
{
    return configureModel(new SettingsModel(g_settingsManager));
}

QObject* ModelManager::configureModel(QObject* object)
{
    QQmlEngine::setObjectOwnership(object, QQmlEngine::JavaScriptOwnership);
    return object;
}
