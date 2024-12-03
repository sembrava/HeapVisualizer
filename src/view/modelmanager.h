#ifndef MODELMANAGER_H
#define MODELMANAGER_H

#include <QObject>
#include <QVariant>

#include <src/model/visualizers/heapalgorithmvisualizer.h>

class ModelManager : public QObject
{
    Q_OBJECT

public:
    explicit ModelManager(QObject *parent = nullptr);

    Q_INVOKABLE QObject* createHomePageModel();

    Q_INVOKABLE QObject* createEditorPageModel(QVariantList tree);

    Q_INVOKABLE QObject* createVisualizerPageModel(QVariantList tree, const QString& algorithmName, const int newNodeKey);

    Q_INVOKABLE QObject* createSettingsPageModel();

private:
    QObject* configureModel(QObject* object);
};

#endif // MODELMANAGER_H
