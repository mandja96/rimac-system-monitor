#ifndef INFOCPU_H
#define INFOCPU_H

#include <QObject>
#include <QThread>
#include <QProcess>

#include <vector>
#include <string>

class InfoCPU : public QThread
{
    Q_OBJECT
public:
    InfoCPU();
    ~InfoCPU();

    std::vector<std::vector<std::string>> cpus();

signals:
    void cpusChanged();

public slots:

private:
    std::vector<std::vector<std::string>> _cpus;
    std::map<std::string, float> _cpusLoad;

    std::map<std::string, float> _prevTotal;
    std::map<std::string, float> _prevIdle;

    QProcess* _processFetchCpusInfo;

    quint16 _processDuration;

    std::vector<std::vector<std::string>> extractValuesFromOutput(std::string);
    float calculateCpuLoad(std::vector<std::string>);

private slots:
    void setCpus(std::vector<std::vector<std::string>>);

protected:
    void run();
};

#endif // INFOCPU_H
