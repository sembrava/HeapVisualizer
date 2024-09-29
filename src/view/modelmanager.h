#ifndef MODELMANAGER_H
#define MODELMANAGER_H

#include <QObject>

class ModelManager : public QObject
{
    Q_OBJECT

public:
    explicit ModelManager(QObject *parent = nullptr);

    Q_INVOKABLE QObject* createHomePageModel();

    Q_INVOKABLE QObject* createEditorPageModel();

    Q_INVOKABLE QObject* createVisualizerPageModel();

private:
    QObject* configureModel(QObject* object);
};

#endif // MODELMANAGER_H
