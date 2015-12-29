#include <QApplication>
#include "mainwindow.h"

int main (int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow m_mainWindow;
    m_mainWindow.show();

    return app.exec();
}
