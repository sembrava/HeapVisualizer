#ifndef COMPLETEBINARYTREE_H
#define COMPLETEBINARYTREE_H

#include <QObject>
#include <QVariant>

#include <src/persistence/treefileinfo.h>

class CompleteBinaryTree : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QVariantList tree READ getTree WRITE setTree NOTIFY treeChanged)

public:
    explicit CompleteBinaryTree(const QString& name, const QVariantList& tree)
        : m_name(name)
        , m_tree(tree)
    {}

    QString getName() const { return m_name; }

    void setName(const QString& name)
    {
        if (name == m_name)
            return;

        m_name = name;
        emit nameChanged();
    }

    QVariantList getTree() const { return m_tree; }

    void setTree(const QVariantList& tree)
    {
        m_tree = tree;
    }

    Q_INVOKABLE void addNode(int key)
    {
        m_tree.append(key);
    }

    Q_INVOKABLE void removeLastNode()
    {
        if (m_tree.size() >= 0)
        {
            m_tree.pop_back();
        }
    }

signals:
    void nameChanged();
    void treeChanged();

private:
    QString m_name;
    QVariantList m_tree;
};

Q_DECLARE_METATYPE(CompleteBinaryTree*)

#endif // COMPLETEBINARYTREE_H
