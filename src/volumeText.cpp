#include "volumeText.h"
#include "constants.h"

VolumeText::VolumeText() : QLabel() {
  QPalette textPalette;
  textPalette.setColor(QPalette::WindowText, Qt::white);
  setPalette(textPalette);
  setStyleSheet(QString("font-weight: bold; font-size: %1px;").arg(constants::VOLUME_FONT_HEIGHT));

  setAlignment(Qt::AlignCenter);

  int osdTextHeight = constants::VOLUME_FONT_HEIGHT + 10; // +10 adds some wiggle room, but it sould be vertically centered in the box
  int yPos = constants::OSD_WIDTH + 20;
  int osdTextWidth = constants::OSD_WIDTH - (constants::VOLUME_STROKE_WIDTH / 2);
	setGeometry(
    0,
    yPos,
    osdTextWidth,
    osdTextHeight
  );
}

VolumeText::~VolumeText() {
  // clean up
}