#include "guiserver.h"

GuiServer::GuiServer(Kernel & kernel)
{
     trayMenu = new Menu(kernel);
     trayIcon = new TrayIcon(trayMenu);

     connect(&kernel,SIGNAL(launchSettings()),this,SLOT(launchSettings()));

}

GuiServer::~GuiServer()
{
    delete trayMenu;
    delete trayIcon;
}

void GuiServer::launchSettings()
{

}

