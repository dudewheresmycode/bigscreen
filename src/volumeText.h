#include <QWidget>
#include <QLabel>

#ifndef VOLUMETEXT_H
#define VOLUMETEXT_H

class QLabel;

class VolumeText : public QLabel
{
  Q_OBJECT
public:
  explicit VolumeText(); //Constructor
  ~VolumeText(); // Destructor
};

#endif // VOLUMETEXT_H