#include <QQmlEngine>

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

QObject* ModelManager::createEditorPageModel()
{
    return configureModel(new EditorModel(QList<int>{ 65, 13, 45, 3, 56, 234, 624, 23, 53, 64, 524, 623, 632, 1234, 523 }, g_fileManager));
}

QObject* ModelManager::createVisualizerPageModel()
{
    return configureModel(new VisualizerModel());
}

QObject* ModelManager::configureModel(QObject* object)
{
    QQmlEngine::setObjectOwnership(object, QQmlEngine::JavaScriptOwnership);
    return object;
}
