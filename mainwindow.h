#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QAction>
#include <KMainWindow>
#include "sessionstack.h"

#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QShortcut>
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

    protected:
        void closeEvent(QCloseEvent *event);

    private:
        SessionStack *m_sessionStack;
        KActionCollection* m_actionCollection;
        QWidget *centralWidget;
        QGridLayout *gridLayout;
        QShortcut *m_split_left_shortcut;
        QShortcut *m_split_right_shortcut;
        Session *m_session;
};

#endif
