#ifndef INFOCPU_H
#define INFOCPU_H

#include <QObject>
#include <QThread>
#include <QMap>
#include <QProcess>
#include <QFloat16>
#include <QVariant>

#include <vector>
#include <string>

/*
 * This InfoCPU class is used for fetching system data
 * about active processors (CPU) and creating human
 * readable results through percentage.
*/
class InfoCPU : public QThread
{
    Q_OBJECT
    Q_PROPERTY(QVariantMap cpuMap READ cpuMap WRITE setCpuMap NOTIFY cpusChanged)

public:
    InfoCPU();
    ~InfoCPU();

    std::vector<std::vector<std::string>> cpus();
    std::map<std::string, float> cpusLoad();
    QVariantMap cpuMap();

signals:
    void cpusChanged();

public slots:
    // functions declared here can be called from QML

private:
    std::vector<std::vector<std::string>> _cpus;
    std::map<std::string, float> _cpusLoad;

    std::map<std::string, float> _prevTotal;
    std::map<std::string, float> _prevIdle;

    // NOTE: Workaround for wrapping std::vector<std::vector<std::string>>
    // into something that QML can read and extract!
    QMap<QString, QString> _cpusLoadQt;
    QVariantMap _cpuMap;

    QProcess* _processFetchCpusInfo;
    quint16 _processDuration;

    std::vector<std::vector<std::string>> extractValuesFromOutput(std::string);
    float calculateCpuLoad(std::vector<std::string>);
    void fillCpusLoadQt();

    std::string roundFloatStr(float);

private slots:
    void setCpus(std::vector<std::vector<std::string>>);
    void setCpuMap(QVariantMap);

protected:
    void run();
};

#endif // INFOCPU_H
