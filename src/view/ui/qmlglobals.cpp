#include "qmlglobals.h"
#include "../../globals.h"

QmlGlobals::QmlGlobals(QObject *parent)
    : m_currentFileName("")
    , m_currentlyEditedTree(QVariantList())
    , m_currentAlgorithm("")
    , m_documentHeapification(true)
    , m_newNodeKey(0)
    , m_language(QString::fromStdString(g_settingsManager->getSettings().getLanguage()))
    , m_isLightTheme(QString::fromStdString(g_settingsManager->getSettings().getTheme()) == "light")
    , QObject(parent)
{}

QString QmlGlobals::getCurrentFileName() const { return m_currentFileName; }

QVariantList QmlGlobals::getCurrentlyEditedTree() const { return m_currentlyEditedTree; }

QString QmlGlobals::getCurrentAlgorithm() const { return m_currentAlgorithm; }

bool QmlGlobals::getDocumentHeapification() const { return m_documentHeapification; }

int QmlGlobals::getNewNodeKey() const { return m_newNodeKey; }

QString QmlGlobals::getLanguage() const { return m_language; }

bool QmlGlobals::getIsLightTheme() const { return m_isLightTheme; }

void QmlGlobals::setCurrentFileName(const QString &newName)
{
    m_currentFileName = newName;
    emit currentFileNameChanged();
}

void QmlGlobals::setCurrentlyEditedTree(QVariantList newTree)
{
    m_currentlyEditedTree = newTree;
    emit currentlyEditedTreeChanged();
}

void QmlGlobals::setCurrentAlgorithm(const QString &newAlgorithm)
{
    m_currentAlgorithm = newAlgorithm;
    emit currentAlgorithmChanged();
}

void QmlGlobals::setDocumentHeapification(bool newValue)
{
    m_documentHeapification = newValue;
    emit documentHeapificationChanged();
}

void QmlGlobals::setNewNodeKey(int newKey)
{
    m_newNodeKey = newKey;
    emit newNodeKeyChanged();
}

void QmlGlobals::setLanguage(const QString &newLanguage)
{
    m_language = newLanguage;
    emit languageChanged();
}

void QmlGlobals::setIsLightTheme(bool newValue)
{
    m_isLightTheme = newValue;
    emit isLightThemeChanged();
}

void QmlGlobals::addNode(int key)
{
    m_currentlyEditedTree.append(key);
}

void QmlGlobals::removeLastNode()
{
    if (m_currentlyEditedTree.size() >= 0)
    {
        m_currentlyEditedTree.pop_back();
    }
}
