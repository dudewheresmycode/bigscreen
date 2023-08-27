#include <QWidget>
#include <QLabel>

#ifndef MUTEICON_H
#define MUTEICON_H

class QLabel;

class MuteIcon : public QLabel
{
  Q_OBJECT
public:
  explicit MuteIcon(); //Constructor
  ~MuteIcon(); // Destructor
// private:
	// QLabel* muteIconLabel;

};

#endif // MUTEICON_H