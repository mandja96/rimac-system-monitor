#include "infomemory.h"

#include <chrono>
#include<iostream>
#include<sstream>

InfoMemory::InfoMemory()
    : _availableMemory(0),
      _usedMemory(0),
      _totalMemory(0)
{

}

InfoMemory::~InfoMemory()
{
    delete _processFetchMemoryInfo;
}

//andja.start("/bin/sh",
//             QStringList() << "-c" << "free -k | head -n 2 | tail -n 1");
void InfoMemory::run()
{
    _processFetchMemoryInfo = new QProcess();

    QString program = "/bin/sh";
    QStringList arguments;
    arguments << "-c"
              << "free -m | head -n 2 | tail -n 1";

    while(true) {
        _processFetchMemoryInfo->start(program, arguments, QIODevice::ReadOnly);
        auto startTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

        _processFetchMemoryInfo->waitForFinished();
        auto exitTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

        QString  numberOfProcessesStr = _processFetchMemoryInfo->readAllStandardOutput();

        _processDuration = static_cast<quint16>(exitTime - startTime);

        std::vector<std::string> available_used_total = extractValuesFromString(numberOfProcessesStr.toStdString());

        QString availableMemory = QString::fromStdString(available_used_total.at(6));
        //QString usedMemory = QString::fromStdString(available_used_total.at(2));
        QString totalMemory = QString::fromStdString(available_used_total.at(1));

        updateMemoryInfo(static_cast<quint64>(availableMemory.toULongLong()),
                         static_cast<quint64>(totalMemory.toULongLong() - availableMemory.toULongLong()),
                         static_cast<quint64>(totalMemory.toULongLong()));

        QThread::sleep(2);
    }

}

quint64 InfoMemory::availableMemory()
{
    return _availableMemory;
}

quint64 InfoMemory::usedMemory()
{
    return _usedMemory;
}

quint64 InfoMemory::totalMemory()
{
    return _totalMemory;
}

void InfoMemory::setAvailableMemory(quint64 newAvailableMemory)
{
    _availableMemory = newAvailableMemory;
}

void InfoMemory::setUsedMemory(quint64 newUsedMemory)
{
    _usedMemory = newUsedMemory;
}

void InfoMemory::setTotalMemory(quint64 newTotalMemory)
{
    _totalMemory = newTotalMemory;
}

void InfoMemory::updateMemoryInfo(quint64 newAvailableMemory,
                                  quint64 newUsedMemory,
                                  quint64 newTotalMemory)
{
    setAvailableMemory(newAvailableMemory);
    setUsedMemory(newUsedMemory);
    setTotalMemory(newTotalMemory);

    emit memoryChanged();
}

std::vector<std::string> InfoMemory::extractValuesFromString(std::string freeCommandOutput)
{
    std::vector<std::string> result;

    std::istringstream iss(freeCommandOutput);
    for(std::string s; iss >> s; )
        result.push_back(s);

    return result;
}
