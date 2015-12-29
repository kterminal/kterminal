#include "window.h"

Window::Window(QWidget *parent) : QWidget(parent) {
    // set fixed size of the Window widget
    setFixedSize(100, 50);
    // create and set position to button
    QPushButton *button = new QPushButton("seperate class", this);
    button->setGeometry(10, 10, 80, 30);
};
