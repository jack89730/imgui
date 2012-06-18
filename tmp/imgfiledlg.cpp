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

  convertFormat = new QGroupBox;
  convertBox = new QComboBox;
  convertBox->addItems(loadformat.writeFmts);
  convertBox->setSizeAdjustPolicy(QComboBox::AdjustToContentsOnFirstShow);
  convertBox->setCurrentIndex(0);
  convertTo = new QLabel(tr("Convert Format"));
  convertTo->setBuddy(convertBox);
  convert = new QPushButton("Convert");
  QHBoxLayout *convertHL = new QHBoxLayout;
  convertHL->addWidget(convertTo);
  convertHL->addWidget(convertBox);
  convertHL->addStretch();
  convertHL->addWidget(convert);
  convertFormat->setLayout(convertHL);
  //    connect(convert, clicked(), this, startConvert());

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
