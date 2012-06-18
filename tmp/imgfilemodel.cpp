#include "imgfilemodel.h"
#include <QtGui>

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

  QStringList dirs = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden) ;
  for (int i = 0; i < dirs.count() && dirs.at(i) != QString() ; i++) {
    QString absolutePath(path + QDir::separator() + dirs.at(i));
    addImgDir(absolutePath, namefilters);
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
  QStringList rmFiles;        /* 要删除文件的绝对路径名列表 */
  QList<QFileInfo> rmFileInfoList;
  while (i.hasNext()) {
    i.next();
    int rowNum = i.value().row();
    rmFiles << imgfilelist.at(rowNum).absoluteFilePath();
  }
  for (int j = 0; j < rmFiles.size(); j++) {
    for (int k = 0; k < imgfilelist.size() ; ++k) {
      if (imgfilelist.at(k).absoluteFilePath() == rmFiles.at(j))
        imgfilelist.removeAt(k); 
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
