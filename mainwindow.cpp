#include <iostream>
#include "mainwindow.h"
#include "sessionstack.h"

#include <KMainWindow>

class SessionStack;


MainWindow::MainWindow(QWidget *parent) : KMainWindow(parent) {

    const char *app_name = "Konsplit";
    this->setWindowTitle(QApplication::translate(app_name, app_name, 0));
    if (this->objectName().isEmpty()) {
        this->setObjectName(app_name);
    }

    centralWidget = new QWidget(this);
    centralWidget->setObjectName(QStringLiteral("centralWidget"));

    m_sessionStack = new SessionStack(centralWidget, this);
    m_sessionStack->addSession();

    gridLayout = new QGridLayout(centralWidget);
    gridLayout->setSpacing(6);
    gridLayout->setContentsMargins(1, 1, 1, 1);
    gridLayout->setObjectName(QStringLiteral("gridLayout"));
    this->setCentralWidget(centralWidget);

    gridLayout->addWidget(m_sessionStack);

    //this->resize(700, 340);
    this->resize(1300, 840);


    m_split_left_shortcut = new QShortcut(QKeySequence("Ctrl+)"), this);
    QObject::connect(m_split_left_shortcut, SIGNAL(activated()), this, SLOT(mySplitLeftRight()));

    m_split_right_shortcut = new QShortcut(QKeySequence("Ctrl+("), this);
    QObject::connect(m_split_right_shortcut, SIGNAL(activated()), this, SLOT(mySplitTopBottom()));

}

void MainWindow::closeEvent(QCloseEvent *event) {
    qApp->exit();
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
