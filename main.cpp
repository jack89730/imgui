#include "imgfiledlg.h"

#include <QApplication>
#include <string>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ImgFileDlg xxx;
    xxx.show();
    return app.exec();
}
