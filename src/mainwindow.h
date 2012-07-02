
#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include <QMainWindow>
#include "imgfiledlg.h"
#include "generaloption.h"
#include "resizegrp.h"

class QSplitter;
class QPushButton;
class QVBoxLayout;
class QHBoxLayout;

class MainWindow : public QMainWindow
{
  Q_OBJECT

 public:
  MainWindow();

 public slots:
  void convertNow(void);

 protected:
  void closeEvent(QCloseEvent *event);
 private:
  void readSettings();
  void writeSettings();

  ImgFileDlg *mainDlg;
  GeneralOption *option;
  ResizeGrp *resize;
  QPushButton *Convert;

  QHBoxLayout *convertHL;
  QVBoxLayout *leftLayout;
  QVBoxLayout *rightLayout;
  QHBoxLayout *topLayout;

};
  
#endif /* _MAINWINDOW_H_ */
