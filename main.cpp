#include <QApplication>
#include "mainwindow.h"

int main (int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow *m_mainWindow;

    return app.exec();
}
