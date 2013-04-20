#include "imgfilemodel.h"
#include <QtGui>

ImgFileModel::ImgFileModel(QObject *parent)
  : QAbstractTableModel(parent)
{
  modelheader << tr("Check") << tr("Filename") << tr("FileSize") << tr("FileType") << tr("AbsolutePath");
}

int ImgFileModel::rowCount(const QModelIndex & /* parent */) const
{
  return imgfilelist.size();
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

bool ImgFileModel::setData(const QModelIndex &index, const QVariant &value , int role)
{
  if (!index.isValid()) {
    return false;
  }
  if (index.column() == 0 && role == Qt::CheckStateRole) {
    if (value == Qt::Checked)
      imgfilechecked[imgfilelist.at(index.row()).absoluteFilePath()] = true;
    else
      imgfilechecked[imgfilelist.at(index.row()).absoluteFilePath()] = false;
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
  if (orientation == Qt::Vertical && role == Qt::DisplayRole &&
      section != 0 )
    return QString::number(section);

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

bool ImgFileModel::insertRows(int row, int count, const QModelIndex &index)
{
  Q_UNUSED(index);
  beginInsertRows(QModelIndex(), row, row + count -1);
  endInsertRows();
  return true;
}

bool ImgFileModel::removeRows(int row, int count, const QModelIndex &index)
{
  Q_UNUSED(index);
  beginRemoveRows(QModelIndex(), row, row + count -1);
  endRemoveRows();
  return true;
}

void ImgFileModel::addImgFile(const QStringList &filenames)
{
  int listSizeBefore = imgfilelist.size();
  for (int i = 0; i < filenames.count(); i++) {
    QFileInfo fi(filenames.at(i));
    if (imgfilechecked.find(fi.absoluteFilePath()) == imgfilechecked.end()) {
      beginInsertRows(QModelIndex(), listSizeBefore++, 1);
      imgfilelist += fi;
      imgfilechecked[fi.absoluteFilePath()] = true;
      endInsertRows();
    }
  }
}

void ImgFileModel::addImgDir(const  QString &path, const QStringList &namefilters)
{
  QDir dir(path);
  QList<QFileInfo> newfilelist;
  newfilelist += dir.entryInfoList(namefilters, QDir::Files);
  int listSizeBefore = imgfilelist.size();
  for (int i = 0; i < newfilelist.count(); i++) {
    if (imgfilechecked.find(newfilelist.at(i).absoluteFilePath()) == imgfilechecked.end()) {
      beginInsertRows(QModelIndex(), listSizeBefore++, 1);
      imgfilelist += newfilelist.at(i);
      imgfilechecked[newfilelist.at(i).absoluteFilePath()] = true;
      endInsertRows();
    }
  }
}

void ImgFileModel::addImgDirs(const  QString &path, const QStringList &namefilters)
{
  addImgDir(path, namefilters);

  QDir dir(path);
  QStringList dirs = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden) ;
  for (int i = 0; i < dirs.count() ; i++) {
    QString absolutePath(path + '/' + dirs.at(i));
    addImgDirs(absolutePath, namefilters);
  }
}

void ImgFileModel::selectAll()
{
  beginResetModel();
  QMutableMapIterator<QString, bool> i(imgfilechecked);
  while (i.hasNext()) {
    i.next();
    i.value() = true;
  }
  endResetModel();
}

void ImgFileModel::unSelectAll()
{
  QMutableMapIterator<QString, bool> i(imgfilechecked);
  beginResetModel();
  while (i.hasNext()) {
    i.next();
    i.value() = false;
  }
  endResetModel();
}

void ImgFileModel::removeFile(const QModelIndexList &indexlist)
{
  QListIterator<QModelIndex> i(indexlist);
  QList<int> delRowsList;
  int rowNum;
  while (i.hasNext()) {
    rowNum = i.next().row();
    delRowsList.append(rowNum);
  }

  qSort(delRowsList);
  for (int pos = delRowsList.size(); pos > 0; ++pos) {
    rowNum = delRowsList.at(pos -1);
    beginRemoveRows(QModelIndex(), rowNum, rowNum);
    imgfilechecked.remove(imgfilelist.at(rowNum).absoluteFilePath());
    imgfilelist.removeAt(rowNum);
    endRemoveRows();
  }
}

void ImgFileModel::removeAll()
{
  beginResetModel();
  imgfilelist.clear();
  imgfilechecked.clear();
  endResetModel();
}

void ImgFileModel::convertAll()
{
  QStringList convertFiles;

  QMapIterator<QString, bool> i(imgfilechecked);
  while (i.hasNext()) {
    if (i.next().value())
      convertFiles += i.key();
  }
  emit filesList(convertFiles);
}

void ImgFileModel::removeConverted(const QString &filename)
{
  for (int i = 0; i < imgfilelist.size(); i++)
    if (filename == imgfilelist.at(i).absoluteFilePath()) {
      beginRemoveRows(QModelIndex(), i, i);
      imgfilelist.removeAt(i);
      imgfilechecked.remove(filename);
      endRemoveRows();
      break;
    }
}
