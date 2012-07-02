#include "mainwindow.h"
#include <QApplication>
#include <string>
#include <QTranslator>
#include <QLocale>
#include <Magick++.h>

using namespace Magick;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QTranslator appTranslator;
    appTranslator.load(QLocale::system().name(), ":/language");
    app.installTranslator(&appTranslator);
    InitializeMagick(*argv);
    MainWindow xxx;

    xxx.show();
    return app.exec();
}
