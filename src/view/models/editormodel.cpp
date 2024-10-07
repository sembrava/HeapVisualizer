#include "editormodel.h"

EditorModel::EditorModel(QVariantList& tree, FileManager* fileManager, QObject *parent)
    : m_tree(tree)
    , m_fileManager(fileManager)
    , QObject(parent)
{}

void EditorModel::addNode()
{
    m_tree.append(QVariant::fromValue(QStringLiteral("")));

    emit treeChanged();
}

void EditorModel::removeNode()
{
    if (m_tree.empty())
        return;

    m_tree.removeLast();

    emit treeChanged();
}

void EditorModel::setNodeKey(int index, int newKey)
{
    if (index >= m_tree.size() || index < 0)
        return;

    if (newKey == m_tree[index])
        return;

    m_tree[index] = newKey;

    emit treeChanged();
}
