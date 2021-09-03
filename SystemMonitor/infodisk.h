#ifndef INFODISK_H
#define INFODISK_H

#include <QObject>
#include <QThread>
#include <QProcess>
#include <QVariant>

#include <map>
#include <string>
#include <vector>

/*
 * This InfoDisk class is used for fetching system data
 * about active disks (only solid drives are exposed to
 * the GUI QML side right now, but also floppy and other disks can be
 * in the future - IF NEEDED) and creating human readable results.
 * Available, used and total disk space is shown.
*/

Q_DECLARE_METATYPE(std::vector<std::vector<std::string>>);

class InfoDisk : public QThread
{
    Q_OBJECT
    Q_PROPERTY(QVariantMap solidDisksVariantMap READ solidDisksVariantMap WRITE setSolidDisksVariantMap NOTIFY diskInfoChanged)
public:
    InfoDisk();
    ~InfoDisk();

    std::vector<std::vector<std::string>> solidDisks();
    std::vector<std::vector<std::string>> floppyDisks();
    std::vector<std::vector<std::string>> otherDisks();

    QVariantMap solidDisksVariantMap();

signals:
    void diskInfoChanged();

public slots:
    // functions declared here can be called from QML

private:
    std::vector<std::vector<std::string>> _solidDisks;
    std::vector<std::vector<std::string>> _floppyDisks;
    std::vector<std::vector<std::string>> _otherDisks;

    QVariantMap _solidDisksVariantMap;
    QProcess* _processFetchDiskInfo;

    quint16 _processDuration;

    std::vector<std::vector<std::string>> extractValuesFromOutput(std::string);

private slots:
    void setDisks(std::vector<std::vector<std::string>>,
                  std::vector<std::vector<std::string>>,
                  std::vector<std::vector<std::string>>);

    void setSolidDisksVariantMap(QVariantMap);
protected:
    void run();
};

#endif // INFODISK_H
