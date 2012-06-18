#ifndef  IMGFILEDLG_INC
#define  IMGFILEDLG_INC


#include "loadformats.h"
#include "imgfilemodel.h"
#include <QDialog>

class QTableView;
class QGroupBox;
class QLabel;
class QPushButton;
class QComboBox;
class QAction;

class ImgFileDlg : public QDialog
{
    Q_OBJECT
 public:
    ImgFileDlg(QWidget *parent = 0);
 private slots:
//     void startConvert();
    void addFiles();
    void addDirs();
    void removeSelected();
 private:
    LoadFormats loadformat;
    ImgFileModel *model;
    QTableView *tableView;

    QGroupBox *convertFormat;
    QLabel *convertTo;
    QComboBox *convertBox;
    QPushButton *convert;
    
    QGroupBox *addImg;
    QPushButton *addImgFile;
    QPushButton *addImgFolder;
    QPushButton *selectAll;
    QPushButton *unSelectAll;
    QPushButton *removeImg;
    QPushButton *removeAll;
};

#endif   /* ----- #ifndef IMGFILEDLG_INC  ----- */
