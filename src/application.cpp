#include "application.h"

HTPCApplication::HTPCApplication(int argc, char **argv) {
  // QApplication.instance()
}

HTPCApplication::~HTPCApplication() {

}

bool HTPCApplication::notify( QObject *recv, QEvent *e ) {
  try {
    if (e->type() == QEvent::KeyPress) {
      // got a keypress event
      QWidget * w = focusWidget();
      // was it sent from a line edit?
      if (qobject_cast<QLineEdit*>(w) == nullptr) {
        // no, handle as global key press
        QKeyEvent * ke = dynamic_cast<QKeyEvent *>(e);
        if (SVViewStateHandler::instance().m_geometryView->handleGlobalKeyPress(ke)) {
          return true;
        }
      }
    }
    return QApplication::notify( recv, e );
  } catch (Vic3D::Exception &ex) {
    ex.writeMsgStackToError();
    IBK::IBK_Message("Vic3D::Exception caught.", IBK::MSG_ERROR, FUNC_ID);
  }
 
  return false;
}