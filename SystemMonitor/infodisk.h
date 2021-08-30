#ifndef INFODISK_H
#define INFODISK_H

#include <QObject>
#include <QThread>
#include <QProcess>

#include <map>
#include <string>
#include <vector>

class InfoDisk : public QThread
{
    Q_OBJECT
public:
    InfoDisk();
    ~InfoDisk();

    std::vector<std::vector<std::string>> solidDisks();
    std::vector<std::vector<std::string>> floppyDisks();
    std::vector<std::vector<std::string>> otherDisks();

signals:

public slots:

private:
    std::vector<std::vector<std::string>> _solidDisks;
    std::vector<std::vector<std::string>> _floppyDisks;
    std::vector<std::vector<std::string>> _otherDisks;

    QProcess* _processFetchDiskInfo;

    quint16 _processDuration;

    std::vector<std::vector<std::string>> extractValuesFromOutput(std::string);

private slots:
    void setDisks(std::vector<std::vector<std::string>>,
                  std::vector<std::vector<std::string>>,
                  std::vector<std::vector<std::string>>);

protected:
    void run();
};

#endif // INFODISK_H
