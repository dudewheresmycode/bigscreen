#include "volumeIcon.h"
#include "constants.h"

VolumeIcon::VolumeIcon() : QLabel() {
  Q_INIT_RESOURCE(library);
  QPixmap mutePixMap(":resources/volume-high-white.png");
	setPixmap(mutePixMap);
	setScaledContents(true);
  int iconPadding = (constants::OSD_WIDTH - constants::VOLUME_HIGH_ICON_WIDTH) / 2;
	setGeometry(iconPadding, iconPadding, constants::VOLUME_HIGH_ICON_WIDTH, constants::VOLUME_HIGH_ICON_WIDTH);
}

VolumeIcon::~VolumeIcon() {
  // clean up
  Q_CLEANUP_RESOURCE(library);
}