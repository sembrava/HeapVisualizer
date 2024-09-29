#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "view/modelmanager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    ModelManager modelManager;
    engine.rootContext()->setContextProperty("modelManager", &modelManager);

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
