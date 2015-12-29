#include "mainwindow.h"

class Button;

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    setFixedSize(300, 300);
    QPushButton *button = new QPushButton("yo button", this);
    button->setGeometry(10, 10, 80, 30);
}
