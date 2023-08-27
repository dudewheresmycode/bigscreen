#include <QtWidgets>
#include "muteIcon.h"
#include "volumeText.h"

#ifndef MUTEDISPLAY_H
#define MUTEDISPLAY_H

class QWidget;

class MuteDisplay : public QWidget
{
  Q_OBJECT
public:
  explicit MuteDisplay(); //Constructor
  ~MuteDisplay(); // Destructor

// public slots:

private:
  MuteIcon* muteIcon;
  VolumeText* muteText;
};

#endif // MUTEDISPLAY_H