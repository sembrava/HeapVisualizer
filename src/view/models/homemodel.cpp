#include "homemodel.h"

#include <QVariant>
#include "completebinarytree.h"

HomeModel::HomeModel(FileManager* fileManager, QObject* parent)
    : m_fileManager(fileManager)
    , QObject(parent)
{
    std::vector<TreeFileInfo> source = m_fileManager->loadAll();

    m_savedVisualizations = QVariantList();

    for (const auto& treeFileInfo : source)
    {
        const std::vector<int>& tree = treeFileInfo.getTree();

        m_savedVisualizations.append(QVariant::fromValue(new CompleteBinaryTree(QString::fromStdString(treeFileInfo.getName()), QVariantList(tree.begin(), tree.end()))));
    }
}

HomeModel::~HomeModel()
{
    for (const auto& tree : m_savedVisualizations)
        delete qvariant_cast<CompleteBinaryTree*>(tree);
}

void HomeModel::openVisualization(int index) const
{
    return;
}

void HomeModel::deleteVisualization(int index)
{
    if (index >= m_savedVisualizations.size() || index < 0)
        return;

    const QString& name = qvariant_cast<CompleteBinaryTree*>(m_savedVisualizations[index])->getName();

    m_savedVisualizations.removeAt(index);

    m_fileManager->remove(name.toStdString());

    emit savedVisualizationsChanged();
}
