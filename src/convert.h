
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
  void errorAppend(const QString &except);
  void removeConverted(const QString &filename);
 public slots:
  void convertFilesList(QStringList &fileLists);

 private:
  bool allOverride;
  bool allRenamed;
};


#endif /* _CONVERT_H_ */
