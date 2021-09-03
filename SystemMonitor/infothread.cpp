#include "infothread.h"

#include <chrono>
#include <iostream>

InfoThread::InfoThread()
    : _numberOfThreads(0)
{

}

InfoThread::~InfoThread()
{
    if (_processFetchNumberOfThreads != nullptr)
        delete _processFetchNumberOfThreads;
}

// COMMAND FOR FETCHING THREADS DATA:
//ps -eo nlwp --no-headers
//    | awk '{ num_threads += $1 } END { print num_threads }'
void InfoThread::run(){

    _processFetchNumberOfThreads = new QProcess();

    QString program = "/bin/sh";
    QStringList arguments;
    arguments << "-c"
              << "ps -eo nlwp --no-headers | awk '{ num_threads += $1 } END { print num_threads }'";

    while(true) {
        _processFetchNumberOfThreads->start(program, arguments);
        auto startTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

        _processFetchNumberOfThreads->waitForFinished();
        auto exitTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

        QString  numberOfThreadsStr= _processFetchNumberOfThreads->readAllStandardOutput();

        _processDuration = static_cast<quint16>(exitTime - startTime);

        setNumberOfThreads(numberOfThreadsStr.toLongLong());
        QThread::sleep(1);
    }
}

quint64 InfoThread::numberOfThreads()
{
    return _numberOfThreads;
}

void InfoThread::setNumberOfThreads(quint64 newNumberOfThreads)
{
    _numberOfThreads = newNumberOfThreads;
    emit numberOfThreadsChanged();
}
