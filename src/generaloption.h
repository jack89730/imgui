#ifndef _GENARALOPTION_H_
#define _GENARALOPTION_H_

#include <QDialog>
#include <QCoreApplication>

class QGroupBox;
class QCheckBox;
class QComboBox;
class QSpinBox;
class QDoubleSpinBox;

class GeneralOption : public QWidget
{
  Q_DECLARE_TR_FUNCTIONS(GeneralOption)

 public:
  GeneralOption(QWidget *parent = 0);
  void optionSettings(void);
  void setTips(void);
 private:
  QGroupBox *generalOption;
  QCheckBox *quality;                   //JPG,PNG,MIFF ONLY
  QSpinBox *qualityBox;
  QCheckBox *eraseProfile;
  QCheckBox *keepExif;
  // QCheckBox *autoRorate; Fixme:Todo
  QCheckBox *reduceNoise;
  QCheckBox *reduceSpeckleNoise;
  QCheckBox *enhance; // minimize noise
  QCheckBox *normalize; // 归一化对比度
  QCheckBox *trim;
  QCheckBox *edge;       // Highlight img edge
  QCheckBox *emboss;     //3D highlight edge
  QCheckBox *equalize;   // histogram equalize
  QCheckBox *monoChrome; //black/white pic,Must use +dither
                         //-colorspace gray -colors 2 效果更好
  
  QCheckBox *addNoise;
  QComboBox *noiseType;

  QCheckBox *sharpen; //锐化
  QDoubleSpinBox *sharpenRadius; //Gaussian radius
  // QDoubleSpinBox *sharpenSigma; //Laplacian deviation
  QCheckBox *charcoal;                  //tan bi; radius 0.0 sigma 1.0
  QDoubleSpinBox *charcoalRadius;
  // QDoubleSpinBox *charcoalSigma;
  QCheckBox *oilPaint;
  QDoubleSpinBox *oilRadius;
};

#endif /* _GENARALOPTIONOPTION_H_ */
