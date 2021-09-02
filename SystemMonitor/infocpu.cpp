#include "infocpu.h"

#include <chrono>
#include <iostream>
#include <sstream>

#include <QDebug>

InfoCPU::InfoCPU()
    : _cpus(),
      _cpusLoad(),
      _prevTotal(),
      _prevIdle()
{

}

InfoCPU::~InfoCPU()
{
    if (_processFetchCpusInfo != nullptr)
        delete _processFetchCpusInfo;
}

std::vector<std::vector<std::string> > InfoCPU::cpus()
{
    return _cpus;
}

std::map<std::string, float> InfoCPU::cpusLoad()
{
    return _cpusLoad;
}

QVariantMap InfoCPU::cpuMap()
{
    return _cpuMap;
}

// fetch cpu info:
// cat /proc/stat  | grep 'cpu'
void InfoCPU::run()
{
    _processFetchCpusInfo = new QProcess();

    QString program = "/bin/sh";
    QStringList arguments;
    arguments << "-c"
              << "cat /proc/stat  | grep 'cpu'";

    while(true) {
        _processFetchCpusInfo->start(program, arguments, QIODevice::ReadOnly);
        auto startTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

        _processFetchCpusInfo->waitForFinished();
        auto exitTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

        QString cpusInfoStr = _processFetchCpusInfo->readAllStandardOutput();

        _processDuration = static_cast<quint16>(exitTime - startTime);

        std::vector<std::vector<std::string>> cpus =
                extractValuesFromOutput(cpusInfoStr.toStdString());

        setCpus(cpus);
        _cpusLoad.clear();

        for (std::vector<std::string> cpu : _cpus) {
            float cpuLoad = calculateCpuLoad(cpu);

            _cpusLoad.insert({cpu.at(0), cpuLoad});
        }

        fillCpusLoadQt();

//        std::cout << std::endl;
//        for (const auto &b: _cpusLoadQt.keys())
//           qDebug() << b << ", " << _cpusLoadQt[b];

        QThread::sleep(1);
    }
}

std::vector<std::vector<std::string> > InfoCPU::extractValuesFromOutput(std::string cpuInfo)
{
    std::vector<std::vector<std::string>> result;

    std::string line;
    std::istringstream issAll(cpuInfo);
    std::vector<std::string> cpu;

    while (std::getline(issAll, line)) {
        cpu.clear();
        std::istringstream issOne(line);

        for(std::string s; issOne >> s; )
            cpu.push_back(s);

        result.push_back(cpu);
    }

    return result;
}

void InfoCPU::setCpus(std::vector<std::vector<std::string>> newCpus)
{
    for (auto cpu: _cpus)
        cpu.clear();
    _cpus.clear();

    _cpus = newCpus;
}

void InfoCPU::setCpuMap(QVariantMap newCpuMap)
{
    for (auto cpu: qAsConst(_cpuMap))
        cpu.clear();
    _cpuMap.clear();

    _cpuMap = newCpuMap;
}

float InfoCPU::calculateCpuLoad(std::vector<std::string> cpu)
{
    float cpuLoad = 0.0;
    std::string key;

    // erase CPU name such as: cpu, cpu1, cpu2, cpu3...
    if (cpu.at(0).substr(0, 3) == "cpu"){
        key = cpu.at(0);
        cpu.erase(cpu.begin());
    }
    else
        qDebug() << "Treba da pocne sa imenom procesora: cpu[1-9]*!";

    quint64 totalTime = 0;
    quint64 idleTime = std::stoull(cpu.at(3));

    for (const std::string &value: cpu) {
        totalTime += std::stoull(value);
    }

    if (totalTime != 0) {

        // NB: must check if it is not the first time and we have the previous values
        if (( _prevIdle.find(key) != _prevIdle.end() ) & ( _prevTotal.find(key) != _prevTotal.end())) {
            cpuLoad = ( 1.0 - ( (idleTime - _prevIdle.find(key)->second)
                                / (totalTime * 1.0 - _prevTotal.find(key)->second) ) ) * 100.0;

            _prevIdle.find(key)->second = idleTime;
            _prevTotal.find(key)->second = totalTime;
        }
        else {
            cpuLoad = ( 1.0 - (idleTime / (totalTime * 1.0)) ) * 100.0;
            _prevIdle.insert({key, idleTime});
            _prevTotal.insert({key, totalTime});
        }
    }

    return cpuLoad;
}

void InfoCPU::fillCpusLoadQt()
{
    _cpusLoadQt.clear();

    for (const auto &element: _cpusLoad) {
        QString key = QString::fromStdString(element.first);
        QString value = QString::fromStdString(roundFloatStr(element.second));

        _cpusLoadQt.insert(key, value);
    }

    foreach (QString key, _cpusLoadQt.keys()) {
        _cpuMap[key] = QVariant::fromValue(_cpusLoadQt[key]);
    }

    emit cpusChanged();
}

std::string InfoCPU::roundFloatStr(float var)
{
    std::ostringstream out;
    out.precision(2);
    out << std::fixed << var;
    return out.str();
}
