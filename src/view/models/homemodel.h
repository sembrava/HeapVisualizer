#ifndef HOMEMODEL_H
#define HOMEMODEL_H

#include <QObject>
#include <QVariant>
#include "../../persistence/filemanager.h"

class HomeModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QVariantList savedVisualizations READ getSavedVisualizations NOTIFY savedVisualizationsChanged)

public:
    explicit HomeModel(FileManager* fileManager, QObject* parent = nullptr);

    virtual ~HomeModel();

    QVariantList getSavedVisualizations() const { return m_savedVisualizations; }

    Q_INVOKABLE void openVisualization(int index) const;

    Q_INVOKABLE void deleteVisualization(int index);

    Q_INVOKABLE QVariantList generateRandomArray(int arraySize);

signals:
    void savedVisualizationsChanged();

private:
    FileManager* m_fileManager;
    QVariantList m_savedVisualizations;
};

#endif // HOMEMODEL_H
