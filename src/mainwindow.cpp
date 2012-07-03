#include "mainwindow.h"
#include <QtGui>

MainWindow::MainWindow()
{
  
  resize = new ResizeGrp;
  option = new GeneralOption;
  mainDlg = new ImgFileDlg;
  exceptError = new ReadError;
  connect(mainDlg, SIGNAL(errorAppend(QString)), exceptError, SLOT(appendText(QString)));

  Convert = new QPushButton(tr("Convert Now"));
  connect(Convert, SIGNAL(clicked()), this, SLOT(convertNow()));
  convertHL = new QHBoxLayout;
  convertHL->addStretch();
  convertHL->addWidget(Convert);

  leftLayout = new QVBoxLayout;
  leftLayout->addWidget(mainDlg);
  leftLayout->addLayout(convertHL);

  rightLayout = new QVBoxLayout;
  rightLayout->addWidget(resize);
  rightLayout->addWidget(option);
  
  topLayout = new QHBoxLayout;
  topLayout->addLayout(leftLayout);
  topLayout->addLayout(rightLayout);
  
  mainLayout = new QVBoxLayout;
  mainLayout->addLayout(topLayout);
  mainLayout->addWidget(exceptError);
  
  QWidget *widget = new QWidget;
  widget->setLayout(mainLayout);
  setCentralWidget(widget);
  
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
  restoreState(settings.value("state").toByteArray());
  settings.remove("resize");
  settings.remove("general");
  settings.remove("output");
}

void MainWindow::writeSettings()
{
  QApplication::setOrganizationName("Sd44 Soft");
  QApplication::setOrganizationDomain("sd44.is-programmer.com");
  QApplication::setApplicationName("Super Img Batcher");
  QSettings settings;

  settings.beginGroup("mainWindow");
  settings.setValue("geometry", saveGeometry());
  settings.setValue("state", saveState());
  settings.remove("resize");
  settings.remove("general");
  settings.remove("output");
  settings.endGroup();
}

void MainWindow::convertNow()
{
  resize->resizeOption();
  option->optionSettings();
  mainDlg->convertNowDlg();

}

