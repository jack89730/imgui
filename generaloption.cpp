#include "generaloption.h"
#include <QtGui>

GeneralOption::GeneralOption(QWidget *parent)
    : QDialog(parent)
{
  generalOption = new QGroupBox(tr("Genaral Option"), this);

  QGridLayout groupGrid;

  quality = new QCheckBox(tr("JPG/PNG Quality "));
  qualityBox = new QSpinBox;
  qualityBox->setRange(1, 100);
  qualityBox->setValue(90);
  qualityBox->adjustSize();
  QFormLayout qualityForm;
  qualityForm.addRow(quality, qualityBox);
  keepExif = new QCheckBox(tr("Keep EXIF Info"));
  groupGrid.addLayout(&qualityForm, 0, 0, 1, 2);
  groupGrid.addWidget(keepExif, 1, 0, 1, 1);

  eraseProfile = new QCheckBox(tr("Remove All Profile"));
  enhance = new QCheckBox(tr("Image Enchance"));
  normalize = new QCheckBox(tr("Normalize Img"));
  groupGrid.addWidget(eraseProfile, 1, 1);
  groupGrid.addWidget(enhance, 2, 0);
  groupGrid.addWidget(normalize, 2, 1);

  reduceNoise = new QCheckBox(tr("Reduce Noise"));
  reduceSpeckleNoise = new QCheckBox(tr("Reduce Speckle Noise"));
  groupGrid.addWidget(reduceNoise, 3, 0);
  groupGrid.addWidget(reduceSpeckleNoise, 3, 1);

  addNoise = new QCheckBox(tr("Add Noise"));
  QStringList noisetypeList = QStringList() << tr("UniformNoise") << tr("GaussianNoise")
                                            << tr("MuliticativeGaus") << tr("ImpulseNoise")
                                            << tr("LaplacianNoise") << tr("PoissonNOise");
  noiseType = new QComboBox();
  noiseType->addItems(noisetypeList);
  noiseType->setSizeAdjustPolicy(QComboBox::AdjustToContents);
  noiseType->setCurrentIndex(0);
  QFormLayout noiseForm;
  noiseForm.addRow(addNoise, noiseType);
  groupGrid.addLayout(&noiseForm, 4, 0, 1, 2);

  sharpen = new QCheckBox(tr("Sharpen Img"));
  sharpenRadius = new QDoubleSpinBox;
  sharpenRadius->setRange(0.0, 4.0);
  sharpenRadius->setValue(0.0);
  sharpenRadius->setSingleStep(0.1);
  QFormLayout sharpenRadiusForm;
  sharpenRadiusForm.addRow(tr("Gaussian Radius Pixel"), sharpenRadius);
  // sharpenSigma = new QDoubleSpinBox;
  // sharpenSigma->setRange(1.0, 2.0);
  // sharpenSigma->setValue(1.0);
  // sharpenSigma->setSingleStep(0.1);
  // QFormLayout sharpenSigmaForm;
  // sharpenSigmaForm.addRow(tr("Laplacian Deviation Pixel"), sharpenSigma);
  groupGrid.addWidget(sharpen, 5, 0);
  groupGrid.addLayout(&sharpenRadiusForm, 5, 1);
  // groupGrid.addLayout(&sharpenSigmaForm, 5, 2);

  trim = new QCheckBox(tr("Trim Edge BackGround Color"));
  edge = new QCheckBox(tr("Hightlight Edge"));
  emboss = new QCheckBox(tr("3D Hightlight Edge"));
  groupGrid.addWidget(trim, 6, 0);
  groupGrid.addWidget(edge, 6, 1);
  groupGrid.addWidget(emboss, 6, 2);

  equalize = new QCheckBox(tr("Histogram Equalize"));
  monoChrome = new QCheckBox(tr("Monochrome Img"));
  groupGrid.addWidget(equalize, 7, 0);
  groupGrid.addWidget(monoChrome, 7, 1);

  charcoal = new QCheckBox(tr("Charcoal Effect"));
  charcoalRadius = new QDoubleSpinBox;
  charcoalRadius->setRange(0.00, 0.99);
  charcoalRadius->setValue(0.0);
  charcoalRadius->setSingleStep(0.1);
  QFormLayout charcoalRadiusForm;
  charcoalRadiusForm.addRow(tr("Gaussian Radius Pixel"), charcoalRadius);
  // charcoalSigma = new QDoubleSpinBox;
  // charcoalSigma->setRange(1.0, 2.0);
  // charcoalSigma->setValue(1.0);
  // QFormLayout charcoalSigmaForm;
  // charcoalSigmaForm.addRow(tr("Laplacian Deviation Pixel"), charcoalSigma);
  groupGrid.addWidget(charcoal, 8, 0);
  groupGrid.addLayout(&charcoalRadiusForm, 8, 1);
  // groupGrid.addLayout(&charcoalSigmaForm, 8, 2);

  oilPaint = new QCheckBox(tr("OilPaint Effect Radius"));
  oilRadius = new QDoubleSpinBox;
  oilRadius->setRange(1.0, 5.0);
  oilRadius->setValue(3.0);
  oilRadius->setSingleStep(0.1);
  QFormLayout oilBox;
  oilBox.addRow(oilPaint, oilRadius);
  groupGrid.addLayout(&oilBox, 9, 0);

  groupGrid.setSizeConstraint(QLayout::SetMinAndMaxSize);
  generalOption->setLayout(&groupGrid);
  generalOption->adjustSize();

}

void GeneralOption::optionSettings(void)
{
  QCoreApplication::setOrganizationName("Sd44 Soft");
  QCoreApplication::setOrganizationDomain("sd44.is-programmer.com");
  QCoreApplication::setApplicationName("Super Img Batcher");
  QSettings settings;
  if (quality->isChecked()) {
    settings.setValue("quality", true);
    settings.setValue("qualityBox", qualityBox->value());
  }
  
  if (eraseProfile->isChecked())
    settings.setValue("eraseProfile", true);
  
  if (keepExif->isChecked())
    settings.setValue("keepExif", true);
    
  if (reduceNoise->isChecked())
    settings.setValue("reduceNoise", true);
  if (reduceSpeckleNoise->isChecked())
    settings.setValue("reduceSpeckleNoise", true);
  if (enhance->isChecked())
    settings.setValue("enhance", true);
  if (normalize->isChecked())
    settings.setValue("normalize", true);
  if (trim->isChecked())
    settings.setValue("trim", true);
  if (edge->isChecked())
    settings.setValue("edge", true);
  if (emboss->isChecked())
    settings.setValue("emboss", true);
  if (equalize->isChecked())
    settings.setValue("equalize", true);
  if (monoChrome->isChecked())
    settings.setValue("monoChrome", true);
  if (addNoise->isChecked()) {
    settings.setValue("addNoise", true);
    settings.setValue("noiseType", noiseType->currentIndex());
  }
  if (sharpen->isChecked()) {
    settings.setValue("sharpen", true);
    settings.setValue("sharpenRadius", sharpenRadius->value());
    // settings.setValue("sharpenSigma", sharpenSigma->value());
  }
  if (charcoal->isChecked()) {
    settings.setValue("charcoal", true);
    settings.setValue("charcoalRadius", charcoalRadius->value());
  }
  if (oilPaint->isChecked()) {
    settings.setValue("oilPaint", true);
    settings.setValue("oilRadius", oilRadius->value());
  }
}
