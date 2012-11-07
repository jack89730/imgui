
#ifndef _CONVERT_H_
#define _CONVERT_H_
#include <QStringList>
#include <QObject>

enum EXISTSPROCESS{IGNORE, ALLRENAMED, ALLOVERRIDE};

class Convert : public QObject
{
  Q_OBJECT
  
 public:
  Convert(QObject *parent = 0);

signals:
  void fileExists();
  void setProgressRange(int min, int max);
  void setProgressValue(int value);
  void errorAppend(const QString &except);
  void removeConverted(const QString &filename);
  void finished();
 public slots:
  void startConvert();
  void convertFilesList(const QStringList &fileLists);
  void cancelProgress();
  void renameFile();
  void setExistsProcess(int value);

 private:
  QStringList convertFiles;
  QString writeToFile;
  QString suffix;
  EXISTSPROCESS exists;
};


#endif /* _CONVERT_H_ */
