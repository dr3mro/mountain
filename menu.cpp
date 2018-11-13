#include "menu.h"


Menu::Menu(Kernel &kernel, QWidget *parent):QMenu(parent),_kernel(&kernel)
{
    addAction("Mount",&kernel,SLOT(Mount()));
    addAction("UnMount",&kernel,SLOT(Unmount()));
    addAction("Settings",&kernel,SLOT(Settings()));
    addSeparator();
    subMenu.setTitle("Power");
    subMenu.addAction("Shell",&kernel,SLOT(Shell()));
    subMenu.addAction("Shutdown",&kernel,SLOT(Shutdown()));
    subMenu.addAction("Reboot",&kernel,SLOT(Reboot()));

    addMenu(&subMenu);
    addSeparator();
    addAction("Quit",&kernel,SLOT(Quit()));

    connect(&kernel,SIGNAL(showMount()),this,SLOT(showMountOnly()));
    connect(&kernel,SIGNAL(showUnmount()),this,SLOT(showUnmountOnly()));

    connect(this,SIGNAL(aboutToShow()),&kernel,SLOT(checkDevice()));
    connect(this,SIGNAL(aboutToShow()),this,SLOT(toggleUi()));
    //qApp->installEventFilter(this);
}

void Menu::showMountOnly()
{
    actions().at(0)->setVisible(true);
    actions().at(1)->setVisible(false);
}

void Menu::showUnmountOnly()
{
    actions().at(0)->setVisible(false);
    actions().at(1)->setVisible(true);
}

void Menu::toggleUi()
{
    if(_kernel->isMount())
        showUnmountOnly();
    else
        showMountOnly();

    QProcess process;
    process.start("pmset -g ps");
    process.waitForFinished();
    QString title = QString(process.readAllStandardOutput()).split(" ").at(8);
    subMenu.setTitle( ( (title=="(no") || (title == "attached;") || (title == "0:00") )? "Power":title);

}

//bool Menu::eventFilter(QObject *watched, QEvent *event)
//{
//    qDebug() << event->type() << watched->objectName();

//    return QMenu::eventFilter(watched,event);
//}
