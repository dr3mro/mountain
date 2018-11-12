#include "settings.h"

mSettings::mSettings(QObject *parent):QSettings(parent)
{

    setDefaultFormat(QSettings::NativeFormat);
    if (!QFile(fileName()).exists())
    {
        setValue(COMMAND,QVariant("/usr/local/bin/sshfs"));
        setValue(DEVICE,QVariant("192.168.1.3"));
        setValue(REMOTEPATH,QVariant("/opt/MyCloud"));
        setValue(OPTIONS,QVariant("password_stdin,volname=MyCloud,uid=501,gid=20,umask=0000,noappledouble,no_readahead,no_remote_lock"));
        setValue(MOUNTPOINT,QVariant("/Volumes/MyCloud"));
        setValue(SSHUSER,QVariant("root"));
        setValue(SSHPASS,QVariant("12345"));
    }

    options.mount_command = value(COMMAND).toString();
    options.device_ip = value(DEVICE).toString();
    options.remote_path = value(REMOTEPATH).toString();
    options.mount_options = value(OPTIONS).toString();
    options.mount_point = value(MOUNTPOINT).toString();
    options.username = value(SSHUSER).toString();
    options.password = value(SSHPASS).toString();

}
