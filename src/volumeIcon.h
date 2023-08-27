#include <QWidget>
#include <QLabel>

#ifndef VOLUMEICON_H
#define VOLUMEICON_H

class QLabel;

class VolumeIcon : public QLabel
{
  Q_OBJECT
public:
  explicit VolumeIcon(); //Constructor
  ~VolumeIcon(); // Destructor
};

#endif // VOLUMEICON_H