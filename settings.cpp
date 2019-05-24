#include "settings.h"

mSettings::mSettings(QObject *parent):QSettings(parent)
{

    setDefaultFormat(QSettings::NativeFormat);
    if (!QFile(fileName()).exists())
    {
        setValue(COMMAND,QVariant("/opt/local/bin/sshfs"));
        setValue(DEVICE,QVariant("192.168.1.3"));
        setValue(REMOTEPATH,QVariant("/opt/MyCloud"));
        setValue(OPTIONS,QVariant("password_stdin,volname=MyCloud,uid=501,gid=20,umask=0000,noappledouble,defer_permissions,reconnect,compression=no,Cipher=arcfour,cache=no,ServerAliveInterval=3,ServerAliveCountMax=2"));
        setValue(MOUNTPOINT,QVariant("/mnt/MyCloud"));
        setValue(SSHUSER,QVariant("root"));
        setValue(SSHPASS,QVariant("12345"));
        setValue(SHUTDOWNSCRIPT,QVariant("/opt/bin/PowerOff"));
        setValue(REBOOTSCRIPT,QVariant("/opt/bin/Reboot"));
        setValue(SSHARGS,QVariant("-p 22"));

    }


    options = getOptions();
}

mSettings::Options & mSettings::getOptions()
{
    options.mount_command = value(COMMAND).toString();
    options.device_ip = value(DEVICE).toString();
    options.remote_path = value(REMOTEPATH).toString();
    options.mount_options = value(OPTIONS).toString();
    options.mount_point = value(MOUNTPOINT).toString();
    options.username = value(SSHUSER).toString();
    options.password = value(SSHPASS).toString();
    options.shutdown_script = value(SHUTDOWNSCRIPT).toString();
    options.reboot_script = value(REBOOTSCRIPT).toString();
    options.args = value(SSHARGS).toString();
    return  options;
}
