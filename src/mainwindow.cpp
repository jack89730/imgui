#include "mainwindow.h"
#include <QtGui>

MainWindow::MainWindow()
{
  resize = new ResizeGrp;
  option = new GeneralOption;
  mainDlg = new ImgFileDlg;
  exceptError = new ReadError;

  convertButton = new QPushButton(tr("Convert Now"));
  connect(convertButton, SIGNAL(clicked()), this, SLOT(convertNow()));
  convertHL = new QHBoxLayout;
  convertHL->addStretch();
  convertHL->addWidget(convertButton);

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
  
  setWindowTitle(tr("QGM Image Batcher"));
  readSettings();
}

int MainWindow::isAllOveride()
{
  int ret = QMessageBox::warning(this, tr("My Application"),
                                 tr("The writeto File is existed, "
                                    "Do you want to override it.\n"
                                    "If you selecet NO, \n "
                                    "the writeto File will autorenamed xxx01.format"),
                                 QMessageBox::Yes | QMessageBox::No
                                 | QMessageBox::YesToAll | QMessageBox::NoToAll);
  switch (ret) {
  case QMessageBox::Yes:
    return 0;
  case QMessageBox::No:
    return 1;
  case QMessageBox::YesToAll:
    return 2;
  case QMessageBox::NoToAll:
    return 3;
  default:
    qDebug() << "What's fucking happend at writefile." << endl;
    return -1;
    }
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
  convertButton->setEnabled(false);
  QThread *thread = new QThread;
  convert = new Convert;
  convert->mainWindow = this;

  connect(mainDlg, SIGNAL(filesList(QStringList)),
          convert, SLOT(convertFilesList(QStringList)));
  connect(convert, SIGNAL(removeConverted(const QString &)),
          mainDlg, SIGNAL(removeConverted(const QString &)));
  resize->resizeOption();
  option->optionSettings();
  mainDlg->convertNowDlg();


  progressDialog = new QProgressDialog;
  progressDialog->setLabelText(tr("Converting Image files now"));
  progressDialog->setWindowModality(Qt::WindowModal);

  connect(progressDialog, SIGNAL(canceled()),
          convert, SIGNAL(finished()));
  connect(convert, SIGNAL(setProgressRange(int,int)),
          progressDialog, SLOT(setRange(int,int)));
  connect(convert, SIGNAL(setProgressValue(int)),
          progressDialog, SLOT(setValue(int)));

  connect(convert, SIGNAL(finished()), this, SLOT(enableConvert()));


  connect(convert, SIGNAL(errorAppend(const QString &)),
          exceptError, SLOT(appendText(const QString &)));

  connect(thread, SIGNAL(started()), convert, SLOT(startConvert()));
  connect(convert, SIGNAL(finished()),
          progressDialog, SLOT(deleteLater()));
  connect(convert, SIGNAL(finished()), thread, SLOT(quit()));
  connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
  connect(thread, SIGNAL(terminated()), thread, SLOT(deleteLater()));
  connect(thread, SIGNAL(terminated()), convert, SLOT(deleteLater()));
  connect(convert, SIGNAL(finished()), convert, SLOT(deleteLater()));

  convert->moveToThread(thread);
  thread->start();
}

void MainWindow::enableConvert()
{
  convertButton->setEnabled(true);
}
