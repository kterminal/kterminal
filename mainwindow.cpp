#include <iostream>
#include "mainwindow.h"
#include "sessionstack.h"

#include <KMainWindow>

class SessionStack;


MainWindow::MainWindow(QWidget *parent) : KMainWindow(parent) {
    this->resize(1024, 640);
    m_sessionStack = new SessionStack(this);
    m_sessionStack->addSession();

    /*
    Session* session = new Session(Session::Single, this);
    */

    /*
    QSplitter *splitter = new QSplitter(this);
    splitter->resize(600, 600);
    QPushButton *m_button = new QPushButton("1");
    QPushButton *m_button2 = new QPushButton("2");
    splitter->addWidget(m_button);
    splitter->addWidget(m_button2);
    */
    //QPushButton *m_button = new QPushButton("1", this);
    //m_button->resize(600, 600);

    QShortcut *shortcut = new QShortcut(QKeySequence("Ctrl+)"), this);
    QObject::connect(shortcut, SIGNAL(activated()), this, SLOT(mySplitLeftRight()));

    shortcut = new QShortcut(QKeySequence("Ctrl+("), this);
    QObject::connect(shortcut, SIGNAL(activated()), this, SLOT(mySplitTopBottom()));

}


void MainWindow::handleTerminalActivity(Terminal *terminal) {

}

void MainWindow::handleTerminalSilence(Terminal *terminal) {
}
void MainWindow::mySplitTopBottom() {
    std::cout << "mySplitTopBottom" << std::endl;
    m_sessionStack->splitSessionTopBottom(0);
}
void MainWindow::mySplitLeftRight() {
    std::cout << "mySplitLeftRight" << std::endl;
    m_sessionStack->splitSessionLeftRight(0);
}
