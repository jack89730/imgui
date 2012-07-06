#include "convert.h"
#include <Magick++.h>
#include <QtGui>
#include <QProgressDialog>

using namespace std;
using namespace Magick;

Convert::Convert(QWidget *parent)
    : QWidget(parent)
{
}

void Convert::convertFilesList(QList<QString> filelist)
{
    allOverride = false;
    allRenamed = false;

    Image img;

    QApplication::setOrganizationName("Sd44 Soft");
    QApplication::setOrganizationDomain("sd44.is-programmer.com");
    QApplication::setApplicationName("Super Img Batcher");
    QSettings settings;


    int progressRange = filelist.size();
    QProgressDialog progress;
    progress.setLabelText(tr("Converting now"));
    progress.setRange(0, progressRange);
    progress.setWindowModality(Qt::WindowModal);
    int fileNumbers = 0;

    while (!filelist.isEmpty()) {
        QString imgFile = filelist.at(0);
        if (progress.wasCanceled()) {
            emit errorAppend("Canceld Convert by yourself!!");
            return;
        }
        progress.setValue(++fileNumbers);

        try {
            // img.read(imgFile.toAscii().constData());
            img.read(imgFile.toLocal8Bit().constData());
            // img.read(imgFile.toUtf8().constData());

            if (int filterType = settings.value("resize/filterBox").toInt()) {
                switch (filterType) {
                case 1:
                    img.filterType(LanczosFilter);
                    break;
                case 2:
                    img.filterType(MitchellFilter);
                    break;
                }
            }
            if (settings.value("resize/geometry").isValid()) {
                std::string tmpgeo = settings.value("resize/geometry").toString().toStdString();
                img.zoom(tmpgeo);
            }

            settings.beginGroup("general");
            if (settings.value("quality").toBool()) {
                img.quality(settings.value("qualityBox").toInt());
            }
            Blob exifBlob;
            if (settings.value("eraseProfile").toBool()) {
                if (settings.value("keepExif").toBool()) {
                    img.profile("EXIF", exifBlob);
                }
                img.profile("*", Blob());
                img.profile("EXIF", exifBlob);
            }
            if (settings.value("reduceNoise").toBool()) {
                img.reduceNoise();
            }
            if (settings.value("reduceSpeckleNoise").toBool()) {
                img.despeckle();
            }
            if (settings.value("enhance").toBool()) {
                img.enhance();
            }
            if (settings.value("normalize").toBool()) {
                img.normalize();
            }
            if (settings.value("trim").toBool()) {
                img.trim();
            }
            if (settings.value("edge").toBool()) {
                img.edge();
            }
            if (settings.value("emboss").toBool()) {
                img.emboss();
            }
            if (settings.value("equalize").toBool()) {
                img.equalize();
            }
            if (settings.value("monoChrome").toBool()) {
                img.quantizeColorSpace(GRAYColorspace);
                img.quantizeColors(2);
                img.quantize();
                img.normalize();
            }
            if (settings.value("addNoise").toBool()) {
                int noise = settings.value("noiseType").toInt();
                switch (noise) {
                case 0:
                    img.addNoise(UniformNoise);
                    break;
                case 1:
                    img.addNoise(GaussianNoise);
                    break;
                case 2:
                    img.addNoise(MultiplicativeGaussianNoise);
                    break;
                case 3:
                    img.addNoise(ImpulseNoise);
                    break;
                case 4:
                    img.addNoise(LaplacianNoise);
                    break;
                case 5:
                    img.addNoise(PoissonNoise);
                    break;
                default:
                    img.addNoise(RandomNoise);
                    break;
                }
            }
            if (settings.value("sharpen").toBool()) {
                img.sharpen(settings.value("sharpenRadius").toDouble());
            }
            if (settings.value("charcoal").toBool()) {
                img.charcoal(settings.value("charcoalRadius").toDouble());
            }
            if (settings.value("oilPaint").toBool()) {
                img.oilPaint(settings.value("oilRadius").toDouble());
            }
            settings.endGroup();

            // FIXME: if except error, then the ImgFile maybe 0 bytes....
            settings.beginGroup("output");
            // TODO: 批量修改文件名
            QString path = QDir::homePath();
            if (settings.value("outputDir").isValid()) {
                path = settings.value("outputDir").toString() + "/";
            }
            QString filename = imgFile.left(imgFile.lastIndexOf('.') + 1);
            filename = filename.mid(filename.lastIndexOf('/') + 1);

            QString suffix = settings.value("format", "fuck").toString();
            filename += suffix;
            settings.endGroup();
            QString writeto(path + filename);
            if (QFile::exists(writeto)) {
                if (allRenamed) {
                  renameFile(writeto, suffix);
                } else if (!allOverride) {
                    int ret = QMessageBox::warning(this, tr("My Application"),
                                                   tr("The writeto File is existed, Do you want to override it.\n"
                                                      "If you selecet NO, \n "
                                                      "the writeto File will autorenamed xxx01.format"),
                                                   QMessageBox::Yes | QMessageBox::No
                                                   | QMessageBox::YesToAll | QMessageBox::NoToAll);
                    switch (ret) {
                    case QMessageBox::Yes:
                        break;
                    case QMessageBox::No:
                      renameFile(writeto, suffix);
                        break;
                    case QMessageBox::YesToAll:
                        allOverride = true;
                        break;
                    case QMessageBox::NoToAll:
                      renameFile(writeto, suffix);
                        allRenamed = true;
                        break;
                    default:
                        qDebug() << "What's fucking happend at writefile." << endl;
                    }
                }
            }

            std::string writeFile = writeto.toLocal8Bit().constData();
            img.write(writeFile);
        } catch ( Exception &error_ ) {
            QString error = QString("%1%2").arg("Caught exception:  ").arg(error_.what());
            emit errorAppend(error);
        }
        filelist.removeFirst();
        emit removeConverted(imgFile);
    }
}

void Convert::renameFile(QString &renameFilenames, const QString &suffix)
{
    int i = 0;
    int dotIndex = renameFilenames.lastIndexOf('.');
    while (QFile::exists(renameFilenames)) {
      QString widthNum = QString::number(++i);
      if (i < 10)
        widthNum = QString("00") + widthNum;
      else if (i < 100)
        widthNum = QString("0") + widthNum;

      QString tmp = "." + suffix;
        
      renameFilenames = QString("%1%2%3%4").arg(renameFilenames.left(dotIndex))
          .arg("-").arg(widthNum).arg(tmp);
    }
}
