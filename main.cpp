#include <QApplication>
#include "guiserver.h"
#include "kernel.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);
    Kernel K;

    GuiServer Gui(K);    Q_UNUSED(Gui)

    return a.exec();
}
