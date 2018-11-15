#include "guiserver.h"

GuiServer::GuiServer(Kernel & kernel)
{
    trayMenu = new Menu(kernel);
    trayIcon = new TrayIcon(trayMenu); Q_UNUSED(trayIcon)

    connect(&kernel,&Kernel::launchSettings,this,&GuiServer::launchSettings);

}

GuiServer::~GuiServer()
{
    delete trayMenu;
    delete trayIcon;
}

void GuiServer::launchSettings()
{

}

