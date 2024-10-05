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

QObject* ModelManager::createVisualizerPageModel(QVariantList tree)
{
    std::vector<int> vectorTree;

    for (const QVariant& node : tree)
        vectorTree.push_back(qvariant_cast<int>(node));

    return configureModel(new VisualizerModel(tree, g_fileManager, new HeapSortVisualizer(vectorTree, true)));
}

QObject* ModelManager::configureModel(QObject* object)
{
    QQmlEngine::setObjectOwnership(object, QQmlEngine::JavaScriptOwnership);
    return object;
}
