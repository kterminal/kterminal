#include <QApplication>
#include <QSettings>
#include "mainwindow.h"

int main (int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    QSettings::setDefaultFormat(QSettings::IniFormat); // personal preference
    qApp->setOrganizationName("Unknown");
    qApp->setApplicationName("KTerminal");

    MainWindow m_mainWindow;
    m_mainWindow.show();

    return app.exec();
}
