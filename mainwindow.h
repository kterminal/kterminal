#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <KMainWindow>
#include "sessionstack.h"



// TODO:: rm it
#include <QPushButton>
#include <QSplitter>
#include "session.h"

class MainWindow : public KMainWindow {
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);

    public slots:
        void handleTerminalActivity(Terminal* terminal);
        void handleTerminalSilence(Terminal* terminal);

    signals:
        void windowClosed();

    private:
        SessionStack *m_sessionStack;
        // TODO:: rm it
        QPushButton *m_button;
        QPushButton *m_button2;
        Session *m_session;
};

#endif
