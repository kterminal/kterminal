#include "mainwindow.h"
#include "sessionstack.h"

class SessionStack;

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    m_sessionStack = new SessionStack(this);
}
