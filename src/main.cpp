#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "src/view/models/completebinarytree.h"
#include "view/modelmanager.h"
#include "view/ui/qmlglobals.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qRegisterMetaType<CompleteBinaryTree*>("CompleteBinaryTree");

    ModelManager modelManager;
    engine.rootContext()->setContextProperty("modelManager", &modelManager);

    CompleteBinaryTree currentlyEditedTree("", QVariantList());
    engine.rootContext()->setContextProperty("currentlyEditedTree", &currentlyEditedTree);

    QmlGlobals globals;
    engine.rootContext()->setContextProperty("globals", &globals);

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
