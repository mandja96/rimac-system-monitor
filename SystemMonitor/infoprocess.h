#ifndef INFOPROCESS_H
#define INFOPROCESS_H

#include <QObject>
#include <QThread>
#include <QProcess>

/*
 * This InfoProcess class is used for fetching system data
 * about active processes. Number of processes is fetched.
*/

class InfoProcess : public QThread
{
    Q_OBJECT
    Q_PROPERTY(quint64 numberOfProcesses READ numberOfProcesses WRITE setNumberOfProcesses NOTIFY numberOfProcessesChanged)

public:
    InfoProcess();
    ~InfoProcess();

    quint64 numberOfProcesses();

signals:
    void numberOfProcessesChanged();

public slots:
    // functions declared here can be called from QML

private:
    quint64 _numbertOfProcesses;
    QProcess* _processFetchNumberOfProcesses;
    quint16 _processDuration;

private slots:
    void setNumberOfProcesses(quint64);

protected:
    void run();
};

#endif // INFOPROCESS_H
