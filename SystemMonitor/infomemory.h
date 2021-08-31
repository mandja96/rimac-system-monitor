#ifndef INFOMEMORY_H
#define INFOMEMORY_H

#include <QObject>
#include <QThread>
#include <QProcess>

#include <vector>
#include <string>

class InfoMemory : public QThread
{
    Q_OBJECT
    Q_PROPERTY(quint64 availableMemory READ availableMemory WRITE setAvailableMemory NOTIFY memoryChanged)
    Q_PROPERTY(quint64 usedMemory READ usedMemory WRITE setUsedMemory NOTIFY memoryChanged)
    Q_PROPERTY(quint64 totalMemory READ totalMemory WRITE setTotalMemory NOTIFY memoryChanged)
    Q_PROPERTY(quint64 cacheMemory READ cacheMemory WRITE setCacheMemory NOTIFY memoryChanged)

public:
    InfoMemory();
    ~InfoMemory();

    quint64 availableMemory();
    quint64 usedMemory();
    quint64 totalMemory();
    quint64 cacheMemory();

    void setAvailableMemory(quint64);
    void setUsedMemory(quint64);
    void setTotalMemory(quint64);
    void setCacheMemory(quint64);

signals:
    void memoryChanged();

public slots:

private:
    quint64 _availableMemory;
    quint64 _usedMemory;
    quint64 _totalMemory;
    quint64 _cacheMemory;

    QProcess* _processFetchMemoryInfo;
    quint16 _processDuration;

    std::vector<std::string> extractValuesFromString(std::string);

private slots:
    void updateMemoryInfo(quint64, quint64, quint64, quint64);

protected:
    void run();
};

#endif // INFOMEMORY_H
