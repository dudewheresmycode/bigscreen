#include <iostream>
#include <QDebug>
#include <qxtglobalshortcut.h>
#include "mainWidget.h"
#include "volume.h"

MainWidget::MainWidget(QWidget *parent) : QWidget(parent) {
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
  muteDisplay = new MuteDisplay;
  muteDisplay->setParent(this);

  volumeDisplay = new VolumeDisplay;
  volumeDisplay->setParent(this);
  connect(volumeDisplay, SIGNAL(finished()), this, SLOT(volumeDisplayHidden()));

  volumeHideTimer = new QTimer(this);
  connect(volumeHideTimer, SIGNAL(timeout()), this, SLOT(volumeTimeout()));

  // get volume status first
  volumeControl::getVolume();
  updateVolumeOSD();
}

// Destructor
MainWidget::~MainWidget() {
  Q_CLEANUP_RESOURCE(library);
}

void MainWidget::toggleVolumeVisibility(bool visible) {
  qDebug() << QString("volume-ui - Setting visibility to: %1").arg(visible);
  volumeDisplay->reset();
  volumeDisplay->setVisible(visible);

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

void MainWidget::volumeDisplayHidden() {
  // hide the window
  setVisible(false);
  qDebug() << "volumeDisplayHidden";
}

void MainWidget::volumeTimeout() {
  qDebug() << "volumeTimeout";
  volumeDisplay->fadeOut();
}

void MainWidget::updateVolumeOSD() {
  // one way or another we'll display something
  setVisible(true);
  // either mute
	muteDisplay->setVisible(volumeControl::isMuted);
  // either or volume control
  toggleVolumeVisibility(!volumeControl::isMuted);

  if (!volumeControl::isMuted) {
    volumeDisplay->update(volumeControl::volumePercent);
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
  // TODO: Allow turning down volume while still muted, and apply that lower 
  // volume when unmuted. For now just ignore the volume press when muted.
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