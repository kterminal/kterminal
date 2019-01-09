#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QAction>
#include <QSettings>
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
	~MainWindow();
        KActionCollection* actionCollection() { return m_actionCollection; }

    public slots:
        void handleTerminalActivity(Terminal* terminal);
        void handleTerminalSilence(Terminal* terminal);

    signals:
        void windowClosed();

    private:
	void createMenus();
	void createMenuActions();
	void createShortcuts();
	QSettings *settings;
        QString VersionStr;
        SessionStack *m_sessionStack;
        KActionCollection* m_actionCollection;
        QWidget *centralWidget;
        QGridLayout *gridLayout;
        QShortcut *m_left_tab_shortcut;
        QShortcut *m_right_tab_shortcut;
        QShortcut *m_split_horizontal_shortcut;
        QShortcut *m_split_vertical_shortcut;
        QShortcut *m_new_tab_shortcut;
        Session *m_session;
	void readSettings();
	void writeSettings();
	
	QMenu *fileMenu;
	QMenu *viewMenu;
	QMenu *helpMenu;
	QAction *newTabAct;
	QAction *closeTabAct;
	QAction *quitAct;
	QAction *splitVAct;
	QAction *splitHAct;
	QAction *aboutAct;
	QAction *aboutQtAct;
        
    private slots:
        void aboutQtBox();
        void aboutBox();
};

#endif
