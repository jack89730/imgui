
#ifndef _CONVERT_H_
#define _CONVERT_H_
#include <QWidget>

class Convert : public QWidget
{
  Q_OBJECT
  
 public:
  Convert(QWidget *parent = 0);
  void renameFile(QString &renameFilenames,const QString &suffix);

 signals:
  void errorAppend(QString except);
  void removeConverted(QString filename);
 public slots:
  void convertFilesList(QList<QString> filelist);

 private:
  bool allOverride;
  bool allRenamed;
};


#endif /* _CONVERT_H_ */
