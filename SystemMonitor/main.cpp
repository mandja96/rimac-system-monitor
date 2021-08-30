#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QProcess>

#include <iostream>

#include "infothread.h"
#include "infoprocess.h"
#include "infomemory.h"
#include "infodisk.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    InfoThread threadInfo;
    threadInfo.start();

    InfoProcess processInfo;
    processInfo.start();

    InfoMemory memoryInfo;
    memoryInfo.start();

    InfoDisk diskInfo;
    diskInfo.start();

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));

    QObject::connect(&engine,
                     &QQmlApplicationEngine::objectCreated,
                     &app,
                     [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl) {
            QCoreApplication::exit(-1);
        }
    }, Qt::QueuedConnection);

    QQmlContext *rootContext = engine.rootContext();
    rootContext->setContextProperty("threadsInfo", &threadInfo);
    rootContext->setContextProperty("processesInfo", &processInfo);
    rootContext->setContextProperty("memoryInfo", &memoryInfo);

    engine.load(url);
    if (engine.rootObjects().isEmpty())
            return -1;

    app.exec();

    // AFTER APP IS CLOSED SHOULD FIX THREADS
    // TODO: Try to do this with signal from QGuiApplication::aboutToQuit()
    //       and slot in thread to quit() and wait() there.
    threadInfo.terminate();
    threadInfo.wait();

    processInfo.terminate();
    processInfo.wait();

    memoryInfo.terminate();
    memoryInfo.wait();

    diskInfo.terminate();
    diskInfo.wait();

    return 0;
}
