#include <iostream>
#include <QDebug>
#include <qxtglobalshortcut.h>
#include "mainWidget.h"
#include "volume.h"

// Constructor for main widget
// add to enable frameless mode
// Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowStaysOnTopHint
MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent) {
  Q_INIT_RESOURCE(library);

  // set window size and position in top right
	QDesktopWidget widget;
	QRect screenGeometry = widget.screenGeometry();
  int screenWidth = screenGeometry.width();
  int marginTop = 200;
  int marginLeft = 200;
  qDebug() << QString("windowWidth: %1, windowHeight: %2, screenWidth: %3").arg(constants::OSD_WIDTH).arg(constants::OSD_HEIGHT).arg(screenWidth);

	resize(constants::OSD_WIDTH, constants::OSD_HEIGHT);
	move(screenGeometry.width() - constants::OSD_WIDTH - marginLeft, marginTop);

  setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowStaysOnTopHint);
	setAttribute(Qt::WA_TranslucentBackground);
	setAttribute(Qt::WA_ShowWithoutActivating);
  setFocusPolicy(Qt::FocusPolicy::TabFocus);

	setWindowTitle(tr("htpc-utils"));

  // setup widgets
  muteWidget = new QWidget;
  muteWidget->setParent(this);

  muteIcon = new MuteIcon;
  muteIcon->setParent(muteWidget);

  muteText = new VolumeText();
  muteText->setParent(muteWidget);
  muteText->setText("MUTE");
  
  volumeWidget = new QWidget;
  volumeWidget->setParent(this);

  volumeIcon = new VolumeIcon;
  volumeIcon->setParent(volumeWidget);

  volumeText = new VolumeText();
  volumeText->setParent(volumeWidget);
  volumeText->setVisible(true);
  volumeText->setText("0");

  volumeBar = new VolumeIndicator;
  volumeBar->setParent(volumeWidget);
  volumeBar->setVisible(true);

  volumeHideTimer = new QTimer(this);
  connect(volumeHideTimer, SIGNAL(timeout()), this, SLOT(volumeTimeout()));

  // get volume status first
  volumeControl::getVolume();

  // setup fade in/out animation
  volumeHideEffect = new QGraphicsOpacityEffect(this);
  volumeHideEffect->setOpacity(1);
  volumeHideAnimation = new QPropertyAnimation(volumeHideEffect, "opacity");
  volumeHideAnimation->setDuration(1000);
  volumeHideAnimation->setStartValue(1);
  volumeHideAnimation->setEndValue(0);

  volumeWidget->setGraphicsEffect(volumeHideEffect);

  updateVolumeOSD();
}

// Destructor
MainWidget::~MainWidget() {
  Q_CLEANUP_RESOURCE(library);
}


void MainWidget::finishFadeOut() {
  qDebug() << "finishFadeOut...";
  // QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect(this);
  volumeHideEffect->setOpacity(1);
  volumeWidget->setVisible(false);
  setVisible(false);
}

void MainWidget::resetVolumeOpacity() {
  volumeHideAnimation->stop();
  volumeHideEffect->setOpacity(1);
}

void MainWidget::toggleVolumeVisibility(bool visible) {
  qDebug() << QString("volume-ui - Setting visibility to: %1").arg(visible);
  volumeWidget->setVisible(visible);
  resetVolumeOpacity();
  if (volumeHideTimer->isActive()) {
    qDebug() << "canceling timer";
    volumeHideTimer->stop();
  }
  if (visible) {
    qDebug() << QString("volume-ui - Hiding in %1 ms").arg(constants::VOLUME_HIDE_DURATION);
    // only timeout once
    volumeHideTimer->setSingleShot(true);
    volumeHideTimer->start(constants::VOLUME_HIDE_DURATION);
  }
  
}

void MainWidget::volumeTimeout() {
  qDebug() << "volumeTimeout";
  volumeHideAnimation->setEasingCurve(QEasingCurve::InQuad);
  volumeHideAnimation->start();
  connect(volumeHideAnimation, SIGNAL(finished()), this, SLOT(finishFadeOut()));
}

void MainWidget::updateVolumeOSD() {
  // one way or another we'll display something
  setVisible(true);
  // either mute
	muteWidget->setVisible(volumeControl::isMuted);
  // either or volume control
  toggleVolumeVisibility(!volumeControl::isMuted);

  if (!volumeControl::isMuted) {
    volumeText->setText(QString("%1").arg(volumeControl::volumePercent));
    volumeBar->upd((qreal)(volumeControl::volumePercent / 100.0));
  }
}

void MainWidget::timerEvent(QTimerEvent *event) {
  qDebug()<<"Refreshing volume...";
  volumeControl::getVolume();
}


void MainWidget::onMuteKeyPress() {
  qDebug() << "onMuteKeyPress";
  volumeControl::toggleMute();
  updateVolumeOSD();
}

void MainWidget::onVolumeUpKeyPress() {
  qDebug() << "onVolumeUpKeyPress";
  if (volumeControl::isMuted) {
    volumeControl::toggleMute();
  } else {
    volumeControl::volumeUp();
  }
  updateVolumeOSD();
}

void MainWidget::onVolumeDownKeyPress() {
  // ignore volume press when muted
  if (volumeControl::isMuted) {
    return;
  }
  qDebug() << "onVolumeDownKeyPress";
  volumeControl::volumeDown();
  updateVolumeOSD();
}

void MainWidget::onSleepKeyPress() {
  qDebug() << "onSleepKeyPress";

}