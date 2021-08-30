#include "infoprocess.h"

#include <chrono>
#include <iostream>

InfoProcess::InfoProcess()
    : _numbertOfProcesses(0)
{

}

InfoProcess::~InfoProcess()
{
    delete _processFetchNumberOfProcesses;
}

//andja.start("/bin/sh",
//             QStringList() << "-c" << "ps -e --no-headers | wc -l", QIODevice::ReadOnly");
void InfoProcess::run()
{
    _processFetchNumberOfProcesses = new QProcess();

    QString program = "/bin/sh";
    QStringList arguments;
    arguments << "-c"
              << "ps -e --no-headers | wc -l";

    while(true) {
        _processFetchNumberOfProcesses->start(program, arguments, QIODevice::ReadOnly);
        auto startTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

        _processFetchNumberOfProcesses->waitForFinished();
        auto exitTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

        QString  numberOfProcessesStr = _processFetchNumberOfProcesses->readAllStandardOutput();

        _processDuration = static_cast<quint16>(exitTime - startTime);

        setNumberOfProcesses(numberOfProcessesStr.toLongLong());
        QThread::sleep(1);
    }
}

quint64 InfoProcess::numberOfProcesses()
{
    return _numbertOfProcesses;
}

void InfoProcess::setNumberOfProcesses(quint64 newNumberOfProcesses)
{
    _numbertOfProcesses = newNumberOfProcesses;
    emit numberOfProcessesChanged();
}
