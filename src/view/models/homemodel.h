#ifndef HOMEMODEL_H
#define HOMEMODEL_H

#include <QObject>
#include "completebinarytree.h"
#include "../../persistence/filemanager.h"

class HomeModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QList<CompleteBinaryTree*> savedVisualizations READ getSavedVisualizations NOTIFY savedVisualizationsChanged)

public:
    explicit HomeModel(FileManager* fileManager, QObject* parent = nullptr);

    virtual ~HomeModel();

    QList<CompleteBinaryTree*> getSavedVisualizations() const { return m_savedVisualizations; }

    Q_INVOKABLE void openVisualization(int index) const;

    Q_INVOKABLE void deleteVisualization(int index);

signals:
    void savedVisualizationsChanged();

private:
    FileManager* m_fileManager;
    QList<CompleteBinaryTree*> m_savedVisualizations;
};

#endif // HOMEMODEL_H
