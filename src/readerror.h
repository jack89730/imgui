#ifndef _READERROR_H_
#define _READERROR_H_

#include <QWidget>
class QGroupBox;
class QTextEdit;

class ReadError : public QWidget
{
  Q_OBJECT
  
 public:
  ReadError(QWidget *parent = 0);
 public slots:
  void appendText(const QString &text);
  
 private:
  QTextEdit *errorText;
  QGroupBox *exceptOutput;
};



#endif /* _READERROR_H_ */
