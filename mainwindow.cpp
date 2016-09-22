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
