#ifndef _RESIZEGRP_H_
#define _RESIZEGRP_H_

#include <QStringList>
#include <QDialog>
#include <string>

class QLabel;
class QGroupBox;
class QCheckBox;
class QSpinBox;
class QComboBox;
class QIntValidator;
class QGridLayout;
class QStringList;

class ResizeGrp : public QDialog
{
  Q_OBJECT
 public:
  ResizeGrp(QWidget *parent = 0);
                     
 public slots:
  void isPercent(int checked);
  void fixedPropo(int checked);
  void keepRatio(int size);
  void resizeOption(void);
 private:
  QGroupBox *resize;
  QSpinBox *widthEdit;
  QSpinBox *heightEdit;
  QSpinBox *xOffset;
  QSpinBox *yOffset;
  QCheckBox *percent;
  QCheckBox *fixedProportion;
  QCheckBox *onlySmaller;
  QCheckBox *onlyGreater;
  QComboBox *filterBox;
  QGridLayout *resizeGrid;
  QStringList filterType;
};

#endif /* _RESIZEGRP_H_ */






