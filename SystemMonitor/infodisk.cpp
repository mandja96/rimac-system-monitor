#include "infodisk.h"

#include <iostream>
#include <sstream>
#include <QVector>

InfoDisk::InfoDisk()
    : _solidDisks(),
      _floppyDisks(),
      _otherDisks(),
      _solidDisksVariantMap()
{

}

InfoDisk::~InfoDisk()
{
    if (_processFetchDiskInfo != nullptr)
        delete _processFetchDiskInfo;
}

QVariantMap InfoDisk::solidDisksVariantMap()
{
    return _solidDisksVariantMap;
}

// COMMANDS FOR FETCHING DISK DATA:

// solid drives:
// df -h --output=source,size,avail,used | egrep '/dev/sd'

// floppy drives:
// df -h --output=source,size,avail,used | egrep '/dev/fd'

// other drives:
// df -h --output=source,size,avail,used | egrep -v '/dev/(sd.|fd.)'
void InfoDisk::run()
{
    _processFetchDiskInfo = new QProcess();

    QString program = "/bin/sh";
    QStringList arguments;

    while(true) {

        arguments.clear();
        arguments << "-c"
                  << "df -h --output=source,size,avail,used | egrep '/dev/sd'";

        _processFetchDiskInfo->start(program, arguments, QIODevice::ReadOnly);
        _processFetchDiskInfo->waitForFinished();

        QString  diskInfoOutputStr = _processFetchDiskInfo->readAllStandardOutput();
        std::vector<std::vector<std::string>> solid =
                extractValuesFromOutput(diskInfoOutputStr.toStdString());

        arguments.clear();
        arguments << "-c"
                  << "df -h --output=source,size,avail,used | egrep '/dev/fd'";

        _processFetchDiskInfo->start(program, arguments, QIODevice::ReadOnly);
        _processFetchDiskInfo->waitForFinished();

        diskInfoOutputStr = _processFetchDiskInfo->readAllStandardOutput();
        std::vector<std::vector<std::string>> floppy =
                extractValuesFromOutput(diskInfoOutputStr.toStdString());

        arguments.clear();
        arguments << "-c"
                  << "df -h --output=source,size,avail,used | egrep -v '/dev/(sd.|fd.)'";

        _processFetchDiskInfo->start(program, arguments, QIODevice::ReadOnly);
        _processFetchDiskInfo->waitForFinished();

        diskInfoOutputStr = _processFetchDiskInfo->readAllStandardOutput();
        std::vector<std::vector<std::string>> others =
                extractValuesFromOutput(diskInfoOutputStr.toStdString());

        setDisks(solid, floppy, others);
        QThread::sleep(1);
    }
}

std::vector<std::vector<std::string>> InfoDisk::extractValuesFromOutput(std::string diskInfo)
{
    std::vector<std::vector<std::string>> result;

    std::string line;
    std::istringstream issAll(diskInfo);
    std::vector<std::string> disk;

    while (std::getline(issAll, line)) {
        disk.clear();
        std::istringstream issOne(line);

        for(std::string s; issOne >> s; )
            disk.push_back(s);

        result.push_back(disk);
    }

    return result;
}

void InfoDisk::setDisks(std::vector<std::vector<std::string>> newSolidDisks,
                        std::vector<std::vector<std::string>> newFloppyDisks,
                        std::vector<std::vector<std::string>> newOtherDisks)
{
    for (auto vec: _solidDisks)
        vec.clear();
    _solidDisks.clear();

    for (auto vec: _floppyDisks)
        vec.clear();
    _floppyDisks.clear();

    for (auto vec: _otherDisks)
        vec.clear();
    _otherDisks.clear();

    _solidDisks = newSolidDisks;
    _floppyDisks = newFloppyDisks;
    _otherDisks = newOtherDisks;

    _solidDisksVariantMap.clear();
    for (auto sd: _solidDisks) {
        QString key = QString::fromStdString(sd.at(0));
        QVector<QString> values;

        sd.erase(sd.begin());
        for (const auto &vec: sd) {
            values.append(QString::fromStdString(vec));
        }
        _solidDisksVariantMap[key] = QVariant::fromValue(values);
    }

    emit diskInfoChanged();
}

void InfoDisk::setSolidDisksVariantMap(QVariantMap newSolidDiskVariantMap)
{
    _solidDisksVariantMap = newSolidDiskVariantMap;
}
