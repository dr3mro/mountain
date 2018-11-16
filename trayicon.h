#ifndef TRAYICON_H
#define TRAYICON_H

#include <QObject>
#include <QSystemTrayIcon>
#include "menu.h"

class TrayIcon : public QSystemTrayIcon
{
public:
    explicit TrayIcon(Menu *menu, QWidget *parent=nullptr);

};

#endif // TRAYICON_H
