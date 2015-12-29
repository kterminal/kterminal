#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "sessionstack.h"


class MainWindow : public QWidget {
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
    private:
        SessionStack *m_sessionStack;
};

#endif
