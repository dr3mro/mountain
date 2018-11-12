#include "trayicon.h"

TrayIcon::TrayIcon(Menu * menu, QWidget *parent):QSystemTrayIcon(parent)
{
    QIcon icon = QIcon(":/cloud.png");
    icon.setIsMask(true);
    setIcon(icon);
    setVisible(true);
    setContextMenu(menu);
}
