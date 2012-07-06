#include "readerror.h"
#include <QtGui>

ReadError::ReadError(QWidget *parent)
    : QWidget(parent)
{
  errorText = new QTextEdit;
  errorText->setReadOnly(true);
  errorText->setMaximumHeight(100);
  errorText->setToolTip(tr("Except Error is displayed here "));
  QVBoxLayout *errorLayout = new QVBoxLayout;
  errorLayout->addWidget(errorText);

  exceptOutput = new QGroupBox(tr("Except Output"));
  exceptOutput->setLayout(errorLayout);

  QVBoxLayout *mainLayout = new QVBoxLayout(this);
  mainLayout->addWidget(exceptOutput);
  setLayout(mainLayout);
}

void ReadError::appendText(QString text)
{
  errorText->append(text);
}
