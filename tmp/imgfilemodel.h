#ifndef  imgfilemodel_INC
#define  imgfilemodel_INC

#include <QStringList>
#include <QFileInfo>
#include <QMap>
#include <QAbstractTableModel>

class ImgFileModel : public QAbstractTableModel
{
    Q_OBJECT

 public:
    ImgFileModel(QObject *parent = 0);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    void addImgFile(const QStringList &filenames); 
    void addImgDir(const QString path, const QStringList namefilters = QStringList());

 public slots:
    void selectAll();
    void unSelectAll();
    void removeFile(QModelIndexList indexlist);
    void removeAll();
    

 private:
    QStringList modelheader;
    QList<QFileInfo> imgfilelist;
    QMap<QString, bool> imgfilechecked; /* tablemodel with checkbox */
};

#endif   /* ----- #ifndef imgfilemodel_INC  ----- */
