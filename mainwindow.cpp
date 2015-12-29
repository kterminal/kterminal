#include "mainwindow.h"
#include "sessionstack.h"

#include <KMainWindow>

class SessionStack;


MainWindow::MainWindow(QWidget *parent) : KMainWindow(parent) {
    m_sessionStack = new SessionStack(this);
    m_sessionStack->addSession();
}


void MainWindow::handleTerminalActivity(Terminal *terminal) {

}

void MainWindow::handleTerminalSilence(Terminal *terminal) {
}
