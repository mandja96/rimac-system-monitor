#ifndef INFOTHREAD_H
#define INFOTHREAD_H

#include <QObject>
#include <QThread>
#include <QProcess>

class InfoThread : public QThread
{
    Q_OBJECT
    Q_PROPERTY(quint64 numberOfThreads READ numberOfThreads WRITE setNumberOfThreads NOTIFY numberOfThreadsChanged)

public:
    InfoThread();
    ~InfoThread();

    quint64 numberOfThreads();

signals:
    void numberOfThreadsChanged();

public slots:

private:
    quint64 _numberOfThreads;
    QProcess* _processFetchNumberOfThreads;
    quint16 _processDuration;

private slots:
    void setNumberOfThreads(quint64);

protected:
    void run();
};

#endif // INFOTHREAD_H
