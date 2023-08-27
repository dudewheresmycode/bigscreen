#include <QApplication>

#ifndef TRAY_APPLICATION_H
#define TRAY_APPLICATION_H

class HTPCApplication : public QApplication
{
public:
  explicit HTPCApplication(int argc, char **argv); //Constructor
  ~HTPCApplication(); // Destructor
protected:
    bool notify(QObject *recv, QEvent *e);  
};

#endif // TRAY_APPLICATION_H