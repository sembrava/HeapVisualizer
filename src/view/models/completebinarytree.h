#ifndef COMPLETEBINARYTREE_H
#define COMPLETEBINARYTREE_H

#include <QObject>

#include <src/persistence/treefileinfo.h>

class CompleteBinaryTree : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ getName CONSTANT)
    Q_PROPERTY(QList<int> tree READ getTree CONSTANT)

public:
    explicit CompleteBinaryTree(const QString& name, const QList<int>& tree)
        : m_name(name)
        , m_tree(tree)
    {}

    QString getName() const { return m_name; }

    QList<int> getTree() const { return m_tree; }

private:
    QString m_name;
    QList<int> m_tree;
};

#endif // COMPLETEBINARYTREE_H
