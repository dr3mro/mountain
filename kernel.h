#ifndef KERNEL_H
#define KERNEL_H

#include <QObject>
#include "QDebug"
#include <QSharedMemory>
#include <QMessageBox>
#include <QProcess>
#include <QDesktopServices>
#include <QNetworkConfigurationManager>
#include <QNetworkSession>
#include <QUrl>
#include <QTimer>
#include <QtConcurrent>
#include <QFuture>
#include "settings.h"
#include <memory.h>

class Kernel : public QObject
{
    Q_OBJECT
public:
    explicit Kernel(QObject *parent = nullptr);
    bool isMount();

signals:
    void launchSettings();
    void showMount();
    void showUnmount();
    void isUpFinished();
public slots:
    void Mount();
    bool Unmount(bool silent=false);
    void OpenFinder();
    void Settings();
    void Quit()__attribute__((noreturn));
    void onNetworkStateChanged(QNetworkSession::State state);
    void preBoot();
    void postBoot();
    void Shutdown();
    void Reboot();
    void Shell();
    void checkDevice();
private:
    bool isUp();
    void executeInTerminal(QString command);
    QStringList getCommandArgs();
    mSettings settings;
    QNetworkConfigurationManager manager;
    QNetworkConfiguration cfg;
    std::unique_ptr<QNetworkSession> session;
    QFuture<bool> isUpFuture;
};

#endif // KERNEL_H
