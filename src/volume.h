#ifndef VOLUME_H
#define VOLUME_H

#include <iostream>
// #include <alsa/asoundlib.h>
#include <unistd.h>
#include <QProcess>
#include <QDebug>

namespace volumeControl {
  bool isMuted = false;
  int volumePercent = -1;
  int storedVolumePercent = -1;
  QProcess process_;
  QRegExp rx("Left:.*\\[(\\d+)%\\]");

  int parseVolume(QString volumeString) {
    int pos = 0;
    int percent = -1;
    QList<int> list;
    while ((pos = rx.indexIn(volumeString, pos)) != -1) {
      list << rx.cap(1).toInt();
      pos += rx.matchedLength();
    }
    qDebug()<<list;
    if (list.count() == 1) {
      percent = list.first();
    }
    return percent;
  }

  void getVolume() {
    process_.start("amixer -D pulse sget Master");
    // process_.start("awk -F\"[][]\" '/Left:/ { print $2 }' <(amixer -D pulse sget Master)");
    process_.waitForFinished(); // sets current thread to sleep and waits for pingProcess end
    QString output(process_.readAllStandardOutput());
    volumePercent = parseVolume(output);
    // isMuted = volumePercent < 1;
    // qDebug()<<QString("Volume detected: %1").arg(volumePercent);
    // qDebug()<<QString("isMuted: %1").arg(isMuted);
    qDebug()<<QString("volume get - isMuted: %1, volumePercent: %2").arg(isMuted).arg(volumePercent);
  }

  void setVolume(int newVolume) {
    if (newVolume == volumePercent) {
      return;
    }
    qDebug() << QString("volume - Setting volume to: %1%").arg(newVolume);
    QString cmd = QString("amixer -D pulse set Master %1%").arg(newVolume);
    // qDebug() << cmd.toStdString();
    process_.start(cmd);
    process_.waitForFinished(); // sets current thread to sleep and waits for pingProcess end
    QString output(process_.readAllStandardOutput());
    volumePercent = parseVolume(output);
    qDebug()<<QString("volume set - isMuted: %1, volumePercent: %2%").arg(isMuted).arg(volumePercent);
  }

  // int getMuted() {
  //   return isMuted;
  // }

  void volumeUp() {
    // TODO: do this in a periodic background task?
    // getVolume();
    int newVolume = std::min(volumePercent + 5, 100);
    qDebug() << QString("set to: %1%").arg(newVolume);
    setVolume(newVolume);
  }

  void volumeDown() {
    // TODO: do this in a periodic background task?
    // getVolume();
    if (volumePercent > 0) {
      // int newVolume = volumePercent - 5;
      int newVolume = std::max(volumePercent - 5, 0);
      qDebug() << QString("set to: %1%").arg(newVolume);
      setVolume(newVolume);
    }
  }

  int toggleMute() {
    getVolume();
    if (isMuted) {
      if (storedVolumePercent < 0) {
        storedVolumePercent = volumePercent;
      }
      // unmute
      setVolume(storedVolumePercent);
    } else {
      // mute
      storedVolumePercent = volumePercent;
      setVolume(0);
    }
    isMuted = !isMuted;
    return 0;
  }
  
}
#endif // VOLUME_H