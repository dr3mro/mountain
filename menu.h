#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QMenu>
//#include <QEvent>
//#include <QKeyEvent>
#include "kernel.h"

class Menu : public QMenu
{
    Q_OBJECT
public:
    explicit Menu(Kernel & kernel, QWidget * parent=nullptr);

private slots:
    void showMountOnly();
    void showUnmountOnly();
    void toggleUi();

private:
    Kernel * _kernel;
    QMenu subMenu;
protected:
    //bool eventFilter(QObject *watched, QEvent *event);
};

#endif // MENU_H
