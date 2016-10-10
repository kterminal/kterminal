#include "mainwindow.h"
#include "sessionstack.h"
#include <QMessageBox>
#include <QDesktopWidget>
#include <KMainWindow>
#include <QMenuBar>
#include <QAction>
#include <QLabel>
#include <QVBoxLayout>
#include <QSize>
class SessionStack;


MainWindow::MainWindow(QWidget *parent) : KMainWindow(parent) {

    const char *app_name = "kterminal";
    VersionStr = "0.0.1";
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
    

    readSettings();
    createShortcuts();
    createMenuActions();
    createMenus();

    
    QWidget *topFiller = new QWidget;
    topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    
    QLabel *infoLabel = new QLabel(tr("<i>Choose a menu option</i>"));
    infoLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    infoLabel->setAlignment(Qt::AlignCenter);
    
    QWidget *bottomFiller = new QWidget;
    bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(5);
    layout->addWidget(topFiller);
    layout->addWidget(infoLabel);
    layout->addWidget(bottomFiller);


    //this->setWindowTitle(tr("Test"));
    this->setMinimumSize(160, 160);
    
    
    
    
}

MainWindow::~MainWindow()
{
  writeSettings();
}

void MainWindow::readSettings()
{
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    const QByteArray geometry = settings.value("geometry", QByteArray()).toByteArray();
    if (geometry.isEmpty()) {
        const QRect availableGeometry = QApplication::desktop()->availableGeometry(this);
        resize(availableGeometry.width() / 3, availableGeometry.height() / 2);
        move((availableGeometry.width() - width()) / 2,
             (availableGeometry.height() - height()) / 2);
    } else {
        restoreGeometry(geometry);
    }
}

void MainWindow::writeSettings()
{
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    settings.setValue("geometry", saveGeometry());
}

void MainWindow::handleTerminalActivity(Terminal *terminal) {

}

void MainWindow::handleTerminalSilence(Terminal *terminal) {
}

void MainWindow::createShortcuts()
{
      m_left_tab_shortcut = new QShortcut(QKeySequence("Shift+Left"), this);
    QObject::connect(m_left_tab_shortcut, SIGNAL(activated()),
                     m_sessionStack, SLOT(select_left_tab()));

    m_right_tab_shortcut = new QShortcut(QKeySequence("Shift+Right"), this);
    QObject::connect(m_right_tab_shortcut, SIGNAL(activated()),
                     m_sessionStack, SLOT(select_right_tab()));

    m_split_horizontal_shortcut = new QShortcut(QKeySequence("Ctrl+'"), this);
    QObject::connect(m_split_horizontal_shortcut, SIGNAL(activated()),
                     m_sessionStack, SLOT(horizontal_split_current_terminal()));

    m_split_vertical_shortcut = new QShortcut(QKeySequence("Ctrl+;"), this);
    QObject::connect(m_split_vertical_shortcut, SIGNAL(activated()),
                     m_sessionStack, SLOT(vertical_split_current_terminal()));

    QShortcut *m_new_tab_shortcut = new QShortcut(QKeySequence("Ctrl+t"), this);
    QObject::connect(m_new_tab_shortcut, SIGNAL(activated()), m_sessionStack, SLOT(addSession()));
}


void MainWindow::createMenuActions()
{
    newTabAct = new QAction(tr("&New Tab"), this);
    connect(newTabAct, SIGNAL(triggered()), m_sessionStack, SLOT(addSession()));
    
    closeTabAct = new QAction(tr("&Close Tab"), this);
    connect(closeTabAct, SIGNAL(triggered(bool)), m_sessionStack, SLOT(removeSession(-1))); // TODO: reggler 10/08/2016: this doesn't work yet
    
    splitVAct = new QAction(tr("Split &vertically"), this);
    connect(splitVAct, SIGNAL(triggered()), m_sessionStack, SLOT(vertical_split_current_terminal()));
    
    splitHAct = new QAction(tr("Split &horizontally"), this);
    connect(splitHAct, SIGNAL(triggered()), m_sessionStack, SLOT(horizontal_split_current_terminal()));
    
    quitAct = new QAction(tr("&Quit"), this);
    quitAct->setShortcuts(QKeySequence::Quit);
    quitAct->setText(tr("&Quit"));
    connect(quitAct, SIGNAL(triggered()), SLOT(close()));
    
    aboutAct = new QAction(tr("&About KTerminal"), this);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(aboutBox()));
    
    aboutQtAct = new QAction(tr("&About Qt"), this);
    connect(aboutQtAct, SIGNAL(triggered()), this, SLOT(aboutQtBox()));

}

void MainWindow::createMenus(void) 
{
  fileMenu = menuBar()->addMenu(tr("&File"));
  fileMenu->addAction(newTabAct);
  fileMenu->addAction(closeTabAct);
  fileMenu->addSeparator();
  fileMenu->addAction(quitAct);
   
  viewMenu = menuBar()->addMenu(tr("&View"));
  viewMenu->addAction(splitHAct);
  viewMenu->addAction(splitVAct);
  
  helpMenu = menuBar()->addMenu(tr("&Help"));
  helpMenu->addAction(aboutAct);
  helpMenu->addAction(aboutQtAct);
}

void MainWindow::aboutBox(void)
{
    QMessageBox::about(this, tr("About KTerminal"), tr("KTerminal version ")+VersionStr);
}

void MainWindow::aboutQtBox(void)
{
    QMessageBox::aboutQt(this, tr("About Qt"));
}

