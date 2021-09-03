#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QProcess>

#include <iostream>

#include "infothread.h"
#include "infoprocess.h"
#include "infomemory.h"
#include "infodisk.h"
#include "infocpu.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);
    app.setApplicationName("System Monitor");

    InfoThread threadInfo;
    threadInfo.start();

    InfoProcess processInfo;
    processInfo.start();

    InfoMemory memoryInfo;
    memoryInfo.start();

    InfoDisk diskInfo;
    diskInfo.start();

    InfoCPU cpuInfo;
    cpuInfo.start();

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

    // Connecting C++ classes to QML side
    rootContext->setContextProperty("threadsInfo", &threadInfo);
    rootContext->setContextProperty("processesInfo", &processInfo);
    rootContext->setContextProperty("memoryInfo", &memoryInfo);
    rootContext->setContextProperty("diskInfo", &diskInfo);
    rootContext->setContextProperty("cpuInfo", &cpuInfo);

    engine.load(url);
    if (engine.rootObjects().isEmpty())
            return -1;

    app.exec();

    // AFTER APP IS CLOSED SHOULD FIX THREADS
    // TODO: Try to do this with signal from QGuiApplication::aboutToQuit()
    //       and slot in thread to quit() and wait() there.


    // NOT THE SMARTEST OPTION, FOR NOW
    threadInfo.terminate();
    threadInfo.wait();

    processInfo.terminate();
    processInfo.wait();

    memoryInfo.terminate();
    memoryInfo.wait();

    diskInfo.terminate();
    diskInfo.wait();

    cpuInfo.terminate();
    cpuInfo.wait();

    return 0;
}
