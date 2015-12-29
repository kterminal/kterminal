#include "mainwindow.h"
#include "sessionstack.h"

class SessionStack;

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    m_sessionStack = new SessionStack(this);
    m_sessionStack->addSession();
}


void MainWindow::handleTerminalActivity(Terminal *terminal) {

}

void MainWindow::handleTerminalSilence(Terminal *terminal) {
}
