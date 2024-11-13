#ifndef QMLGLOBALS_H
#define QMLGLOBALS_H

#include <QObject>
#include <QVariant>
#include <QLocale>
#include <QSettings>

class QmlGlobals : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString currentFileName READ getCurrentFileName WRITE setCurrentFileName NOTIFY currentFileNameChanged);
    Q_PROPERTY(QVariantList currentlyEditedTree READ getCurrentlyEditedTree WRITE setCurrentlyEditedTree NOTIFY currentlyEditedTreeChanged);
    Q_PROPERTY(QString currentAlgorithm READ getCurrentAlgorithm WRITE setCurrentAlgorithm NOTIFY currentAlgorithmChanged);
    Q_PROPERTY(bool documentHeapification READ getDocumentHeapification WRITE setDocumentHeapification NOTIFY documentHeapificationChanged);
    Q_PROPERTY(int newNodeKey READ getNewNodeKey WRITE setNewNodeKey NOTIFY newNodeKeyChanged);
    Q_PROPERTY(QString language READ getLanguage WRITE setLanguage NOTIFY languageChanged);
    Q_PROPERTY(bool isLightTheme READ getIsLightTheme WRITE setIsLightTheme NOTIFY isLightThemeChanged);

public:
    explicit QmlGlobals(QObject *parent = nullptr)
        : m_currentFileName("")
        , m_currentlyEditedTree(QVariantList())
        , m_currentAlgorithm("")
        , m_documentHeapification(true)
        , m_newNodeKey(0)
        , m_language(QLocale::system().name() == "hu_HU" ? "hu" : "en")
        , m_isLightTheme(QSettings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", QSettings::NativeFormat).value("AppsUseLightTheme", 1).toInt() != 0)
        , QObject(parent)
    {}

    QString getCurrentFileName() const { return m_currentFileName; }

    QVariantList getCurrentlyEditedTree() const { return m_currentlyEditedTree; }

    QString getCurrentAlgorithm() const { return m_currentAlgorithm; }

    bool getDocumentHeapification() const { return m_documentHeapification; }

    int getNewNodeKey() const { return m_newNodeKey; }

    QString getLanguage() const { return m_language; }

    bool getIsLightTheme() const { return m_isLightTheme; }

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

    void setNewNodeKey(int newKey)
    {
        m_newNodeKey = newKey;
        emit newNodeKeyChanged();
    }

    void setLanguage(const QString& newLanguage)
    {
        m_language = newLanguage;
        emit languageChanged();
    }

    void setIsLightTheme(bool newValue)
    {
        m_isLightTheme = newValue;
        emit isLightThemeChanged();
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

    void newNodeKeyChanged();

    void languageChanged();

    void isLightThemeChanged();

private:
    QString m_currentFileName;
    QVariantList m_currentlyEditedTree;
    QString m_currentAlgorithm;
    bool m_documentHeapification;
    int m_newNodeKey;
    QString m_language;
    bool m_isLightTheme;
};

#endif // QMLGLOBALS_H
