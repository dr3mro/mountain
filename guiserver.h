#ifndef GUISERVER_H
#define GUISERVER_H

#include <QObject>
#include "trayicon.h"
#include "menu.h"
#include "kernel.h"

class GuiServer : public QObject
{
    Q_OBJECT
public:
    explicit GuiServer(Kernel &kernel);
    ~GuiServer();

signals:

public slots:
    void launchSettings();
private:
    TrayIcon *trayIcon;
    Menu *trayMenu;
};



#endif // GUISERVER_H
