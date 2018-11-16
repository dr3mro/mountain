#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QSettings>
#include <QFile>
#include <QDebug>

#define COMMAND "mount_command"
#define OPTIONS "mount_options"
#define DEVICE "device_ip"
#define REMOTEPATH "remote_path"
#define MOUNTPOINT "mount_point"
#define SSHUSER "ssh_user_name"
#define SSHPASS "ssh_password"
#define AUTOMOUNT "auto_mount"
#define AUTOUNMOUNT "auto_unmount"
#define REBOOTSCRIPT "reboot_script"
#define SHUTDOWNSCRIPT "shutdown_script"

class mSettings : public QSettings
{
    Q_OBJECT
public:
    struct Options
    {
        QString mount_command;
        QString mount_options;
        QString device_ip;
        QString remote_path;
        QString mount_point;
        QString username;
        QString password;
        QString shutdown_script;
        QString reboot_script;
    };
    Options options;
    mSettings(QObject *parent = Q_NULLPTR);

};

#endif // SETTINGS_H
