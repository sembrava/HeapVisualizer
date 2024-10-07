#include <QQmlEngine>
#include <vector>
#include <QVariant>

#include "src/model/visualizers/heapsortvisualizer.h"
#include "modelmanager.h"
#include "models/homemodel.h"
#include "models/editormodel.h"
#include "models/visualizermodel.h"
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
    return configureModel(new EditorModel(tree, g_fileManager));
}

QObject* ModelManager::createVisualizerPageModel(QVariantList tree, const QString& algorithmName)
{
    std::vector<int> vectorTree;

    for (const QVariant& node : tree)
    {
        vectorTree.push_back(qvariant_cast<int>(node));
    }

    HeapAlgorithmVisualizer* visualizer = nullptr;

    if (algorithmName == "heapSort")
        visualizer = new HeapSortVisualizer(vectorTree, true);

    return configureModel(new VisualizerModel(tree, g_fileManager, visualizer));
}

QObject* ModelManager::configureModel(QObject* object)
{
    QQmlEngine::setObjectOwnership(object, QQmlEngine::JavaScriptOwnership);
    return object;
}
