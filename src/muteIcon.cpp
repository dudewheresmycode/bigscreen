#include "muteIcon.h"
#include "constants.h"

MuteIcon::MuteIcon() : QLabel() {
  Q_INIT_RESOURCE(library);
  QPixmap mutePixMap(":resources/mute-circle.png");
	setPixmap(mutePixMap);
	// setScaledContents(true);
  // int iconPadding = (constants::OSD_WIDTH - constants::VOLUME_MUTE_ICON_WIDTH) / 2;
	setGeometry(0, 0, constants::VOLUME_MUTE_ICON_WIDTH, constants::VOLUME_MUTE_ICON_WIDTH);
}

MuteIcon::~MuteIcon() {
  // clean up
  Q_CLEANUP_RESOURCE(library);
}