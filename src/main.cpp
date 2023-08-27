#include <QApplication>
#include <QDebug>
#include <QtWidgets>
#include <QtGui>
#include <qxtglobalshortcut.h>
#include <constants.h>
#include "mainWidget.h"
#include "trayWindow.h"

// void setupKeyHandlers(MainWidget *w) {

// }

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    // this is the important bit
    app.setQuitOnLastWindowClosed(false);

    // This is our MainWidget class containing our OSD
    MainWidget w;
    w.show(); // Show main window

    TrayWindow trayWindow;
    trayWindow.show();
    
    /**
    * Mute Button Key Handler
    */
    const QKeySequence shortcutMute(constants::KEYS_VOLUME_MUTE);
    const QxtGlobalShortcut globalShortcutMute(shortcutMute);

    qDebug() << QString("Setting shortcut %1").arg(shortcutMute.toString());

    if ( !globalShortcutMute.isValid() ) {
        qDebug() << QString("Error: Failed to set shortcutMute %1").arg(shortcutMute.toString());
    }
    QObject::connect(&globalShortcutMute, &QxtGlobalShortcut::activated, &globalShortcutMute, [&]{
        qDebug() << QString("Shortcut pressed %1").arg(shortcutMute.toString());
        w.onMuteKeyPress();
    });

    /**
    * Volume Up Key Handler
    */
    const QKeySequence shortcutVolUp(constants::KEYS_VOLUME_UP);
    const QxtGlobalShortcut globalShortcutVolUp(shortcutVolUp);

    qDebug() << QString("Setting shortcut %1").arg(shortcutVolUp.toString());

    if ( !globalShortcutVolUp.isValid() ) {
        qDebug() << QString("Error: Failed to set shortcut %1").arg(shortcutVolUp.toString());
    }
    QObject::connect(&globalShortcutVolUp, &QxtGlobalShortcut::activated, &globalShortcutVolUp, [&]{
        qDebug() << QString("Shortcut pressed %1").arg(shortcutVolUp.toString());
        w.onVolumeUpKeyPress();
    });

    /**
    * Volume Down Key Handler
    */
    const QKeySequence shortcutVolDown(constants::KEYS_VOLUME_DOWN);
    const QxtGlobalShortcut globalShortcutVolDown(shortcutVolDown);

    qDebug() << QString("Setting shortcut %1").arg(shortcutVolDown.toString());

    if ( !globalShortcutVolDown.isValid() ) {
        qDebug() << QString("Error: Failed to set shortcut %1").arg(shortcutVolDown.toString());
    }
    QObject::connect(&globalShortcutVolDown, &QxtGlobalShortcut::activated, &globalShortcutVolDown, [&]{
        qDebug() << QString("Shortcut pressed %1").arg(shortcutVolDown.toString());
        w.onVolumeDownKeyPress();
    });

    /**
    * Sleep Key Handler
    */
    const QKeySequence shortcutSleep(constants::KEYS_SLEEP);
    const QxtGlobalShortcut globalShortcutSleep(shortcutSleep);

    qDebug() << QString("Setting shortcut %1").arg(shortcutSleep.toString());

    if ( !globalShortcutSleep.isValid() ) {
        qDebug() << QString("Error: Failed to set shortcut %1").arg(shortcutSleep.toString());
    }
    QObject::connect(&globalShortcutSleep, &QxtGlobalShortcut::activated, &globalShortcutSleep, [&]{
        qDebug() << QString("Shortcut pressed %1").arg(shortcutSleep.toString());
    });

    return app.exec();
}
