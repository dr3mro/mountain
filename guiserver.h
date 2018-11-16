#ifndef GUISERVER_H
#define GUISERVER_H

#include <QObject>
#include <memory.h>
#include "trayicon.h"
#include "menu.h"
#include "kernel.h"

class GuiServer : public QObject
{
    Q_OBJECT
public:
    explicit GuiServer(Kernel &kernel);

signals:

private:
    std::unique_ptr<Menu> trayMenu;
    std::unique_ptr<TrayIcon> trayIcon;
};
#endif // GUISERVER_H
