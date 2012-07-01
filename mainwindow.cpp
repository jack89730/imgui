#include "mainwindow.h"
#include <QtGui>

MainWindow::MainWindow()
{
  rightSplitter = new QSplitter(Qt::Vertical);
  topSplitter = new QSplitter(Qt::Horizontal);
  mainSplitter = new QSplitter(Qt::Vertical);

  resize = new ResizeGrp;
  option = new GeneralOption;
  rightSplitter->addWidget(resize);
  rightSplitter->addWidget(option);
  rightSplitter->setStretchFactor(1, 1);
  mainDlg = new ImgFileDlg;

  topSplitter->addWidget(mainDlg);
  topSplitter->addWidget(rightSplitter);

  setCentralWidget(topSplitter);
  setWindowTitle(tr("Fucking Image Batcher"));
  readSettings();
}


void MainWindow::closeEvent(QCloseEvent *event)
{
  writeSettings();
  event->accept();
}
  
void MainWindow::readSettings()
{
  QApplication::setOrganizationName("Sd44 Soft");
  QApplication::setOrganizationDomain("sd44.is-programmer.com");
  QApplication::setApplicationName("Super Img Batcher");
  QSettings settings;

  settings.beginGroup("mainWindow");
  restoreGeometry(settings.value("geometry").toByteArray());
  mainSplitter->restoreState(
      settings.value("mainSplitter").toByteArray());
  topSplitter->restoreState(
      settings.value("topSplitter").toByteArray());
  rightSplitter->restoreState(
      settings.value("rightSplitter").toByteArray());
}

void MainWindow::writeSettings()
{
  QApplication::setOrganizationName("Sd44 Soft");
  QApplication::setOrganizationDomain("sd44.is-programmer.com");
  QApplication::setApplicationName("Super Img Batcher");
  QSettings settings;

  settings.beginGroup("mainWindow");
  settings.setValue("geometry", saveGeometry());
  settings.setValue("mainSplitter", mainSplitter->saveState());
  settings.setValue("rightSplitter", rightSplitter->saveState());
  settings.setValue("topSplitter", topSplitter->saveState());
  settings.endGroup();

}


  
  
 
