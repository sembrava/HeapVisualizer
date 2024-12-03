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
    Q_PROPERTY(int newNodeKey READ getNewNodeKey WRITE setNewNodeKey NOTIFY newNodeKeyChanged);
    Q_PROPERTY(QString language READ getLanguage WRITE setLanguage NOTIFY languageChanged);
    Q_PROPERTY(bool isLightTheme READ getIsLightTheme WRITE setIsLightTheme NOTIFY isLightThemeChanged);

public:
    explicit QmlGlobals(QObject *parent = nullptr);

    QString getCurrentFileName() const;

    QVariantList getCurrentlyEditedTree() const;

    QString getCurrentAlgorithm() const;

    int getNewNodeKey() const;

    QString getLanguage() const;

    bool getIsLightTheme() const;

    void setCurrentFileName(const QString& newName);

    void setCurrentlyEditedTree(QVariantList newTree);

    void setCurrentAlgorithm(const QString& newAlgorithm);

    void setNewNodeKey(int newKey);

    void setLanguage(const QString& newLanguage);

    void setIsLightTheme(bool newValue);

signals:
    void currentFileNameChanged();

    void currentlyEditedTreeChanged();

    void currentAlgorithmChanged();

    void newNodeKeyChanged();

    void languageChanged();

    void isLightThemeChanged();

private:
    QString m_currentFileName;
    QVariantList m_currentlyEditedTree;
    QString m_currentAlgorithm;
    int m_newNodeKey;
    QString m_language;
    bool m_isLightTheme;
};

#endif // QMLGLOBALS_H
