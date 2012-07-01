#ifndef  IMGFILEDLG_H
#define  IMGFILEDLG_H


#include "loadformats.h"
#include "imgfilemodel.h"
#include <QDialog>

class QTableView;
class QGroupBox;
class QLabel;
class QPushButton;
class QComboBox;
class QAction;
class QLineEdit;

class ImgFileDlg : public QWidget
{
  Q_OBJECT
 public:
  ImgFileDlg(QWidget *parent = 0);
 public slots:
  void outputBrowse(void);
 private slots:
  // void startConvert();
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
  QLabel *outputLabel;
  QLineEdit *outputDir;
  QPushButton *browseButton;
 
  QGroupBox *addImg;
  QPushButton *addImgFile;
  QPushButton *addImgFolder;
  QPushButton *selectAll;
  QPushButton *unSelectAll;
  QPushButton *removeImg;
  QPushButton *removeAll;
};

#endif   /* ----- #ifndef IMGFILEDLG_H  ----- */
