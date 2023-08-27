/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtWidgets>

#include "trayWindow.h"

TrayWindow::TrayWindow()
{
    createIconGroupBox();
    createMessageGroupBox();

    iconLabel->setMinimumWidth(durationLabel->sizeHint().width());

    createActions();
    createTrayIcon();

    connect(showIconCheckBox, SIGNAL(toggled(bool)), trayIcon, SLOT(setVisible(bool)));
    connect(trayIcon, SIGNAL(messageClicked()), this, SLOT(messageClicked()));
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(iconGroupBox);
    mainLayout->addWidget(messageGroupBox);
    setLayout(mainLayout);

    // set application icon
    QIcon icon = QIcon(":/resources/home-theater.svg");
    setWindowIcon(icon);
    trayIcon->show();
    trayIcon->setIcon(icon);

    setWindowTitle(tr(constants::APP_NAME));
    resize(400, 300);
}

void TrayWindow::setVisible(bool visible)
{
    // minimizeAction->setEnabled(visible);
    // maximizeAction->setEnabled(!isMaximized());
    restoreAction->setEnabled(isMaximized() || !visible);
    QDialog::setVisible(visible);
}

void TrayWindow::closeEvent(QCloseEvent *event)
{
    if (trayIcon->isVisible()) {
        // QMessageBox::information(this, tr("Systray"),
        //                          tr("The program will keep running in the "
        //                             "system tray. To terminate the program, "
        //                             "choose <b>Quit</b> in the context menu "
        //                             "of the system tray entry."));
        hide();
        event->ignore();
    }
}

void TrayWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    // case QSystemTrayIcon::Trigger:
    // case QSystemTrayIcon::DoubleClick:
    default:
        ;
    }
}


void TrayWindow::messageClicked()
{
    QMessageBox::information(0, tr("Systray"),
                             tr("Sorry, I already gave what help I could.\n"
                                "Maybe you should try asking a human?"));
}

void TrayWindow::createIconGroupBox()
{
    iconGroupBox = new QGroupBox(tr("Tray Icon"));

    iconLabel = new QLabel("Icon:");

    iconComboBox = new QComboBox;

    showIconCheckBox = new QCheckBox(tr("Show icon"));
    showIconCheckBox->setChecked(true);

    QHBoxLayout *iconLayout = new QHBoxLayout;
    iconLayout->addWidget(iconLabel);
    iconLayout->addWidget(iconComboBox);
    iconLayout->addStretch();
    iconLayout->addWidget(showIconCheckBox);
    iconGroupBox->setLayout(iconLayout);
}

void TrayWindow::createMessageGroupBox()
{
    messageGroupBox = new QGroupBox(tr("On Screen Display"));

    themeLabel = new QLabel(tr("Theme:"));

    themeComboBox = new QComboBox;
    themeComboBox->addItem(tr("Mykonos (Default)"), QSystemTrayIcon::NoIcon);
    themeComboBox->addItem(tr("Minimal"), QSystemTrayIcon::NoIcon);
    themeComboBox->setCurrentIndex(0);

    durationLabel = new QLabel(tr("Duration:"));

    durationSpinBox = new QSpinBox;
    durationSpinBox->setRange(1, 10);
    durationSpinBox->setSuffix(" s");
    durationSpinBox->setValue((int) round(constants::VOLUME_HIDE_DURATION / 1000));




    QGridLayout *messageLayout = new QGridLayout;
    messageLayout->addWidget(themeLabel, 0, 0);
    messageLayout->addWidget(themeComboBox, 0, 1, 1, 2);
    messageLayout->addWidget(durationLabel, 1, 0);
    messageLayout->addWidget(durationSpinBox, 1, 1);

    messageLayout->setColumnStretch(3, 1);
    messageLayout->setRowStretch(4, 1);
    messageGroupBox->setLayout(messageLayout);
}

void TrayWindow::helpMenuTriggered()
{
  //
}

void TrayWindow::createActions()
{
    // minimizeAction = new QAction(tr("Mi&nimize"), this);
    // connect(minimizeAction, SIGNAL(triggered()), this, SLOT(hide()));

    helpAction = new QAction(tr("&Help"), this);
    connect(helpAction, SIGNAL(triggered()), this, SLOT(helpMenuTriggered()));

    restoreAction = new QAction(tr("&Settings"), this);
    connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void TrayWindow::createTrayIcon()
{
    trayIconMenu = new QMenu(this);
    // trayIconMenu->addAction(minimizeAction);
    // trayIconMenu->addAction(maximizeAction);
    // QLabel* label = new QLabel(tr("HTPC Tools"), this);
    // QWidgetAction* a = new QWidgetAction(trayIconMenu);
    // a->setDefaultWidget(label);
    // trayIconMenu->addAction(a);

    // trayIconMenu->addSection("HTPC Tools");
    // trayIconMenu->addSeparator();
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(helpAction);
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
}
