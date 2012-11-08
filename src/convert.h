
#ifndef _CONVERT_H_
#define _CONVERT_H_
#include <QStringList>
#include <QObject>
class MainWindow;

enum EXISTSPROCESS{OVERRIDE, RENAME, ALLOVERRIDE, ALLRENAMED};

class Convert : public QObject
{
  Q_OBJECT
  
 public:
  Convert(QObject *parent = 0);
  QObject *mainWindow;

signals:
  void setProgressRange(int min, int max);
  void setProgressValue(int value);
  void errorAppend(const QString &except);
  void removeConverted(const QString &filename);
  void finished();
 public slots:
  void startConvert();
  void convertFilesList(const QStringList &fileLists);
  void cancelProgress();

 private:
  void renameFile();
  QStringList convertFiles;
  QString writeToFile;
  QString suffix;
  EXISTSPROCESS exists;
};


#endif /* _CONVERT_H_ */
