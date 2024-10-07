#ifndef EDITORMODEL_H
#define EDITORMODEL_H

#include <QObject>
#include <QVariant>

#include "../../persistence/filemanager.h"

class EditorModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QVariantList tree READ getTree NOTIFY treeChanged)

public:
    explicit EditorModel(QVariantList& tree, FileManager* fileManager, QObject *parent = nullptr);

    QVariantList getTree() const { return m_tree; }

    Q_INVOKABLE void addNode();

    Q_INVOKABLE void removeNode();

    Q_INVOKABLE void setNodeKey(int index, int newKey);

signals:
    void treeChanged();

private:
    QVariantList m_tree;
    FileManager* m_fileManager;
};

#endif // EDITORMODEL_H
