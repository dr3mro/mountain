#include "guiserver.h"

GuiServer::GuiServer(Kernel & kernel)
{
    trayMenu = std::make_unique<Menu>(kernel);
    trayIcon = std::make_unique<TrayIcon>(trayMenu.get());
}

