#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace constants {
  static const char* APP_NAME = "Bigscreen";

  // interval for system udates (in milliseconds)
  const int SYSTEM_UPDATE_INTERVAL = 7000;
  // pause before hiding the volume (in milliseconds)
  const int VOLUME_HIDE_DURATION = 5000;
  const int OSD_WIDTH = 400;
  const int OSD_HEIGHT = 500;
  const int VOLUME_STROKE_WIDTH = 20;
  const int VOLUME_FONT_HEIGHT = 80;
  const int VOLUME_MUTE_ICON_WIDTH = 400;
  const int VOLUME_HIGH_ICON_WIDTH = 200;
// key bindings
  static const char* KEYS_VOLUME_MUTE = "Ctrl+Shift+1";
  static const char* KEYS_VOLUME_UP = "Ctrl+Shift+2";
  static const char* KEYS_VOLUME_DOWN = "Ctrl+Shift+3";
  static const char* KEYS_SLEEP = "Ctrl+Shift+4";
} // namespace constants

#endif // CONSTANTS_H