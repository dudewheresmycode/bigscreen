#include "muteDisplay.h"

MuteDisplay::MuteDisplay() : QWidget() {
  // implement
  muteIcon = new MuteIcon;
  muteIcon->setParent(this);
  
  muteText = new VolumeText;
  muteText->setParent(this);
  muteText->setText("MUTE");  
}

MuteDisplay::~MuteDisplay() {
  // cleanup
}
