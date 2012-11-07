#include "convert.h"
#include <Magick++.h>
#include <QtCore>

using namespace std;
using namespace Magick;

Convert::Convert(QObject *parent)
  : QObject(parent)
{
}

void Convert::convertFilesList(const QStringList &filelist)
{
  convertFiles = filelist;
}

void Convert::startConvert()
{
  exists = IGNORE;

  Image img;

  QCoreApplication::setOrganizationName("Sd44 Soft");
  QCoreApplication::setOrganizationDomain("sd44.is-programmer.com");
  QCoreApplication::setApplicationName("Super Img Batcher");
  QSettings settings;

  suffix = settings.value("format", "fuck").toString().toLower();
  int progressRange = convertFiles.size();
  emit setProgressRange(0, progressRange);
  int fileNumbers = 0;

  while (!convertFiles.isEmpty()) {
      QString imgFile = convertFiles.at(0);
      emit setProgressValue(++fileNumbers);

      try {
        img.read(imgFile.toLocal8Bit().constData());

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
        if (settings.value("outputDir").isValid())
            path = settings.value("outputDir").toString() + "/";

        QString filename = imgFile.left(imgFile.lastIndexOf('.') + 1);
        filename = filename.mid(filename.lastIndexOf('/') + 1);

        filename += suffix;
        settings.endGroup();
        writeToFile = QString(path + filename);
        if (QFile::exists(writeToFile)) {
            if (exists == ALLRENAMED) {
                renameFile();
              } else if (exists != ALLOVERRIDE) {
                emit fileExists();
              }
          }

        std::string writeFile = writeToFile.toLocal8Bit().constData();
        img.write(writeFile);
      }
       catch ( Exception &error_ ) {
        QString error = QString("%1%2").arg("Caught exception:  ").arg(error_.what());
        emit errorAppend(error);
      }
      convertFiles.removeFirst();
      emit removeConverted(imgFile);
    }
  emit finished();
}

void Convert::cancelProgress()
{
  emit errorAppend("Canceld the image files convert by yourself");
  emit finished();
}

void Convert::renameFile()
{
  int i = 0;
  int dotIndex = writeToFile.lastIndexOf('.');
  QString widthNum;
  QString tmp = "." + suffix;
  while (QFile::exists(writeToFile)) {
      widthNum = QString::number(++i);
      if (i < 10)
        widthNum = QString("000") + widthNum;
      else if (i < 100)
        widthNum = QString("00") + widthNum;

      writeToFile = QString("%1%2%3%4").arg(writeToFile.left(dotIndex))
          .arg("-").arg(widthNum).arg(tmp);
    }
}

void Convert::setExistsProcess(int value) //0,ignore;1, allrenamed, 2,AllOveride
{
  if (value == 1)
    exists = ALLRENAMED;
  if (value == 2)
    exists = ALLOVERRIDE;
}

