#ifndef QMLGLOBALS_H
#define QMLGLOBALS_H

#include <QObject>
#include <QVariant>

class QmlGlobals : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString currentFileName READ getCurrentFileName WRITE setCurrentFileName NOTIFY currentFileNameChanged);
    Q_PROPERTY(QVariantList currentlyEditedTree READ getCurrentlyEditedTree WRITE setCurrentlyEditedTree NOTIFY currentlyEditedTreeChanged);
    Q_PROPERTY(QString currentAlgorithm READ getCurrentAlgorithm WRITE setCurrentAlgorithm NOTIFY currentAlgorithmChanged);
    Q_PROPERTY(bool documentHeapification READ getDocumentHeapification WRITE setDocumentHeapification NOTIFY documentHeapificationChanged);

public:
    explicit QmlGlobals(QObject *parent = nullptr)
        : m_currentFileName("")
        , m_currentlyEditedTree(QVariantList())
        , m_currentAlgorithm("")
        , m_documentHeapification(true)
        , QObject(parent)
    {}

    QString getCurrentFileName() const { return m_currentFileName; }

    QVariantList getCurrentlyEditedTree() const { return m_currentlyEditedTree; }

    QString getCurrentAlgorithm() const { return m_currentAlgorithm; }

    bool getDocumentHeapification() const { return m_documentHeapification; }

    void setCurrentFileName(const QString& newName)
    {
        m_currentFileName = newName;
        emit currentFileNameChanged();
    }

    void setCurrentlyEditedTree(QVariantList newTree)
    {
        m_currentlyEditedTree = newTree;
        emit currentlyEditedTreeChanged();
    }

    void setCurrentAlgorithm(const QString& newAlgorithm)
    {
        m_currentAlgorithm = newAlgorithm;
        emit currentAlgorithmChanged();
    }

    void setDocumentHeapification(bool newValue)
    {
        m_documentHeapification = newValue;
        emit documentHeapificationChanged();
    }

    Q_INVOKABLE void addNode(int key)
    {
        m_currentlyEditedTree.append(key);
    }

    Q_INVOKABLE void removeLastNode()
    {
        if (m_currentlyEditedTree.size() >= 0)
        {
            m_currentlyEditedTree.pop_back();
        }
    }

signals:
    void currentFileNameChanged();

    void currentlyEditedTreeChanged();

    void currentAlgorithmChanged();

    void documentHeapificationChanged();

private:
    QString m_currentFileName;
    QVariantList m_currentlyEditedTree;
    QString m_currentAlgorithm;
    bool m_documentHeapification;
};

#endif // QMLGLOBALS_H
