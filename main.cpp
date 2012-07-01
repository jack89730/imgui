#include "mainwindow.h"
#include <QApplication>
#include <QCoreApplication>
#include <string>
#include <Magick++.h>

using namespace Magick;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    InitializeMagick(*argv);
    MainWindow xxx;

    xxx.show();
    return app.exec();
}
