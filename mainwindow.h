#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QAction>
#include <KMainWindow>
#include "sessionstack.h"



// TODO:: rm it
#include <QShortcut>
#include <QKeySequence>
#include <QPushButton>
#include <QSplitter>
#include "session.h"


class QAction;
class KActionCollection;

class MainWindow : public KMainWindow {
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        KActionCollection* actionCollection() { return m_actionCollection; }

    public slots:
        void handleTerminalActivity(Terminal* terminal);
        void handleTerminalSilence(Terminal* terminal);
        void mySplitTopBottom();
        void mySplitLeftRight();

    signals:
        void windowClosed();

    private:
        SessionStack *m_sessionStack;
        KActionCollection* m_actionCollection;
        // TODO:: rm it
        QShortcut *shortcut;
        QAction *openAct;
        QPushButton *m_button;
        QPushButton *m_button2;
        Session *m_session;
};

#endif
