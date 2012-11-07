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
  
  setWindowTitle(tr("Fucking Image Batcher"));
  readSettings();
}

void MainWindow::isAllOveride()
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
    break;
  case QMessageBox::No:
    emit renameFile();
    break;
  case QMessageBox::YesToAll:
    emit setExistsProcess(2);
    break;
  case QMessageBox::NoToAll:
    emit renameFile();
    emit setExistsProcess(1);
    break;
  default:
    qDebug() << "What's fucking happend at writefile." << endl;
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
  QThread *thread = new QThread;
  convert = new Convert;

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

  connect(convert, SIGNAL(fileExists()),
          this, SLOT(isAllOveride()), Qt::BlockingQueuedConnection);
  connect(this, SIGNAL(renameFile()),
          convert, SLOT(renameFile()));
  connect(this, SIGNAL(setExistsProcess(int)),
          convert, SLOT(setExistsProcess(int)));

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
