#include "editormodel.h"

EditorModel::EditorModel(const QList<int>& tree, FileManager* fileManager, QObject *parent)
    : m_tree(tree)
    , m_fileManager(fileManager)
    , m_selectedNode(-1)
    , QObject(parent)
{}

void EditorModel::addNode()
{
    m_tree.append(1);

    emit treeChanged();
}

void EditorModel::removeNode()
{
    if (m_tree.empty())
        return;

    m_tree.removeLast();

    emit treeChanged();
}

void EditorModel::selectNode(int index)
{
    m_selectedNode = index;
}
