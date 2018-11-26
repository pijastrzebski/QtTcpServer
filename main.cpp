#include "tcpServer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    tcpServer w;
    return a.exec();
}
