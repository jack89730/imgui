#include "imgfilemodel.h"
#include <QtGui>
#include <iostream>
#include <string>
#include <QProgressDialog>

using namespace std;
using namespace Magick;
ImgFileModel::ImgFileModel(QObject *parent)
    : QAbstractTableModel(parent)
{
  modelheader << tr("Check") << tr("Filename") << tr("FileSize") << tr("FileType") << tr("AbsolutePath");
}

int ImgFileModel::rowCount(const QModelIndex & /* parent */) const
{
  return imgfilelist.count();
}

int ImgFileModel::columnCount(const QModelIndex & /* parent */) const
{
  return modelheader.size();
}

QVariant ImgFileModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid()) {
    return QVariant();
  }

  if (role == Qt::TextAlignmentRole) {
    return int(Qt::AlignLeft | Qt::AlignVCenter);
  }
  if (role == Qt::DisplayRole) {
    QString tmp;
    switch (index.column()) {
      case 1:
        return imgfilelist.at(index.row()).fileName();
      case 2:
        return imgfilelist.at(index.row()).size();
      case 3:
        tmp = imgfilelist.at(index.row()).suffix();
        return tmp.toUpper();
      case 4:
        return imgfilelist.at(index.row()).absolutePath();
      default:
        return QVariant();
    }
  }
  if (role == Qt::CheckStateRole && index.column() == 0) {
    if (imgfilechecked[imgfilelist.at(index.row()).absoluteFilePath()] == true) {
      return Qt::Checked;
    } else {
      return Qt::Unchecked;
    }
  }
  return QVariant();
}

bool ImgFileModel::setData(const QModelIndex &index, const QVariant& /* &value */, int /* role */)
{
  if (!index.isValid()) {
    return false;
  }
  if (index.column() == 0) {
    const bool tmp = imgfilechecked.value(imgfilelist.at(index.row()).absoluteFilePath());
    imgfilechecked[imgfilelist.at(index.row()).absoluteFilePath()] = !tmp;
    emit dataChanged(index, index);
    return true;
  }
  return false;
}

QVariant ImgFileModel::headerData(int section, Qt::Orientation orientation,
                                  int role) const
{
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
    return modelheader.at(section);
  }
  return QVariant();
}


Qt::ItemFlags ImgFileModel::flags(const QModelIndex & index) const
{
  Qt::ItemFlags flags = QAbstractItemModel::flags(index);
  if (index.column() == 0) {
    flags |= Qt::ItemIsUserCheckable;
  }
  return flags;
}

void ImgFileModel::addImgFile(const QStringList &filenames)
{
  for (int i = 0; i < filenames.count(); i++) {
    QFileInfo fi(filenames.at(i));
    if (imgfilechecked.find(fi.absoluteFilePath()) == imgfilechecked.end()) {
      imgfilelist += fi;
      imgfilechecked[fi.absoluteFilePath()] = true;
    }
  }
  reset();
}

void ImgFileModel::addImgDir(const  QString path, const QStringList namefilters)
{
  QDir dir(path);
  QList<QFileInfo> newfilelist;
  newfilelist += dir.entryInfoList(namefilters, QDir::Files | QDir::CaseSensitive);
  for (int i = 0; i < newfilelist.count(); i++) {
    if (imgfilechecked.find(newfilelist.at(i).absoluteFilePath()) == imgfilechecked.end()) {
      imgfilelist += newfilelist.at(i);
      imgfilechecked[newfilelist.at(i).absoluteFilePath()] = true;
    }
  }
  reset();
}
void ImgFileModel::addImgDirs(const  QString path, const QStringList namefilters)
{
  QDir dir(path);
  QList<QFileInfo> newfilelist;
  newfilelist += dir.entryInfoList(namefilters, QDir::Files | QDir::CaseSensitive);
  for (int i = 0; i < newfilelist.count(); i++) {
    if (imgfilechecked.find(newfilelist.at(i).absoluteFilePath()) == imgfilechecked.end()) {
      imgfilelist += newfilelist.at(i);
      imgfilechecked[newfilelist.at(i).absoluteFilePath()] = true;
    }
  }

  QStringList dirs = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden) ;
  for (int i = 0; i < dirs.count() && dirs.at(i) != QString() ; i++) {
    QString absolutePath(path + QDir::separator() + dirs.at(i));
    addImgDirs(absolutePath, namefilters);
  }
  reset();
}

