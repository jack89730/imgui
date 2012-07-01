
#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include <QMainWindow>
#include "imgfiledlg.h"
#include "generaloption.h"
#include "resizegrp.h"

class QSplitter;

class MainWindow : public QMainWindow
{
  Q_OBJECT

 public:
  MainWindow();

 protected:
  void closeEvent(QCloseEvent *event);
 private:
  void readSettings();
  void writeSettings();

  ImgFileDlg *mainDlg;
  GeneralOption *option;
  ResizeGrp *resize;

  QSplitter *mainSplitter;
  QSplitter *rightSplitter;
  QSplitter *topSplitter;
};
  
#endif /* _MAINWINDOW_H_ */
