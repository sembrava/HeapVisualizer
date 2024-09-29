#ifndef EDITORMODEL_H
#define EDITORMODEL_H

#include <QObject>

#include "../../persistence/filemanager.h"

class EditorModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QList<int> tree READ getTree NOTIFY treeChanged)

public:
    explicit EditorModel(const QList<int>& tree, FileManager* fileManager, QObject *parent = nullptr);

    QList<int> getTree() const { return m_tree; }

    Q_INVOKABLE void addNode();

    Q_INVOKABLE void removeNode();

    Q_INVOKABLE void selectNode(int index);

signals:
    void treeChanged();

    void selectedNodeChanged();

private:
    QList<int> m_tree;
    FileManager* m_fileManager;
    int m_selectedNode;
};

#endif // EDITORMODEL_H
