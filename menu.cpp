#include "menu.h"


Menu::Menu(Kernel &kernel, QWidget *parent):QMenu(parent),_kernel(&kernel)
{
    addAction("Mount",&kernel,SLOT(Mount()));
    addAction("Open in Finder",&kernel,SLOT(OpenFinder()));
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

    connect(&kernel,&Kernel::showMount,this,&Menu::showMountOnly);
    connect(&kernel,&Kernel::showUnmount,this,&Menu::showUnmountOnly);

    connect(this,&Menu::aboutToShow,&kernel,&Kernel::checkDevice);
    connect(this,&Menu::aboutToShow,this,&Menu::toggleUi);
}

void Menu::showMountOnly()
{
    actions().at(0)->setVisible(true);
    actions().at(1)->setVisible(false);
    actions().at(2)->setVisible(false);
}

void Menu::showUnmountOnly()
{
    actions().at(0)->setVisible(false);
    actions().at(1)->setVisible(true);
    actions().at(2)->setVisible(true);
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
    subMenu.setTitle( ( (title=="(no") || (title == "attached;") || (title == "charge;") || (title == "0:00") )? "Power":title);

}
