#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QtWidgets>
#include <QWidget>
#include <QProcess>
#include <QTimer>
#include <constants.h>
#include "muteIcon.h"
#include "muteDisplay.h"
#include "volumeDisplay.h"

class QPushButton;
class QLabel;
// class QTextBrowser;

// This is the declaration of our MainWidget class
// The definition/implementation is in mainwidget.cpp
class MainWidget : public QWidget
{
  Q_OBJECT

public:
  explicit MainWidget(QWidget *parent = 0); //Constructor
  ~MainWidget(); // Destructor

private slots:
  // void addMuteIcon();
  // void addVolumeUpIcon();
  void updateVolumeOSD();
  void toggleVolumeVisibility(bool visible);
  void volumeTimeout();
  void volumeDisplayHidden();

public slots:
  void onMuteKeyPress();
  void onSleepKeyPress();
  void onVolumeUpKeyPress();
  void onVolumeDownKeyPress();

protected:
  void timerEvent(QTimerEvent *event);

private:
	QPushButton* button_;
  QLabel* clock_icon_;
  MuteDisplay* muteDisplay;
  VolumeDisplay* volumeDisplay;

  QPixmap mute_pix_;
  QLabel* volume_down_icon_;
  QLabel* volume_up_icon_;
	QLabel* volume_level_;
	QProcess process_;
	QWidget* main_widget_;
  QTimer* volumeHideTimer;
  
  int timerId;
  //  QTextBrowser* textBrowser_;

// protected:
//   virtual void keyPressEvent(QKeyEvent *event);
//   virtual void keyReleaseEvent(QKeyEvent *event);
};

#endif // MAINWIDGET_H