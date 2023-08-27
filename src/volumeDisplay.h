#include <QtWidgets>
#include "volumeIcon.h"
#include "volumeIndicator.h"
#include "volumeText.h"

#ifndef VOLUMEDISPLAY_H
#define VOLUMEDISPLAY_H

class QWidget;

class VolumeDisplay : public QWidget
{
  Q_OBJECT
public:
  explicit VolumeDisplay(); //Constructor
  ~VolumeDisplay(); // Destructor

public slots:
  void reset();
  void fadeOut();
  void finished();
  void update(int percent);

private:
  QPropertyAnimation* volumeHideAnimation;
  QGraphicsOpacityEffect* volumeHideEffect;
  VolumeIndicator *volumeBar;
	VolumeIcon* volumeIcon;
  VolumeText* volumeText;
};

#endif // VOLUMEDISPLAY_H