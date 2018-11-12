#include "kernel.h"

Kernel::Kernel(QObject *parent) : QObject(parent)
{
    QSharedMemory sharedMemory;
    sharedMemory.setKey("com.dr3mro.mountain");

    if (!sharedMemory.create(512))
    {
        exit(1);
    }

    QTimer::singleShot(2000,this,SLOT(preBoot()));

    cfg = manager.defaultConfiguration();
    session = new QNetworkSession(cfg);
    connect(session, SIGNAL(stateChanged(QNetworkSession::State)), this, SLOT(onNetworkStateChanged(QNetworkSession::State)));
    session->open();
    session->waitForOpened(100);

}

Kernel::~Kernel()
{
    delete session;
}

void Kernel::Mount()
{
    if(!isUp())
        return;

    QProcess process1;
    QProcess process2;

    process1.setStandardOutputProcess(&process2);

    process1.start("bash",QStringList() << "-c" << QString("echo %1").arg(settings.options.password));

    process1.waitForFinished();

    process2.start(settings.options.mount_command,getCommandArgs());

    process2.waitForFinished();

    if(isMount())
        emit showUnmount();
    else
        emit showMount();


}

void Kernel::Unmount()
{
    int exitCode = QProcess::execute("umount", QStringList() << settings.options.mount_point);
    if (0 == exitCode || !isMount())
        emit showMount();
    else
        emit showUnmount();
}

void Kernel::Settings()
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(settings.fileName()));
    qDebug() << settings.fileName();
}

void Kernel::Quit()
{
    exit(0);
}

void Kernel::onNetworkStateChanged(QNetworkSession::State state)
{
    qDebug() << state;
    if(isMount())
        Unmount();
    else if(state == QNetworkSession::State::Connected)
        Mount();
}

void Kernel::postBoot()
{
    disconnect(this,SIGNAL(isUpFinished()),this,SLOT(postBoot()));

    if(isUpFuture.result())
        Mount();
}

void Kernel::Shutdown()
{
    executeInTerminal(QString("sshpass -p %1 ssh %2@%3 /opt/bin/PowerOff")
                      .arg(settings.options.password)
                      .arg(settings.options.username)
                      .arg(settings.options.device_ip));
}

void Kernel::Reboot()
{
    executeInTerminal(QString("sshpass -p %1 ssh %2@%3 /opt/bin/Reboot")
                      .arg(settings.options.password)
                      .arg(settings.options.username)
                      .arg(settings.options.device_ip));
}

void Kernel::Shell()
{
    executeInTerminal(QString("sshpass -p %1 ssh %2@%3")
                      .arg(settings.options.password)
                      .arg(settings.options.username)
                      .arg(settings.options.device_ip));
}

void Kernel::checkDevice()
{
    if(isMount() && !isUp())
        Unmount();
}

bool Kernel::isMount()
{
    QProcess process1;
    QProcess process2;

    process1.setStandardOutputProcess(&process2);

    process1.start("bash",QStringList() << "-c" << QString("mount"));

    process1.waitForFinished();

    process2.start(QString("grep %1").arg(settings.options.mount_point));

    process2.waitForFinished();

    if(process2.readAllStandardOutput().length() != 0)
        return true;
    else
        return false;
}

void Kernel::preBoot()
{
    if(isMount())
        return;
    connect(this,SIGNAL(isUpFinished()),this,SLOT(postBoot()));
    isUpFuture = QtConcurrent::run(this,&Kernel::isUp);
}

bool Kernel::isUp()
{
    bool state;
    int exitCode = QProcess::execute("ping", QStringList() << "-W" << "100" << "-c1" << "192.168.1.3");
    if (0 == exitCode)
        state = true;
    else
        state = false;
    emit isUpFinished();
    return state;
}

void Kernel::executeInTerminal(QString command)
{
    QString aScript=QString(
    "if application \"Terminal\" is running then\n"
    "    tell application \"Terminal\"\n"
    "        (do script \"%1\") activate\n"
    "    end tell\n"
    "else\n"
    "    tell application \"Terminal\"\n"
    "        (do script \"%1\" in window 1) activate\n"
    "    end tell\n"
    "end if\n").arg(command);


    QStringList args = QStringList()
            << "-e"
            << aScript;

    QProcess p;
    p.start("osascript", args);
    p.waitForBytesWritten();
    p.waitForFinished();
}

QStringList Kernel::getCommandArgs()
{

    return QStringList() << QString("%1@%2:%3")
                            .arg(settings.options.username)
                            .arg(settings.options.device_ip)
                            .arg(settings.options.remote_path)
                         << settings.options.mount_point
                         << QString("-o%1")
                            .arg(settings.options.mount_options);

}
