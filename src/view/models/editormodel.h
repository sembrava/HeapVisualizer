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

    Q_INVOKABLE void selectNode(int index);

signals:
    void treeChanged();

    void selectedNodeChanged();

private:
    QVariantList m_tree;
    FileManager* m_fileManager;
    int m_selectedNode;
};

#endif // EDITORMODEL_H
