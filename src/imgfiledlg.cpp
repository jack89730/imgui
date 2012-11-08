#include "imgfiledlg.h"
#include <QtGui>

ImgFileDlg::ImgFileDlg(QWidget *parent)
  : QWidget(parent)
{
  model = new ImgFileModel;
  connect(this, SIGNAL(removeConverted(const QString&)),
          model, SLOT(removeConverted(const QString&)));
  connect(model, SIGNAL(filesList(QStringList)),
          this, SIGNAL(filesList(QStringList)));

  tableView = new QTableView;
  tableView->horizontalHeader()->setStretchLastSection(true);
  tableView->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
  tableView->horizontalHeader()->setResizeMode(4, QHeaderView::Stretch);
  tableView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  tableView->adjustSize();
  tableView->setShowGrid(false);

  tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
  tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
  tableView->setModel(model);

  addImg = new QGroupBox;
  addImgFile = new QPushButton(tr("Add Imgs"));
  addImgFolder = new QPushButton(tr("Add Folder"));
  selectAll = new QPushButton(tr("Select All"));
  unSelectAll = new QPushButton(tr("Unselect All"));
  removeImg = new QPushButton(tr("Remove"));
  removeAll = new QPushButton(tr("Remove All"));
  QGridLayout * addImgLayout = new QGridLayout;
  addImgLayout->addWidget(addImgFile, 0, 0);
  addImgLayout->addWidget(addImgFolder, 0, 1);
  addImgLayout->addWidget(selectAll, 0, 2);
  addImgLayout->addWidget(unSelectAll, 0, 3);
  addImgLayout->addWidget(removeImg, 0, 4);
  addImgLayout->addWidget(removeAll, 0, 5);
  addImg->setLayout(addImgLayout);
  addImg->setSizePolicy(QSizePolicy::MinimumExpanding,
                        QSizePolicy::MinimumExpanding);
  connect(addImgFile, SIGNAL(clicked()), this, SLOT(addFiles()));
  connect(addImgFolder, SIGNAL(clicked()), this, SLOT(addDirs()));
  connect(selectAll, SIGNAL(clicked()), model, SLOT(selectAll()));
  connect(unSelectAll, SIGNAL(clicked()), model, SLOT(unSelectAll()));
  connect(removeImg, SIGNAL(clicked()), this, SLOT(removeSelected()));
  connect(removeAll, SIGNAL(clicked()), model, SLOT(removeAll()));

  convertFormat = new QGroupBox(tr("Convert Format"));
  convertBox = new QComboBox(this);
  convertBox->addItems(loadformat.writeFmts);
  convertBox->setSizeAdjustPolicy(QComboBox::AdjustToMinimumContentsLength);
  convertTo = new QLabel(tr("Convert Format"));
  convertTo->setBuddy(convertBox);

  QGridLayout *convertLayout = new QGridLayout;
  convertLayout->addWidget(convertTo, 1, 0, 1, 1);
  convertLayout->addWidget(convertBox, 1, 1, 1, 2);

  outputLabel = new QLabel(tr("Output Dir"));
  outputDir = new QLineEdit;
  browseButton = new QPushButton(tr("Browse"));
  connect(browseButton, SIGNAL(clicked()), this, SLOT(outputBrowse()));
  convertLayout->addWidget(outputLabel, 0, 0, 1, 1);
  convertLayout->addWidget(outputDir, 0, 1, 1, 2);
  convertLayout->addWidget(browseButton, 0, 3, 1, 1);

  convertFormat->setLayout(convertLayout);
  convertFormat->setSizePolicy(QSizePolicy::MinimumExpanding,
                               QSizePolicy::Minimum);
  connect(convertBox, SIGNAL(currentIndexChanged(int)), this, SLOT(saveFormatSet(int)));
  connect(outputDir, SIGNAL(textChanged(const QString &)), this, SLOT(saveOutDir(const QString &)));

  QApplication::setOrganizationName("Sd44 Soft");
  QApplication::setOrganizationDomain("sd44.is-programmer.com");
  QApplication::setApplicationName("Super Img Batcher");
  QSettings settings;

  int curIndex = settings.value("mainWindow/formatIndex", 20).toInt();
  convertBox->setCurrentIndex(curIndex);
  QString xx = settings.value("mainWindow/outDir", QDir::homePath()).toString();
  outputDir->setText(xx);

  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addWidget(tableView);
  mainLayout->addWidget(addImg);
  mainLayout->addWidget(convertFormat);
  mainLayout->setStretchFactor(tableView, 1);
  setLayout(mainLayout);
  setTips();
}

