#ifndef INFODISK_H
#define INFODISK_H

#include <QObject>
#include <QThread>
#include <QProcess>
#include <QVariant>

#include <map>
#include <string>
#include <vector>

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
