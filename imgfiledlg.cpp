#include "imgfiledlg.h"
#include <QtGui>

ImgFileDlg::ImgFileDlg(QWidget *parent)
  : QDialog(parent)
{
  model = new ImgFileModel;
  tableView = new QTableView;
  tableView->horizontalHeader()->setStretchLastSection(true);
  tableView->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
  tableView->horizontalHeader()->setResizeMode(4, QHeaderView::Stretch);
  tableView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
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
  connect(addImgFile, SIGNAL(clicked()), this, SLOT(addFiles()));
  connect(addImgFolder, SIGNAL(clicked()), this, SLOT(addDirs()));
  connect(selectAll, SIGNAL(clicked()), model, SLOT(selectAll()));
  connect(unSelectAll, SIGNAL(clicked()), model, SLOT(unSelectAll()));
  connect(removeImg, SIGNAL(clicked()), this, SLOT(removeSelected()));
  connect(removeAll, SIGNAL(clicked()), model, SLOT(removeAll()));

  convertFormat = new QGroupBox(tr("Convert Format"));
  convertBox = new QComboBox(this);
  convertBox->addItems(loadformat.writeFmts);
  convertBox->setSizeAdjustPolicy(QComboBox::AdjustToContentsOnFirstShow);
  convertBox->setCurrentIndex(0);
  convertTo = new QLabel(tr("Convert Format"));
  convertTo->setBuddy(convertBox);
  convert = new QPushButton(tr("Convert"));
  // connect(convert, clicked(), this, startConvert());
  QGridLayout *convertLayout = new QGridLayout;

  // QHBoxLayout *convertHL = new QHBoxLayout(this);
  convertLayout->addWidget(convertTo, 0, 0, 1, 1);
  convertLayout->addWidget(convertBox, 0, 1, 1, 2);
  convertLayout->addWidget(convert, 0, 3, 1, 1);
  // convertLayout.addLayout(convertHL, 0, 0);

  outputLabel = new QLabel(tr("Output Dir"));
  outputDir = new QLineEdit(QDir::homePath());
  browseButton = new QPushButton(tr("Browse"));
  connect(browseButton, SIGNAL(clicked()), this, SLOT(outputBrowse()));
  convertLayout->addWidget(outputLabel, 1, 0, 1, 1);
  convertLayout->addWidget(outputDir, 1, 1, 1, 2);
  convertLayout->addWidget(browseButton, 1, 3, 1, 1);

  convertFormat->setLayout(convertLayout);

  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addWidget(tableView);
  mainLayout->addWidget(addImg);
  mainLayout->addWidget(convertFormat);
  setLayout(mainLayout);
}

void ImgFileDlg::addFiles()
{
  QString path = QDir::homePath();

  QStringList fileNames =
    QFileDialog::getOpenFileNames(this, tr("Add Images"),
                                  path, loadformat.readFilter);
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