void ImgFileDlg::setTips(void)
{

  convertTo->setToolTip(tr("Convert To the Format Speced By right box"));
  outputLabel->setToolTip(tr("in the right, Choose Output Dir"));
 
  addImg->setToolTip(tr("Add Image Files"));
  addImgFile->setToolTip(tr("Add Image Files"));
  addImgFolder->setToolTip(tr("Add Image Folder, Can Rescuse Subdir"));
  selectAll->setToolTip(tr("Check All"));
  unSelectAll->setToolTip(tr("UnCheck All"));
  removeImg->setToolTip(tr("Remove The Images by Selected Lines"));
  removeAll->setToolTip(tr("Remove All Images From Table"));
}

void ImgFileDlg::addFiles()
{
  QString path = QDir::homePath();

  QStringList fileNames =
    QFileDialog::getOpenFileNames(this, tr("Add Images"),
                                  path, loadformat.readFilter); //FIXME:LINUX下只支持全大写或全小写文件名。
  if (!fileNames.isEmpty()) {
    model->addImgFile(fileNames);
  }
}

void ImgFileDlg::addDirs()
{
  QString path = QDir::homePath();
  QString dir =
    QFileDialog::getExistingDirectory(this, tr("Add Directory"), path,
                                      QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
  if (!dir.isEmpty()) {
    int ret = QMessageBox::warning(this, tr("contant SubDir?"),
                                   tr("Do you want add files in subdirectory recursively ?\n"),
                                   QMessageBox::Ok | QMessageBox::Cancel);
    if (ret == QMessageBox::Ok)
      model->addImgDirs(dir, loadformat.readFmts);
    else
      model->addImgDir(dir, loadformat.readFmts);
  }
}

void ImgFileDlg::removeSelected()
{
  QModelIndexList selectList = tableView->selectionModel()->selectedRows();
  model->removeFile(selectList);
}

void ImgFileDlg::outputBrowse()
{
  
  QString path = QDir::homePath();
  QString dir =
    QFileDialog::getExistingDirectory(this, tr("Add Directory"), path,
                                      QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
  if (!dir.isEmpty())
    outputDir->setText(dir);
}

void ImgFileDlg::convertNowDlg()
{
  QApplication::setOrganizationName("Sd44 Soft");
  QApplication::setOrganizationDomain("sd44.is-programmer.com");
  QApplication::setApplicationName("Super Img Batcher");
  QSettings settings;

  QDir dir(outputDir->text());
  if (!dir.exists()) {
    int ret = QMessageBox::warning(this, tr("The output Dir isn't Exists"),
                                   tr("Do you want auto Create this Dir \n",
                                      "If you Not, images will not to Convert"),
                                   QMessageBox::Ok | QMessageBox::Cancel);
    if (ret == QMessageBox::Ok)
      dir.mkpath(outputDir->text());
    else 
      return;
  }

  settings.beginGroup("output");
  settings.setValue("outputDir", outputDir->text());
  QString outFormat = convertBox->currentText();
  settings.setValue("format", outFormat.left(outFormat.indexOf('-')));
  model->convertAll();
}
  
void ImgFileDlg::saveFormatSet(int index)
{
  QApplication::setOrganizationName("Sd44 Soft");
  QApplication::setOrganizationDomain("sd44.is-programmer.com");
  QApplication::setApplicationName("Super Img Batcher");
  QSettings settings;

  settings.beginGroup("mainWindow");
  settings.setValue("formatIndex", index);
  settings.endGroup();
}

void ImgFileDlg::saveOutDir(const QString &dir)
{
  QApplication::setOrganizationName("Sd44 Soft");
  QApplication::setOrganizationDomain("sd44.is-programmer.com");
  QApplication::setApplicationName("Super Img Batcher");
  QSettings settings;

  settings.beginGroup("mainWindow");
  settings.setValue("outDir", dir);
  settings.endGroup();
}
