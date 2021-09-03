#ifndef INFOTHREAD_H
#define INFOTHREAD_H

#include <QObject>
#include <QThread>
#include <QProcess>

/*
 * This InfoThread class is used for fetching system data
 * about active threads. Number of threads is fetched.
*/

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
    // functions declared here can be called from QML

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
