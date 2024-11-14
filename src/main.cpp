#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>

#include "src/view/models/completebinarytree.h"
#include "view/modelmanager.h"
#include "globals.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQuickStyle::setStyle("Material");

    QQmlApplicationEngine engine;

    qRegisterMetaType<CompleteBinaryTree*>("CompleteBinaryTree");

    ModelManager modelManager;
    engine.rootContext()->setContextProperty("modelManager", &modelManager);

    CompleteBinaryTree currentlyEditedTree("", QVariantList());
    engine.rootContext()->setContextProperty("currentlyEditedTree", &currentlyEditedTree);

    engine.rootContext()->setContextProperty("globals", &g_qmlGlobals);

    const QUrl url(QStringLiteral("qrc:/HeapVisualizer/src/view/ui/Main.qml"));

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
