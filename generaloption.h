#ifndef _GENARALOPTION_H_
#define _GENARALOPTION_H_

#include <QDialog>

class QGroupBox;
class QCheckBox;
class QComboBox;
class QSpinBox;
class QDoubleSpinBox;

// 具有的功能 quality压缩级别， profile(*),strip, keepexif,rorate,
// reduceNoise降噪， despeckle亮点降噪, addnoise, 高斯模糊
// gaussianblur,炭笔效果charcoal，enhance, 直方图均衡，shave修剪边缘，
// equalize,油画效果oilpaint, trim 移除背景色边缘，sharpen 锐化
class GeneralOption : public QDialog
{
 public:
  GeneralOption(QWidget *parent = 0);
 public slots:
  void optionSettings(void);
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
