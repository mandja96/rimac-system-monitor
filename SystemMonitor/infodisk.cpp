#include "infodisk.h"

#include <iostream>
#include <sstream>

InfoDisk::InfoDisk()
    : _solidDisks(),
      _floppyDisks(),
      _otherDisks()
{

}

InfoDisk::~InfoDisk()
{
    delete _processFetchDiskInfo;
}

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
}