void ImgFileModel::selectAll()
{
  QMutableMapIterator<QString, bool> i(imgfilechecked);
  while (i.hasNext()) {
    i.next();
    i.value() = true;
  }
  reset();
}

void ImgFileModel::unSelectAll()
{
  QMutableMapIterator<QString, bool> i(imgfilechecked);
  while (i.hasNext()) {
    i.next();
    i.value() = false;
  }
  reset();
}

/* TODO: it's too stupid...占用资源。。。*/
void ImgFileModel::removeFile(QModelIndexList indexlist)
{
  QMutableListIterator<QModelIndex> i(indexlist);
  QStringList rmFiles;        /* 用户想要删除文件的绝对路径名列表 */
  QList<QFileInfo> rmFileInfoList;
  while (i.hasNext()) {
    i.next();
    int rowNum = i.value().row();
    rmFiles << imgfilelist.at(rowNum).absoluteFilePath();
  }
  for (int j = 0; j < rmFiles.size(); j++) {
    for (int k = 0; k < imgfilelist.size() ; ++k) {
      if (imgfilelist.at(k).absoluteFilePath() == rmFiles.at(j)) {
        imgfilelist.removeAt(k);
      }
    }
    imgfilechecked.remove(rmFiles.at(j));
  }
  reset();
}

void ImgFileModel::removeAll()
{
  imgfilelist.clear();
  imgfilechecked.clear();
  reset();
}

void ImgFileModel::convertAll()
{
  Image img;

  QApplication::setOrganizationName("Sd44 Soft");
  QApplication::setOrganizationDomain("sd44.is-programmer.com");
  QApplication::setApplicationName("Super Img Batcher");
  QSettings settings;

  int progressRange = imgfilelist.size();
  QProgressDialog progress;
  progress.setLabelText(tr("Converting now"));
  progress.setRange(0, progressRange -1);
  progress.setModal(true);

  int fileNumbers = 0;
  
  while (!imgfilelist.isEmpty()) {
    progress.setValue(++fileNumbers);
    qApp->processEvents();
    if (progress.wasCanceled()) {
      emit errorAppend("Canceld Convert by yourself!!");
      return;
    }
    QString imgFile = imgfilelist.at(0).absoluteFilePath();
    try {
      img.read((const char *)imgFile.toLocal8Bit());

      if (int filterType = settings.value("resize/filterBox").toInt()) {
        switch (filterType) {
          case 1:
            img.filterType(LanczosFilter);
          case 2:
            img.filterType(MitchellFilter);
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
          case 1:
            img.addNoise(GaussianNoise);
          case 2:
            img.addNoise(MultiplicativeGaussianNoise);
          case 3:
            img.addNoise(ImpulseNoise);
          case 4:
            img.addNoise(LaplacianNoise);
          case 5:
            img.addNoise(PoissonNoise);
          default:
            img.addNoise(RandomNoise);
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
      
      // FIXME: 转换图片文件后的文件夹 img.write()....
      settings.beginGroup("output");
      // TODO: 批量修改文件名
      QString path = QDir::toNativeSeparators(QDir::homePath());
      if (settings.value("outputDir").isValid()) {
        path = settings.value("outputDir").toString() + "/";
      }
      QString filename = imgfilelist.at(0).completeBaseName();
      filename += "." + settings.value("format", "fuck").toString();
      settings.endGroup();
      QString to8bit(path +filename);
      std::string writeFile = (const char *)to8bit.toLocal8Bit();
      img.write(writeFile);
    }
    catch ( Exception &error_ ) {
      QString error = QString("%1%2").arg("Caught exception:  ").arg(error_.what());
      emit errorAppend(error);
    }
    process.cancel();
    imgfilelist.removeAt(0);
    imgfilechecked.remove(imgFile);
    reset();
  }
}

