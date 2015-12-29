#include <QApplication>
//#include "mainwindow.h"
#include <QPushButton>

int main (int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget window;
    window.setFixedSize(100, 50);
    QPushButton *button = new QPushButton("yo", &window);
    button->setGeometry(10, 10, 80, 30);
    window.show();
    return app.exec();
}
