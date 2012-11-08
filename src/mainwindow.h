#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include <QMainWindow>
#include "imgfiledlg.h"
#include "generaloption.h"
#include "resizegrp.h"
#include "readerror.h"
#include "convert.h"

class QSplitter;
class QPushButton;
class QVBoxLayout;
class QHBoxLayout;
class QProgressDialog;

class MainWindow : public QMainWindow
{
  Q_OBJECT

 public:
  MainWindow();

public slots:
  void enableConvert();
  int isAllOveride();
 private slots:
  void convertNow();

 protected:
  void closeEvent(QCloseEvent *event);
 private:
  void readSettings();
  void writeSettings();

  ImgFileDlg *mainDlg;
  GeneralOption *option;
  ResizeGrp *resize;
  ReadError *exceptError;
  Convert *convert;
  QPushButton *convertButton;
  QProgressDialog *progressDialog;

  QHBoxLayout *convertHL;
  QVBoxLayout *leftLayout;
  QVBoxLayout *rightLayout;
  QHBoxLayout *topLayout;
  QVBoxLayout *mainLayout;
};
  
#endif /* _MAINWINDOW_H_ */
