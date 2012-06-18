#include "imgfiledlg.h"

#include <QApplication>
#include <string>
#include <Magick++.h>

using namespace Magick;

int main(int argc, char *argv[])
{
    InitializeMagick(*argv);
    QApplication app(argc, argv);
    ImgFileDlg xxx;
    xxx.show();
    return app.exec();
}
