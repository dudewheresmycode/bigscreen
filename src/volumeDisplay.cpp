#include "volumeDisplay.h"

VolumeDisplay::VolumeDisplay() : QWidget() {
  // implement
  volumeIcon = new VolumeIcon;
  volumeIcon->setParent(this);

  volumeText = new VolumeText();
  volumeText->setParent(this);
  // volumeText->setVisible(true);
  volumeText->setText("0");

  volumeBar = new VolumeIndicator;
  volumeBar->setParent(this);
  // volumeBar->setVisible(true);

  // setup fade in/out animation
  volumeHideEffect = new QGraphicsOpacityEffect(this);
  volumeHideEffect->setOpacity(1);
  
  volumeHideAnimation = new QPropertyAnimation(volumeHideEffect, "opacity");
  volumeHideAnimation->setDuration(1000);
  volumeHideAnimation->setStartValue(1);
  volumeHideAnimation->setEndValue(0);
  volumeHideAnimation->setEasingCurve(QEasingCurve::InQuad);

  setGraphicsEffect(volumeHideEffect);
  connect(volumeHideAnimation, SIGNAL(finished()), this, SLOT(finished()));
}

VolumeDisplay::~VolumeDisplay() {
  // cleanup
}

void VolumeDisplay::update(int percent) {
  volumeText->setText(QString("%1").arg(percent));
  volumeBar->upd((qreal)(percent / 100.0));
}
void VolumeDisplay::fadeOut() {
  volumeHideAnimation->start();
}

void VolumeDisplay::reset() {
  volumeHideAnimation->stop();
  volumeHideEffect->setOpacity(1);
}

void VolumeDisplay::finished() {
  // reset opacity to 1
  volumeHideEffect->setOpacity(1);
  // hide this VolumeDisplay
  setVisible(false);
}